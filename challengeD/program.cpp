// AJ Jones ChallengeD - Footballl Scores

#include <bits/stdc++.h>

using namespace std;



vector<vector<int>> freeman_glory(int a, vector<int> &scores) {


int n = scores.size();



vector<vector<int>> table(n + 1, vector<int>(a + 1, 0));



// base case: 1 way to reach 0

for (int i = 0; i <= n; i++) {

table[i][0] = 1;

}


  for (int i = 1; i < n + 1; i++) {

for (int j = 0; j < a + 1; j++) {


if ( scores[i - 1] <= j) {

table[i][j] = table[i][j - scores[i -1]] + table[i-1][j];

}

else {

table[i][j] = table[i-1][j];

}

}

}


return table;













}

void output_scores(int target, vector<int> &scores, vector<vector<int>> &table, vector<int> &curr, int index, vector<vector<int>> &u) {

// base case

if (target == 0) {

vector<int> temp = curr; // temp copy of curr

reverse(temp.begin(), temp.end()); // try reversing order



u.push_back(temp); 

return;

}




if (index == 0 || target < 0) return;



if (table[index -1][target] > 0) {

output_scores(target, scores, table, curr, index - 1,u);

}


if (target >= scores[index - 1] && table[index][target - scores[index -1]] > 0) {

curr.push_back(scores[index - 1]);

output_scores(target - scores[index - 1], scores, table, curr, index, u);

curr.pop_back();

}


}


int main() {

// freopen("input.txt", "r", stdin);

//    freopen("output.txt", "w", stdout);



    vector<int> scores = {2, 3, 7};



    int score;

    while (cin >> score) {

        vector<vector<int>> table = freeman_glory(score, scores);

        int numWays = table[scores.size()][score];



        if (numWays == 1) {

            cout << "There is 1 way to achieve a score of " << score << ":\n";

        } else {

            cout << "There are " << numWays << " ways to achieve a score of " << score << ":\n";

        }

        

vector<vector<int>> p;

        vector<int> curr;

        output_scores(score, scores, table, curr, scores.size(), p);


// sort from lecture to get desired output

        sort(p.begin(), p.end());

        for (const auto& sol : p) {

            for (int i = 0; i < (int)sol.size(); i++) {

                if (i > 0) cout << " ";

                cout << sol[i];

            }

            

cout << "\n";

        }

    }



    return 0;


}
