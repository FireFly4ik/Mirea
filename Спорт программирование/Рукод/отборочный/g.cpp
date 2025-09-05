#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

bool creates_forbidden_pattern_around(const string& current_str, int changed_pos, const string& q) {
    for (int k = 0; k < q.length(); ++k) {
        int start_scan_pos = changed_pos;
        int digits_to_go_back = k;

        while (digits_to_go_back > 0) {
            start_scan_pos--;
            if (start_scan_pos < 0) break;
            if (isdigit(current_str[start_scan_pos])) {
                digits_to_go_back--;
            }
        }
        
        if (digits_to_go_back > 0 || start_scan_pos < 0) {
            continue;
        }

        string candidate;
        candidate.reserve(q.length());
        int current_pos = start_scan_pos;
        
        while (candidate.length() < q.length() && current_pos < current_str.length()) {
            if (isdigit(current_str[current_pos])) {
                candidate += current_str[current_pos];
            }
            current_pos++;
        }
        
        if (candidate == q) {
            return true;
        }
    }
    
    return false;
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
                if (d == '0') {
                    bool is_start_of_number = (i == 0 || result[i - 1] == ' ');
                    if (is_start_of_number) {
                        bool has_another_digit = false;
                        for (int j = i + 1; j < result.length(); ++j) {
                            if (result[j] == ' ') {
                                break;
                            }
                            if (isdigit(result[j]) || is_crossed_out[j]) {
                                has_another_digit = true;
                                break;
                            }
                        }
                        if (has_another_digit) {
                            continue;
                        }
                    }
                }

                result[i] = d;

                if (!creates_forbidden_pattern_around(result, i, q)) {
                    break; 
                }
            }
        }
    }

    cout << result << endl;

    return 0;
}