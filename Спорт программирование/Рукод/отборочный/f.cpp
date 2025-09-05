#include <iostream>
#include <vector>
using namespace std;

using ll = long long;
using matrix = vector<vector<ll>>;

const int MOD = 1e9 + 7;
const int MATRIX_SIZE = 4;

matrix multiply(const matrix& a, const matrix& b) {
    matrix result(MATRIX_SIZE, vector<ll>(MATRIX_SIZE, 0));

    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            for (int k = 0; k < MATRIX_SIZE; ++k) {
                result[i][j] = (result[i][j] + a[i][k] * b[k][j]) % MOD;
            }
        }
    }
    return result;
}

matrix power(matrix base, ll p) {
    matrix result(MATRIX_SIZE, vector<ll>(MATRIX_SIZE, 0));
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        result[i][i] = 1;
    }

    while (p > 0) {
        if (p % 2 == 1) {
            result = multiply(result, base);
        }
        base = multiply(base, base);
        p /= 2;
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n;
    cin >> n;

    matrix M = {
        {0, 10, 10, 10},
        {20, 0, 0, 0},
        {1, 0, 0, 0},
        {0, 2, 0, 0}
    };

    vector<ll> s1 = {10, 20, 1, 0};

    matrix m_final = power(M, n - 1);

    ll total_passwords = 0;
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        ll current_state_count = 0;
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            current_state_count = (current_state_count + m_final[i][j] * s1[j]) % MOD;
        }
        total_passwords = (total_passwords + current_state_count) % MOD;
    }

    cout << total_passwords << endl;

    return 0;
}