/*

https://www.geeksforgeeks.org/problems/range-minimum-query/1

*/


class SegmentTree{
    public :
    int *tree, *arr;
    int size;
    
    SegmentTree(int input[],int n){
        size = n;
        arr = input;
        tree = new int[4*size];
        
        build(0,0,size-1);
    }
    
    void build(int node, int start, int end){
        if(start == end){
            tree[node] = arr[start];
            return;
        }
        
        int mid = start+(end-start)/2;
        build(2*node+1,start,mid);
        build(2*node+2,mid+1,end);
        
        tree[node] = min(tree[2*node+1],tree[2*node+2]);
    }
    
    
    int query(int node, int start, int end, int left, int right){
        // no overlap
        if(start>right || end<left)
        return INT_MAX;
        
        // fully overlap
        if(start>=left && end<=right)
        return tree[node];
        
        // partially overlap
        int mid = start+(end-start)/2;
        int l = query(2*node+1,start,mid,left,right);
        int r = query(2*node+2,mid+1,end,left,right);
        
        return min(l,r);
    }
};

SegmentTree *tree;

int *constructST(int arr[],int n)
{
  tree = new SegmentTree(arr,n);
  return tree->tree;
}


int RMQ(int st[] , int n, int a, int b)
{
    return tree->query(0,0,n-1,a,b);
}

