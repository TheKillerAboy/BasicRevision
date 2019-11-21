#include <iostream>
#include <vector>
#include <climits>

using namespace std;

#define INF INT_MAX

int W,H;
vector<vector<bool>> marked;
vector<vector<bool>> canMark;

inline bool cellMarked(int i, int j){
	return (i>=W || j>=H || i<0 || j<0) ? true : marked[i][j];
}

inline bool canMarkCell(int i, int j){
	return cellMarked(i,j) && cellMarked(i,j+1) && cellMarked(i,j+2) && cellMarked(i+1,j+1) && cellMarked(i-1,j+1);
}

int main(){
	cin>>W>>H;
	string line;
	marked.resize(W,vector<bool>(H));
	canMark.resize(W,vector<bool>(H));
	for(int i = 0; i < H; ++i){
		cin>>line;
		for(int j = 0; j < W; ++j){
			marked[j][i] = line[j] == '#';
		}
	}
	for(int i = 0; i < H; ++i){
		for(int j = 0; j < W; ++j){
			canMark[j][i] = canMarkCell(j,i);
		}
	}
	int stampMask = 1 | (1<<W) | (1<<(W-1)) | (1<<(W+1)) | (1<<(2*W));
	vector<vector<int>> dpI(W*H+1,vector<int>(1<<(2*W),INF));
	dpI[0][0] = 0;
	int curCell = -1;
	int nxtCell;
	int nxtMask;
	for(int i = 0 ; i < H; ++i){
		for(int j = 0; j < W; ++j){
			curCell++;
			nxtCell = curCell + 1;
			for(int mask = 0; mask < (1<<(2*W)); mask++){
				if(dpI[curCell][mask] < INF){
					if(canMark[j][i]){
						nxtMask = (mask | stampMask) >> 1;
						dpI[nxtCell][nxtMask] = min(dpI[nxtCell][nxtMask],dpI[curCell][mask]+1);
					}
					if(!canMark[j][i] || mask & 1){
						nxtMask = mask>>1;
						dpI[nxtCell][nxtMask] = min(dpI[nxtCell][nxtMask],dpI[curCell][mask]);
					}
				}
			}
		}
	}
}