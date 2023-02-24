#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int BASE = 256;
const int MOD = 1e9 + 7;

vector<int> RabinKarp(const string& base, const string& pattern) {
    vector<int> matches;
    int baseLen = base.length();
    int patLen = pattern.length();
    int baseHash = 0, patHash = 0;
    int h = 1;

    for (int i = 0; i < patLen - 1; ++i)
        h = (h * BASE) % MOD;

    for (int i = 0; i < patLen; ++i) {
        baseHash = (BASE * baseHash + base[i]) % MOD;
        patHash = (BASE * patHash + pattern[i]) % MOD;
    }

    for (int i = 0; i <= baseLen - patLen; ++i) {
        if (baseHash == patHash) {
            bool match = true;
            for (int j = 0; j < patLen; ++j) {
                if (base[i+j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match)
                matches.push_back(i);
        }
        if (i < baseLen - patLen) {
            baseHash = (BASE * (baseHash - h * base[i]) + base[i+patLen]) % MOD;
            if (baseHash < 0)
                baseHash += MOD;
        }
    }

    return matches;
}

int main() {
    string base, pattern;

    cout << "Enter the base string: ";
    getline(cin, base);

    cout << "Enter the pattern string: ";
    getline(cin, pattern);

    vector<int> matches = RabinKarp(base, pattern);

    if (matches.empty()) {
        cout << "Pattern not found in base string" << endl;
    } else {
        cout << "Pattern found at indices: ";
        for (int i : matches)
            cout << i << " ";
        cout << endl;
    }

    return 0;
}

