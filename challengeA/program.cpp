#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

int sunrise(const vector<int> &heights){
	int count =0;
	int maxh = -1;

	for(int i=(int)heights.size()-1; i >=0; i--){
		if(heights[i] > maxh){	
			count++;
			maxh = heights[i];
		}
	}
	
	return count;
}

int main(){
	string line;
	
	while(getline(cin, line)){

		if(line.empty()){
			continue;
		}
		stringstream ss(line);
		vector<int> heights;
		int h;
	
		while(ss >> h){
			heights.push_back(h);
		}
		int result = sunrise(heights);
		cout << result << '\n';
	}
	
	return 0;
}

