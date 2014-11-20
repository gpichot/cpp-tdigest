#ifndef HEADER_AVLTREE
#define HEADER_AVLTREE

#include <cassert>
#include <cmath>
#include <iostream>


using namespace std;


class AvlTree {

    private:
        int       _root;
        int       _n = 0;
        // TODO We should reallocate tables (ie allow dynamic arrays)
        int       _parent[1000];
        int       _left[1000];
        int       _right[1000];
        char      _depth[1000];
        int       _count[1000];
        double    _values[1000];
        int       _aggregatedCount[1000];

    public:
        static const int NIL = 0;

        AvlTree() {
            _root = NIL;

            _depth[NIL]     = 0;
            _parent[NIL]    = 0;
            _left[NIL]      = 0;
            _right[NIL]     = 0;
        }

        //
        // Node comparison
        //

        // O(1)
        inline int compare(int node, double x) const {
            if(value(node) < x) {
                return 1;
            } else if(value(node) == x) {
                return 0;
            } else {
                return -1;
            }
        }
    
        // O(1)
        inline int compare(int nodeA, int nodeB) const {
            return compare(nodeA, value(nodeB));
        }

        //
        // Tree accessors
        //

        // O(1)
        inline int root() const {
            return _root;
        }
        // O(1)
        inline int size() const {
            return _n;
        }

        //
        // Node accessors
        //

        // O(1)
        inline int parentNode(int node) const {
            return _parent[node];
        }
        // O(1)
        inline int leftNode(int node) const {
            return _left[node];
        }
        // O(1)
        inline int rightNode(int node) const {
            return _right[node];
        }
        // O(1)
        inline int depth(int node) const {
            return _depth[node];
        }
        // O(1)
        inline int count(int node) const {
            return _count[node];
        }
        // O(1)
        inline int aggregatedCount(int node) const {
            return _aggregatedCount[node];
        }
        // O(1)
        inline double value(int node) const {
            return _values[node];
        }

        //
        // Tree accessors
        //

        // O(log(n))
        int first(int node) const {
            if(node == NIL) {
                return NIL;
            }

            while(true) {
                const int left = leftNode(node);
                if(left == NIL) {
                    break;
                }
                node = left;
            }
            return node;
        }

        // O(log(n))
        int first() const {
            return first(_root);
        }

        // O(log(n)) 
        int last(int node) const {
            while(true) {
                const int right = rightNode(node);
                if(right == NIL) {
                    break;
                }
                node = right;
            }
            return node;
        }

        // O(log(n))
        int nextNode(int node) const {
            const int right = rightNode(node);
            if(right != NIL) {
                return first(right);
            } else {
                int parent = parentNode(node);
                while(parent != NIL && node == rightNode(parent)) {
                    node = parent;
                    parent = parentNode(parent);
                }
                return parent;
            }
        }

        // O(log(n))
        int prevNode(int node) const {
            const int left = leftNode(node);
            if(left != NIL) {
                return last(left);
            } else {
                int parent = parentNode(node);
                while(parent != NIL && node == leftNode(parent)) {
                    node = parent;
                    parent = parentNode(parent);
                }
                return parent;
            }
        }



        //
        // Mutators
        //

        // O(1)
        void updateAggregates(int node) {
            // Updating depth
            _depth[node] = 1 + max(depth(leftNode(node)), depth(rightNode(node)));
            _aggregatedCount[node] = count(node) + aggregatedCount(leftNode(node)) + aggregatedCount(rightNode(node));
        }

        // O(log(n))
        void update(int node, double x, int w) {
            _values[node] += w * (x - value(node)) / count(node);
            _count[node] += w;
            
            for(int n = node; n != NIL; n = parentNode(n)) {
               updateAggregates(n);
            }

        }

        // O(log(n))
        void merge(int node, double x, int w) {
            assert(value(node) == x);
            _count[node] += w;
            
            for(int n = node; n != NIL; n = parentNode(n)) {
               updateAggregates(n);
            }
        }

        // O(log(n)) 
        bool add(double x, int w) {
            if(_root == NIL) {
                _root = ++_n;
                _values[_root] = x;
                _count[_root] = w;
                _left[_root] = NIL;
                _right[_root] = NIL;
                _parent[_root] = NIL;
                // Update depth and aggregates
                updateAggregates(_root);
            } else {
                int node = _root;
                int parent = NIL;
                int cmp;
                do {
                    cmp = compare(node, x);
                    if(cmp < 0) {
                        parent = node;
                        node = leftNode(node);
                    } else if (cmp > 0) {
                        parent = node;
                        node = rightNode(node);
                    } else {
                        // we merge the node
                        merge(node, x, w);
                        return false;
                    }
                } while(node != NIL);

                node = ++_n;
                _values[node] = x;
                _count[node] = w;
                _left[node] = NIL;
                _right[node] = NIL;
                _parent[node] = parent;
                if(cmp < 0) {
                    _left[parent] = node;
                } else {
                    assert(cmp > 0);
                    _right[parent] = node;
                }

                rebalance(node);

                return true;
            }
        }

        // O(log(n))
        int find(double x) const {
            for(int node = _root; node != NIL;) {
                const int cmp = compare(node, x);
                if(cmp < 0) {
                    node = leftNode(node);
                } else if(cmp > 0) {
                    node = rightNode(node);
                } else {
                    return node;
                }
            }
            return NIL;
        }
        
        // O(log(n))
        int floor(double x) const {
            int f = NIL;
            for(int node = _root; node != NIL; ) {
                const int cmp = compare(node, x);
                if(cmp <= 0) {
                    node = leftNode(node);
                } else {
                    f = node;
                    node = rightNode(node);
                }
            }
            return f;
        }

        // O(log(n))
        int floorSum(long sum) const {
            int f = NIL;
            for(int node = _root; node != NIL; ) {
                const int left = leftNode(node);
                const long leftCount = aggregatedCount(left);
                if(leftCount <= sum) {
                    f = node;
                    sum -= leftCount + count(node);
                    node = rightNode(node);
                } else {
                    node = leftNode(node);
                }
            }
            return f;
        }

        // O(log(n))
        long ceilSum(int node) const {
            const int left = leftNode(node);
            long sum = aggregatedCount(left);
            int n = node;
            for(int p = parentNode(node); p != NIL; p = parentNode(n)) {
                if(n == rightNode(p)) {
                    const int leftP = leftNode(p);
                    sum += count(p) + aggregatedCount(leftP);
                }
                n = p;
            }
            return sum;

        }

    private:
        // O(1)
        inline int balanceFactor(int node) const {
            return depth(leftNode(node)) - depth(rightNode(node));
        }

        // (O(log(n)^2)
        void rebalance(int node) {
            for(int n = node; n != NIL; ) {
                const int p = parentNode(n);

                updateAggregates(n);

                switch(balanceFactor(n)) {
                    case -2: {
                        const int right = rightNode(n);
                        if(balanceFactor(right) == 1) {
                            rotateRight(right);
                        }
                        rotateLeft(n);
                        break;
                    }
                    case 2: {
                        const int left = leftNode(n);
                        if(balanceFactor(left) == -1) {
                            rotateLeft(left);
                        }
                        rotateRight(n);
                        break;
                    }
                    case -1:
                    case  1:
                    case  0:
                        break;
                    default:
                        // We should throw an error
                        assert(true == false);
                }

                n = p;
            }
        }

        // O(log(n))
        void rotateLeft(int node) {
            const int r  = rightNode(node);
            const int lr = leftNode(r);

            _right[node] = lr;
            if(lr != NIL) {
                _parent[lr] = node;
            }

            const int p = parentNode(node);
            _parent[r] = p;
            if(p == NIL) {
                _root = r;
            } else if(leftNode(p) == node) {
                _left[p] = r;
            } else {
                assert(rightNode(p) == node);
                _right[p] = r;
            }
            _left[r] = node;
            _parent[node] = r;
            updateAggregates(node);
            updateAggregates(parentNode(node));
        }

        // O(log(n))
        // TODO to factor with rotateLeft
        void rotateRight(int node) {
            const int l = leftNode(node);
            const int rl = rightNode(l);

            _left[node] = rl;
            if(rl != NIL) {
                _parent[rl] = node;
            }

            const int p = parentNode(node);
            _parent[l] = p;
            if(p == NIL) {
                _root = l;
            } else if(rightNode(p) == node) {
                _right[p] = l;
            } else {
                assert(leftNode(p) == node);
                _left[p] = l;
            }
            _right[l] = node;
            _parent[node] = l;
            updateAggregates(node);
            updateAggregates(parentNode(node));
        }

    public:
        // 
        // For test or debugging purposes
        //

        // Check balance integrity
        bool checkBalance(int node) const {
            if(node == NIL) {
                return depth(node) == 0;
            } else {
                return depth(node) == 1 + max(depth(leftNode(node)), depth(rightNode(node)))
                    && abs(depth(leftNode(node)) - depth(rightNode(node))) <= 1
                    && checkBalance(leftNode(node))
                    && checkBalance(rightNode(node))
                ;
            }
        }
        inline bool checkBalance() const {
            return checkBalance(_root);
        }

        // Check aggregates integrity
        bool checkAggregates(int node) const {
            if(node == NIL) {
                return count(node) == 0;
            } else {
                return _aggregatedCount[node] == _count[node] + _aggregatedCount[leftNode(node)] + _aggregatedCount[rightNode(node)]
                    && checkAggregates(leftNode(node))
                    && checkAggregates(rightNode(node))
                ;
            }
        }
        inline bool checkAggregates() const {
            return checkAggregates(_root);
        }

        // Check integrity (order of nodes)
        bool checkIntegrity(int node) const {
            if(node == NIL) {
                return true;
            } else {
                bool ok = true;
                if(leftNode(node) != NIL) {
                    ok &= _values[node] >= _values[leftNode(node)];
                    ok &= checkIntegrity(leftNode(node));
                }
                if(rightNode(node) != NIL) {
                    ok &= _values[node] <= _values[rightNode(node)];
                    ok &= checkIntegrity(rightNode(node));
                }
                return ok;
            }
        }
        inline bool checkIntegrity() const {
            return checkIntegrity(_root);
        }

        // Print as rows
        void print(int node) const {
            if(node == NIL)
                return;
            cout << "Node " << node << "=> ";
            cout << "Value:" << _values[node] << " ";
            cout << "(" << _values[leftNode(node)] << ";";
            cout << "" << _values[rightNode(node)] << ") ";
            cout << "Depth: " << depth(node) << " ";
            cout << "Count: " <<_count[node] << " ";
            cout << "Aggregate: " << _aggregatedCount[node] << endl;
            print(leftNode(node));
            print(rightNode(node));
        }
        void print() const {
            print(_root);
        }

};

#endif
