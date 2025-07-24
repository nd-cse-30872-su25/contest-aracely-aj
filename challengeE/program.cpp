#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

void findAPath(const vector<int>& tree, int target, int total, vector<int> path, int index, vector<vector<int>>& results){
	int left = 2 * index + 1;
	int right = 2 * index + 2;
	
	bool leaf = (left >= tree.size() || tree[left] == 0) && (right >= tree.size() || tree[right] == 0);

     if(total == target && leaf){
         results.push_back(path);
         return;
     }

     if(left < tree.size() && tree[left] != 0){
         if(total + tree[left] <= target){
             vector<int> newPath = path;
             newPath.push_back(tree[left]);
             findAPath(tree, target, total+ tree[left], newPath, left, results);
	     }
	}

     if(right < tree.size() && tree[right]!= 0){
         if(total + tree[right] <= target){
             vector<int> newPath = path;
             newPath.push_back(tree[right]);
             findAPath(tree, target, total + tree[right], newPath, right, results);
         }
     }
 }

int main(){
	string line;
	while(getline(cin, line)){
		if(line.empty()){
			continue;
        }

        int target = stoi(line);

		getline(cin, line);
		stringstream ss(line);
		vector<int> tree;
		int val;
		while(ss >> val){
			tree.push_back(val);
		}

		vector<vector<int>> results;
		if(!tree.empty() && tree[0] != 0){
			findAPath(tree, target, tree[0], {tree[0]}, 0, results);
		}
	
		sort(results.begin(), results.end());

		if(results.empty()){
			cout << target << ":" << endl;
		}
		else{
			for(const auto& path : results){
				cout << target << ":";
				for(size_t i=0; i< path.size(); i++){
                     cout << (i ? ", " : " ") << path[i];
                 }
                 cout << endl;
             }
         }
     }

     return 0;
 }

