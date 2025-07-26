#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

struct FamilyTree {
    unordered_map<string, vector<string>> parentToChildren;
    unordered_map<string, vector<string>> childToParents;
    unordered_map<string, string> spouses;
};

void parseFamilyLine(const string& line, FamilyTree& tree){
    stringstream ss(line);
    vector<string> parents;
    string token;

    // Read parents
    while (ss >> token && token.back() != ':'){
        parents.push_back(token);
    }

    if (token.empty() || token.back() != ':'){
        return;
    }
	
	//remove : 
    token.pop_back();
    parents.push_back(token);

    //spouses
    if (parents.size() == 2) {
        tree.spouses[parents[0]] = parents[1];
        tree.spouses[parents[1]] = parents[0];
    }

    //The children
    vector<string> children;
    while (ss >> token) {
        children.push_back(token);
    }

    for (const string& parent : parents){
        for (const string& child : children){
            tree.parentToChildren[parent].push_back(child);
            tree.childToParents[child].push_back(parent);
        }
    }
}

set<string> getNiblings(const string& person, const FamilyTree& tree) {
    set<string> niblings;
    set<string> siblingsToConsider;

    //siblings
    auto cp = tree.childToParents.find(person);
    if (cp != tree.childToParents.end()) {
        for (const string& parent : cp->second) {
            auto ptc = tree.parentToChildren.find(parent);
            if (ptc != tree.parentToChildren.end()) {
                for (const string& child : ptc->second) {
                    if (child != person) siblingsToConsider.insert(child);
                }
            }
        }
    }

    //spouse's siblings
    auto sp = tree.spouses.find(person);
    if (sp != tree.spouses.end()) {
        string spouse = sp->second;
        auto scp = tree.childToParents.find(spouse);
        if (scp != tree.childToParents.end()) {
            for (const string& parent : scp->second) {
                auto ptc = tree.parentToChildren.find(parent);
                if (ptc != tree.parentToChildren.end()) {
                    for (const string& child : ptc->second) {
                        if (child != spouse) siblingsToConsider.insert(child);
                    }
                }
            }
        }
    }

    //children of siblings
    for (const string& sibling : siblingsToConsider) {
        auto ptc = tree.parentToChildren.find(sibling);
        if (ptc != tree.parentToChildren.end()) {
            for (const string& child : ptc->second) {
                niblings.insert(child);
            }
        }
    }

    return niblings;
}

void processGiftGivers(const vector<string>& givers, const FamilyTree& tree) {
    for (const string& giver : givers) {
        set<string> niblings = getNiblings(giver, tree);

        if (niblings.empty()) {
            cout << giver << " does not need to buy gifts" << endl;
        } else {
            vector<string> sorted(niblings.begin(), niblings.end());
            sort(sorted.begin(), sorted.end());

            cout << giver << " needs to buy gifts for: ";
            for (size_t i = 0; i < sorted.size(); ++i) {
                if (i > 0) cout << ", ";
                cout << sorted[i];
            }
            cout << endl;
        }
    }
}

int main() {
    string line;

    while (true) {
        // Skip blank lines
        do {
            if (!getline(cin, line)) return 0;
        } while (line.empty());

        if (line == "0") break;

        int numFamilies;
        try {
            numFamilies = stoi(line);
        } catch (...) {
            continue;
        }

        FamilyTree tree;

        for (int i = 0; i < numFamilies; ++i) {
            if (!getline(cin, line)) return 1;
            parseFamilyLine(line, tree);
        }

        // Read num of gift givers
        do {
            if (!getline(cin, line)) return 1;
        } while (line.empty());

        int numGivers;
        try {
            numGivers = stoi(line);
        } catch (...) {
            continue;
        }

        vector<string> givers;
        for (int i = 0; i < numGivers;i++) {
            if (!getline(cin, line)) return 1;
            givers.push_back(line);
        }

        processGiftGivers(givers, tree);

    }

    return 0;
}

