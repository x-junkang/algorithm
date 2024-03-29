#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;

//划分——每次划分唯一确定一个元素位置
int split(int A[], int low, int high)
{
    int pivot = A[low]; //以第1个位置为基准
    while (low < high)
    {
        while (low < high && A[high] >= pivot)
        {
            --high;
        }
        A[low] = A[high]; //将比基准小的元素移动到左端
        while (low < high && A[low] <= pivot)
        {
            ++low;
        }
        A[high] = A[low]; //将比基准小的元素移动到右端
    }
    A[low] = pivot;
    return low;
}

int r = 5;
//A[low..high]
int select_rank_k(int A[], int low, int high, int k)
{
    int r_group = ceil((high - low + 1) * 1.0 / r); //ceil取上限，总共分为r_group个组
    //计算每个分组中值，存于A[]最前面
    for (int i = 1; i <= r_group; ++i)
    {
        sort(&A[low + (i - 1) * r], &A[(low + i * r - 1) > high ? high : (low + i * r - 1)]);
        swap(A[low + i - 1], A[low + (i - 1) * r + r / 2]);
    }
    //获得每个组的中值的中值(并置于A[low]位置，方便调用快排划分函数)
    sort(&A[low], &A[low + r_group]);
    swap(A[low], A[r_group / 2]);
    int cur = split(A, low, high);
    if (cur == k - 1)
    {
        return A[cur];
    }
    else if (cur < k)
    {
        return select_rank_k(A, cur + 1, high, k);
    }
    else
    {
        return select_rank_k(A, low, cur - 1, k);
    }
}

int main(void)
{
    int A[15] = {4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 10, 11, 12, 13, 14};
    printf("The kth element is : %d\n", select_rank_k(A, 0, 14, 7));
    return 0;
}
