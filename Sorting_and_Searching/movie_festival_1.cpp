#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

bool cmp(pair<int,int> & a, pair<int,int> & b)
{
	return a.second < b.second;
}

int main() {
	int n;
	cin >> n;

	vector<pair<int,int>> intervals(n);

	for (int i=0; i<n; i++)
		cin >> intervals[i].first >> intervals[i].second;

	sort(begin(intervals), end(intervals), cmp);

	int i = 0;
	int endLastMovie = -1;
	int movies = 0;
	while (i < n) {
		if (intervals[i].first >= endLastMovie)
		{
			movies++;
			endLastMovie = intervals[i].second;
			i++;
		} else {
			i++;
		}
	}
	cout << movies;
}