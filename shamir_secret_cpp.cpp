#include <bits/stdc++.h>
using namespace std;

#define int64 __int128

struct Share {
    int64 x;
    string y_expr;
    int64 y;
};

// Convert string to int64 (supporting very big numbers)
int64 toInt128(const string &s) {
    int64 res = 0;
    for (char c : s) if (isdigit(c)) res = res * 10 + (c - '0');
    return res;
}

// Convert int64 back to string for output
string to_string(int64 num) {
    if (num == 0) return "0";
    string s;
    while (num > 0) {
        s += (char)('0' + num % 10);
        num /= 10;
    }
    reverse(s.begin(), s.end());
    return s;
}

// Evaluate expressions like sum(a,b), multiply(a,b)
int64 evaluate(const string &expr) {
    string op;
    vector<int64> args;
    string token;
    for (char ch : expr) {
        if (isalpha(ch)) op += ch;
        else if (isdigit(ch)) token += ch;
        else if (ch == ',' || ch == ')') {
            if (!token.empty()) {
                args.push_back(toInt128(token));
                token = "";
            }
        }
    }
    if (op == "sum") return args[0] + args[1];
    if (op == "multiply") return args[0] * args[1];
    if (op == "subtract") return args[0] - args[1];
    if (op == "divide") return args[0] / args[1];
    return toInt128(expr); // in case it's a number
}

// Extended Euclidean algorithm to find modular inverse
int64 gcdExtended(int64 a, int64 b, int64 &x, int64 &y) {
    if (a == 0) {
        x = 0, y = 1;
        return b;
    }
    int64 x1, y1;
    int64 gcd = gcdExtended(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return gcd;
}

int64 modInverse(int64 a, int64 m) {
    int64 x, y;
    gcdExtended(a, m, x, y);
    return (x % m + m) % m;
}

// Lagrange Interpolation to compute P(0)
int64 lagrangeInterpolation(vector<pair<int64, int64>> points, int64 MOD) {
    int64 result = 0;
    int k = points.size();

    for (int i = 0; i < k; ++i) {
        int64 xi = points[i].first;
        int64 yi = points[i].second;
        int64 num = 1, den = 1;
        for (int j = 0; j < k; ++j) {
            if (j == i) continue;
            int64 xj = points[j].first;
            num *= -xj;
            den *= (xi - xj);
        }
        int64 inv = modInverse(den, MOD);
        int64 term = (yi * num % MOD) * inv % MOD;
        result = (result + term + MOD) % MOD;
    }
    return result;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<Share> shares(n);

    for (int i = 0; i < n; ++i) {
        string x_str, y_expr;
        cin >> x_str >> y_expr;
        shares[i].x = toInt128(x_str);
        shares[i].y_expr = y_expr;
        shares[i].y = evaluate(y_expr);
    }

    map<int64, int> secretFrequency;
    map<int64, vector<vector<int>>> combMap;
    int64 MOD = (int64)1e20 + 7; // Big prime for modular arithmetic

    // Generate all combinations of k shares
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);

    vector<vector<int>> validCombinations;

    for (int i = 0; i < (1 << n); ++i) {
        if (__builtin_popcount(i) != k) continue;
        vector<pair<int64, int64>> points;
        vector<int> comb;
        for (int j = 0; j < n; ++j) {
            if (i & (1 << j)) {
                points.push_back({shares[j].x, shares[j].y});
                comb.push_back(j);
            }
        }
        int64 s = lagrangeInterpolation(points, MOD);
        secretFrequency[s]++;
        combMap[s].push_back(comb);
    }

    // Find the most frequent secret
    int64 finalSecret = 0;
    int maxFreq = 0;
    for (auto &p : secretFrequency) {
        if (p.second > maxFreq) {
            maxFreq = p.second;
            finalSecret = p.first;
        }
    }

    // Mark corrupted shares
    set<int> correctIndexes;
    for (auto &c : combMap[finalSecret])
        for (int id : c)
            correctIndexes.insert(id);

    vector<int> corrupted;
    for (int i = 0; i < n; ++i) {
        if (correctIndexes.find(i) == correctIndexes.end())
            corrupted.push_back(i + 1); // 1-based
    }

    // Output JSON
    cout << "{\n  \"secret\": \"" << to_string(finalSecret) << "\",\n";
    cout << "  \"corrupted_shares\": [";
    for (size_t i = 0; i < corrupted.size(); ++i) {
        cout << corrupted[i];
        if (i + 1 != corrupted.size()) cout << ", ";
    }
    cout << "]\n}" << endl;
    return 0;
}
