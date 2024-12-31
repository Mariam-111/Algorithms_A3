#include <bits/stdc++.h>
#define l '\n'
#include <sstream>
#include <algorithm>

using namespace std;

vector<int> Fill_From_Input(const string& input) {  // Function to parse input strings of the format "g = [1,2,3]" as the assignment saiddddd
    vector<int> result;
    size_t start = input.find('[');
    size_t end = input.find(']');
    string numbers = input.substr(start + 1, end - start - 1);
    stringstream ss(numbers);
    string num;

    while (getline(ss, num, ',')) {
        result.push_back(stoi(num));  //string to int
    }

    return result;
}

int Cookies_and_childss(vector<int>& g, vector<int>& s) {
    sort(g.begin(), g.end()); // Sort greed factors and cookie sizes
    sort(s.begin(), s.end());

    int i = 0, j = 0; // Pointers for g and s --> Cookies and childss
    int Number_of_children = 0;

    while (i < g.size() && j < s.size()) {
        if (s[j] >= g[i]) { // Cookie can satisfy the child
            Number_of_children++;
            i++; // Move to the next child
        }
        j++; // Move to the next cookie
    }

    return Number_of_children;
}

int main() {

    string inputLine;
    getline(cin, inputLine); // Read the single-line input
    size_t commaPos = inputLine.find(", s = "); // Split the input into parts for g and s
    string gInput = inputLine.substr(0, commaPos);
    string sInput = inputLine.substr(commaPos + 6); // +6 --> to skip 6 chars after (,) so it will get [1,3,2]

    vector<int> g = Fill_From_Input(gInput);
    vector<int> s = Fill_From_Input(sInput);

    // Compute and output the result
    int result = Cookies_and_childss(g, s);
    cout  << result << l;

    return 0;
}
