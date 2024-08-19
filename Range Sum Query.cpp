/*

https://leetcode.com/problems/range-sum-query-mutable/

*/


class SegmentTree{
    vector<int> tree;
    vector<int> arr;
    int size;

    public:

    SegmentTree(vector<int> input){
        size = input.size();
        arr = input;
        tree.resize(4*size);

        build(0,0,size-1);
    }

    void build(int node, int start, int end){
        if(start == end){
            tree[node] = arr[start];
            return;
        }

        int mid = start+(end-start)/2;

        // left part
        build(2*node+1,start,mid);
        // right part
        build(2*node+2,mid+1,end);

        tree[node] = tree[2*node+1] + tree[2*node+2];
    }


    int query(int node, int start, int end, int left, int right){
        // case1 : not included range
        if(start>right || end<left)
        return 0;

        // case2 : fully included range
        if(start>=left && end<=right)
        return tree[node];

        // case3 : partially included - find in left child and right child
        int mid = start+(end-start)/2;
        int leftSum = query(2*node+1,start,mid,left,right);
        int rightSum = query(2*node+2,mid+1,end,left,right);

        return leftSum + rightSum;
    }


    void update(int node, int start, int end, int val, int index){
        // case1 : index not in range
        if(index<start || index>end)
        return;

        // case2 : index in range
        if(start == end){
            tree[node] = val;
            arr[index] = val;
            return;
        }

        tree[node] += (val-arr[index]);

        int mid = start+(end-start)/2;
        // update in left child
        update(2*node+1,start,mid,val,index);

        // update in right child
        update(2*node+2,mid+1,end,val,index);

    }
};


class NumArray {
public:

    SegmentTree *tree;
    int size;

    NumArray(vector<int>& nums) {
        size = nums.size();
        tree = new SegmentTree(nums);
    }
    
    void update(int index, int val) {
        tree->update(0,0,size-1,val,index);
    }
    
    int sumRange(int left, int right) {
        return tree->query(0,0,size-1,left,right);
    }
};
