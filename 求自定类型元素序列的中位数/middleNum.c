#include <stdio.h>

#define DEBUG 1
#define MAXN 10
typedef int ElementType;

ElementType Median( ElementType A[], int N );

int main ()
{
	ElementType A[MAXN];
	int N, i;

	scanf("%d", &N);
	for ( i = 0; i < N; i++ )
		scanf("%d", &A[i]);
	printf("%d\n", Median(A, N));

	return 0;
}

void HeapAdjust(ElementType A[], int x, int len)
{
	ElementType temp = A[x];
	for(int j = 2 * x + 1; j < len; j = 2 * j + 1)
	{
		if(j + 1 < len && A[j] < A[j + 1])
			j++;
		if(temp > A[j])
			break;
		A[x] = A[j];
		x = j;
	}
	A[x] = temp;
}
ElementType Median( ElementType A[], int N )
{
	// 构建初始堆
	for(int i = N / 2 - 1; i >= 0; i--)
	{
		HeapAdjust(A, i, N);
	}
	// 堆调整、交换元素
	for(int i = N - 1; i > 0; i--)
	{
		ElementType temp = A[0];
		A[0] = A[i];
		A[i] = temp;
		HeapAdjust(A, 0, i);
	}
#if DEBUG
	for(int i = 0; i < N; i++)
	{
		printf("%d ", A[i]);
	}
#endif // DEBUG
	return A[N / 2];
}

// 二分插入排序
/*for(int i = 1; i < N ; i++)
{
	int temp = A[i];
	int left = 0;
	int right = i - 1;
	while(left <= right)
	{
		int middle = (left + right) / 2;
		if(temp > A[middle])
		{
			left = middle + 1;
		}
		else
		{
			right = middle - 1;
		}
	}
	for(int j = i - 1; j >= right; j--)
	{
		A[j + 1] = A[j];
	}
	A[right + 1] = temp;
	for(int i = 0; i < N; i++)
	{
		printf("%d ", A[i]);
	}
	puts("");
}*/

// 快排
/*
void qs(int l, int r, ElementType *A)
{
	if(l >= r)
	{
		return;
	}
	int temp = A[l];
	int i = l, j = r;
	while(i != j)
	{
		while(A[j] >= temp && j > i)
		{
			j--;
		}
		while(A[i] <= temp && i < j)
		{
			i++;
		}
		if(l < r)
		{
			ElementType ps = A[i];
			A[i] = A[j];
			A[j] = ps;
		}
	}
	A[l] = A[i];
	A[i] = temp;
	qs(l, i - 1, A);
	qs(i + 1, r, A);
}

qs(0, N - 1, A);
	for(int i = 0; i < N; i++)
	{
		printf("%d ", A[i]);
	}
	puts("");
*/

/*	选择排序
 for(int i=0;i<N;i++)
    {
        int k=i;
        for(int j=i;j<N;j++)
        {
          if(A[k]>A[j])
          {
            k=j;
          }
        }
        if(i != k)
        {
          ElementType temp=A[i];
          A[i]=A[k];
          A[k]=temp;
        }
    }
*/
/*	冒泡排序
 int flag=1;
    for(int i=0;i<N-1 && flag;i++)
    {
      flag=0;
      for(int j=1;j<N-i;j++)
      {
        if(A[j]<A[j-1])
        {
          ElementType temp=A[j];
          A[j]=A[j-1];
          A[j-1]=temp;
          flag=1;
        }
      }
    }
    */
