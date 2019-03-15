#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <iterator>

using namespace std;

void addEdge(int a, int b, vector<vector<int>>* list)
{
	for (vector<int>::iterator i = (*list)[a].begin(); i != (*list)[a].end();++i)
		if (*i == b)return;
	if (a != b)
	{
		(*list)[a].push_back(b);
		(*list)[b].push_back(a);
	}
}

void addEdgeDirected(int a, int b, vector<vector<int>>* list)
{
	for (vector<int>::iterator i = (*list)[a].begin(); i != (*list)[a].end();++i)
		if (*i == b)return;
	if (a != b)(*list)[a].push_back(b);
}

void printGraph(vector<vector<int>> list)
{
	int count = 0;
	for (vector<vector<int>>::iterator i = list.begin(); i != list.end(); ++i)
	{
		cout << "The neighbours of node " << count << " are : ";
		if(list[count].size())
			for (vector<int>::iterator j = (*i).begin(); j != (*i).end(); ++j)
				cout << *j << " ";
		else cout << "No neighbours.";
		cout << endl;
		count++;
	}
}

vector<vector<int>> BFS(int root, vector<vector<int>> list)
{
	int n = list.size();
	vector<vector<int>> BFSTree(n), L(n + 1);
	vector<int> discovered(n,0);
	int layer = 0;

	L[0].push_back(root);
	discovered[L[0][0]] = 1;

	while (!L[layer].empty())
	{
		for (vector<int>::iterator i = list[L[layer][0]].begin(); i != list[L[layer][0]].end(); ++i)
		{
			if (!discovered[(*i)])
			{
				discovered[(*i)] = 1;
				addEdge((*i), L[layer][0], &BFSTree);
				L[layer + 1].push_back((*i));
			}
		}
		layer++;
	}
	return BFSTree;
}

vector<vector<int>> DFS(int root, vector<vector<int>> list)
{
	int n = list.size();
	vector<vector<int>> DFSTree(n);
	vector<int> explored(n, 0);
	vector<int> parent(n, -1);
	stack<int> S;
	int top;

	S.push(root);

	while (!S.empty())
	{
		top = S.top();
		if (!explored[top])
		{
			explored[top] = 1;
			if(top != root)addEdge(top, parent[top], &DFSTree);
			for (vector<int>::iterator i = list[top].begin(); i != list[top].end(); ++i)
			{
				if (!explored[(*i)])
				{
					parent[(*i)] = top;
					S.push((*i));
				}
			}
		}
		else S.pop();
	}
	return DFSTree;
}
