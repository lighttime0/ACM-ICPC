//思路：先以最左下角的点为(0,0)，复原每个点的坐标，然后进行坐标变换。

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int MAXN = 21;

struct NODE {
	int x;
	int y;
};

NODE FBT[1<<MAXN];					//Array index start from 1, not 0

int main()
{
	int N, M, i;
	scanf("%d %d",&N,&M);
	int node_count = (1 << N) - 1;
	int FBT_height = 2, FBT_weight = 5;				//Weight of full binary tree: 1, 5, 5*2+1=11, 11*2+1=23, ...
	if (N == 1)
	{
		FBT_height = 0;
		FBT_weight = 1;
	}
	else
	{
		for (i = 2; i < N; ++i)
		{
			FBT_weight = FBT_weight * 2 + 1;
			FBT_height = FBT_height * 2 + 1;
		}
	}

	int index, start_index, end_index, start_x, start_y;
	start_index = 1 << (N - 1);
	end_index = (1 << N)  - 1;
	start_x = 0;
	start_y = 0;
	for (index = start_index; index <= end_index; index += 2)
	{
		FBT[index].x = start_x;
		FBT[index].y = start_y;
		FBT[index+1].x = start_x;
		FBT[index+1].y = start_y + 4;
		start_y += 6;
	}

	int lc, rc;
	for (index = (1 << (N - 1)) - 1; index >= 1; --index)
	{
		lc = index * 2;
		rc = index * 2 + 1;	
		FBT[index].x = FBT[lc].x + ((FBT[rc].y - 1) - FBT[lc].y) / 2 + 1;
		FBT[index].y = (FBT[lc].y + FBT[rc].y) / 2;
	}

	//Coordinate change
	for (index = 1; index <= node_count; ++index)
	{
		//printf("%d %d ", FBT[index].x, FBT[index].y);
		FBT[index].x = (FBT_height - FBT[index].x);
		FBT[index].y -= FBT_weight / 2;
		//printf("\t%d %d\n", FBT[index].x, FBT[index].y);
	}

	int query;
	NODE lt, rb;
	for (query = 0; query < M; ++query)
	{
		scanf("%d %d %d %d", &lt.x, &lt.y, &rb.x, &rb.y);
		int ans = 0;
		for (i = 1; i <= node_count; ++i)
			if (FBT[i].x >= lt.x && FBT[i].y >= lt.y && FBT[i].x <= rb.x && FBT[i].y <= rb.y)
				++ans;
		printf("%d\n", ans);
	}

	return 0;
}
