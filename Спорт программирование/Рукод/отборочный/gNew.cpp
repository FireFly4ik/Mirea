#include <iostream>
#include <string>
#include <vector>
#include <numeric>

using namespace std;

bool creates_forbidden_pattern(const string& current_str, int pos, const string& q) {
    string last_digits;
    last_digits.reserve(q.length());

    for (int i = pos; i >= 0 && last_digits.length() < q.length(); --i) {
        if (isdigit(current_str[i])) {
            last_digits += current_str[i];
        }
    }
    reverse(last_digits.begin(), last_digits.end());

    return last_digits == q;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string q, s;
    cin >> q;
    cin.ignore(); 
    getline(cin, s);

    string digit_only_str;
    vector<int> digit_to_original_map;

    for (int i = 0; i < s.length(); ++i) {
        if (isdigit(s[i])) {
            digit_only_str += s[i];
            digit_to_original_map.push_back(i);
        }
    }

    vector<bool> is_crossed_out(s.length(), false);
    size_t start_pos = 0;
    while ((start_pos = digit_only_str.find(q, start_pos)) != string::npos) {
        for (size_t i = 0; i < q.length(); ++i) {
            is_crossed_out[digit_to_original_map[start_pos + i]] = true;
        }
        start_pos++;
    }

    string result = s;

    for (int i = 0; i < result.length(); ++i) {
        if (is_crossed_out[i]) {
            for (char d = '0'; d <= '9'; ++d) {
                bool is_leading_zero = (d == '0') && 
                                       (i == 0 || result[i - 1] == ' ') && 
                                       (i + 1 < result.length() && isdigit(result[i + 1]));
                if (is_leading_zero) {
                    continue;
                }

                result[i] = d;

                if (!creates_forbidden_pattern(result, i, q)) {
                    break; 
                }
            }
        }
    }

    cout << result << endl;

    return 0;
}