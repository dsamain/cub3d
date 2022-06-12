#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef long long ll;

int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};

void dfs(vector<vector<int> > &grid, int u, int v, int ord) {
	if (u == 0 || v == 0 || u == grid.size()-1 || v == grid.size()-1 || !grid[u][v])
		return ;

	if (!grid[u+1][v] + !grid[u-1][v] + !grid[u][v+1] + !grid[u][v-1] > 1)
		return ;

	grid[u][v] = 0;

	if (rand() % 10 * (ord+1) == 0 && ord != 4) return ;
	
	vector<int> dir(4);
	for (int i = 0; i < 4; i++) dir[i] = i;

	while (dir.size()) {
		int i = rand() % dir.size();
		int d = dir[i];
		swap(dir[i], dir[dir.size()-1]);
		dir.pop_back();
		dfs(grid, u+dy[d], v+dx[d], 4 - dir.size());
	}
}


int main(int ac, char **av) {
	if (ac != 3) return 0;
	int n = atoi(av[1]), m = atoi(av[2]);
	if (n < 3 || m < 3) return 0;
	vector<vector<int> > grid(n, vector<int>(m, 1));
	dfs(grid, 1,1, 4);

	cout << "NO textures/redbrick.xpm\nSO textures/redbrick.xpm\nWE textures/redbrick.xpm\nEA textures/redbrick.xpm\nC 1,2,3\nF 1,2,3\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << grid[i][j];
		}
		cout << endl;
	}
}