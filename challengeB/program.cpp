// AJ - Challenge B: Isomorphic Mapping

#include <bits/stdc++.h>



using namespace std;



// const ints:

 const size_t ALPH = 26;





// Function Declorations



bool is_iso(string &w1, string &w2) {

 

// length check

if (w1.length() != w2.length()) { return false; }


// map to store chr 1 and chr2

unordered_map<char, char> map;


// seen isntances of chrs

set<char> seen;


for (size_t i = 0; i < w1.size(); i++) {

char c1 = w1[i];

char c2 = w2[i];


// not iso

if (map.count(c1)) { if (map[c1] != c2) return false; 


} else { 


if (seen.count(c2)) return false;


map[c1] = c2;


seen.insert(c2);

}

   

}


return true;

}



int main() {

// freopen("input.txt", "r", stdin);

//   freopen("output.txt", "w", stdout);



string x, y;


while (cin >> x >> y) {

cout << (is_iso(x, y) ? "Isomorphic" : "Not Isomorphic") << endl;

}


return 0;

}


