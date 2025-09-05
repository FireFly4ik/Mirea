#include <iostream>
#include <string>
#include <vector>

// number = 2 * number + term
void mul_add(int term, std::vector<int> &number) {
    int carry = term;
    for (auto &digit : number) {
        digit = 2 * digit + carry;
        carry = 0;
        if (digit >= 10) {
            digit -= 10;
            ++carry;
        }
    }
    if (carry != 0) {
        number.push_back(carry);
    }
}

int main() {
    std::string n1;
    std::cin >> n1;

    std::vector<int> n2 = {0};
    for (char c : n1) {
        mul_add(c - '0', n2);
    }

    for(auto it = n2.rbegin(); it != n2.rend(); ++it) {
        std::cout << *it;
    }
    std::cout << '\n';
}