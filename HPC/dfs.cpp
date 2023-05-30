#include<bits/stdc++.h>
#include<omp.h>

using namespace std;

int main(){
	int n;
	cin >> n;
	vector<int> v[n];

	int e;
	cin >> e;
	for(int i=0;i<e;i++){
		int a,b;
		cin >> a >> b;
		v[a].push_back(b);
		v[b].push_back(a);
	}
	int viz[n] = {0};
	stack<int> q;
	q.push(0);
	while(!q.empty()){
		int x = q.top();
		cout << x << " ";
		viz[x] = 1;
		q.pop();
		#pragma omp parallel for shared(v,viz,q) schedule(dynamic)
		for(auto h:v[x]){
			if(viz[h] == 0){
				q.push(h);
			}
		}
	}
	cout << endl;

	return 0;
}