// AJ Jones ChallengeF: Matrix

#include <bits/stdc++.h>



using namespace std;



typedef vector<vector<int>> Matrix;



// reads a matrix from input

Matrix read_matrix(int m, int n) { 



Matrix matrix(m, vector<int>(n));

    for (int i = 0; i < m; i++)

        for (int j = 0; j < n; j++)

            cin >> matrix[i][j];

    

return matrix;

}



int wrap(int index, int m) { // modular arithmatic 4 wrapping

if (index < 0) return m - 1;

if (index >= m) return 0;

  return index;

}





void compute_min_path(const Matrix& matrix, Matrix& dp, Matrix& prev) {

int m = matrix.size();

    int n = matrix[0].size();



   // initialize first col

    for (int i = 0; i < m; i++)

        dp[i][0] = matrix[i][0];



    // fill DP + backtrack 

    for (int j = 1; j < n; j++) {

        for (int i = 0; i < m; i++) {

            for (int d = -1; d <= 1; d++) {

                int prev_row = wrap(i + d, m);

                int cost = dp[prev_row][j - 1] + matrix[i][j];

                if (cost < dp[i][j] || (cost == dp[i][j] && prev_row < prev[i][j])) {

                    dp[i][j] = cost;

                    prev[i][j] = prev_row;

                }

            }

        }

    }

}



// finds min end row and cost in last column of dp table

pair<int, int> find_min_end_row(const Matrix& dp) {

int m = dp.size(), n = dp[0].size();

    int min_cost = INT_MAX; 

int end_row = 0;



    for (int i = 0; i < m; i++) {

        if (dp[i][n - 1] < min_cost) {

            min_cost = dp[i][n - 1];

            end_row = i;

        }

    }

    return make_pair(min_cost, end_row);

}





vector<int> reconstruct_path(const Matrix& prev, int end_row) {

int n = prev[0].size();

    vector<int> path(n);

    int row = end_row;

    for (int j = n - 1; j >= 0; j--) {

        path[j] = row;

        row = prev[row][j];

   }

    return path;

}



// one matrix input, process and output

void process_matrix(int m, int n) {

Matrix matrix = read_matrix(m, n);

    Matrix dp(m, vector<int>(n, INT_MAX));

    Matrix prev(m, vector<int>(n, -1));



    compute_min_path(matrix, dp, prev);



    pair<int, int> result = find_min_end_row(dp);

    int min_cost = result.first;

    int end_row = result.second;



    vector<int> path = reconstruct_path(prev, end_row);



    // output

    cout << min_cost << endl;

    for (size_t i = 0; i < path.size(); ++i) {

        cout << (path[i] + 1);

        if (i + 1 < path.size())

            cout << " ";

    }

    cout << endl;



}





int main() {

//    freopen("input.txt", "r", stdin);

//    freopen("output.txt", "w", stdout);



int m, n;

    while (cin >> m >> n) {

        process_matrix(m, n);

    }

    

return 0;

}




