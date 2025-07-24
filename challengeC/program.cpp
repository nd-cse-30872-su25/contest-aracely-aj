#include <iostream>
#include <vector>
#include <string>

using namespace std;

int leftPossibilities(const vector<int>& nums, const vector<char>& op){
    int result =nums[0];
    for(int i=0; i<3; i++){
        if (op[i] == '+'){
			result += nums[i +1];
		}
        else if (op[i] == '-'){
			result -= nums[i+ 1];
		}
        else{
			result *= nums[i+1];
		}
    }
    return result;
}

int rightPossibilities(const vector<int>& nums, const vector<char>& op){
    int result= nums[8];
    for(int i=7; i>= 4; i--){
        if(op[i] == '+'){
			result= nums[i]+ result;
		}
        else if (op[i] == '-'){
			result= nums[i]- result;
		}
        else{
			result= nums[i]* result;
		}
    }
    return result;
}

string leftPart(const vector<int>& nums, const vector<char>& op){
    string prt1= "("+ to_string(nums[0])+ " "+ op[0]+ " "+ to_string(nums[1])+ ")";
    for(int i=1; i<3; i++){
        prt1= "("+ prt1+ " " +op[i]+ " "+ to_string(nums[i +1])+ ")";
	}
    return prt1;
}

string rightPart(const vector<int>& nums, const vector<char>& op){
    string prt2= to_string(nums[8]);
    for (int i=7; i>=4; i--){
        prt2= "("+ to_string(nums[i])+ " "+ op[i]+ " "+ prt2+ ")";
	}
    return prt2;
}

void findSolution(int target){
    vector<int> nums= {9,8,7,6,5,4,3,2,1};
    vector<char> opList= {'+','-','*'};
    vector<char> finalOp(8);

    for(int i=0; i< 6561; i++){
        int n = i;
        for(int j=0; j<8; j++){
            finalOp[j]= opList[n%3];
            n /= 3;
        }

        int left = leftPossibilities(nums, finalOp);
        int right= rightPossibilities(nums,finalOp);
        int result;
        if(finalOp[3] == '+'){
			result = left+ right;
		}
        else if(finalOp[3]== '-'){
			result= left- right;
		}
        else{
			result= left* right;
		}

        if(result == target){
            string fullResult = leftPart(nums, finalOp) + " " + finalOp[3] + " " + rightPart(nums, finalOp);
            cout << fullResult << " = " << target << '\n';
			return;
        }
    }
}

int main(){
    int target;
    while(cin >> target){
    	findSolution(target);
	}
    return 0;
}


