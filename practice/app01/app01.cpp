#include <iostream>
#include <stack>
#include <string>
#include <cctype>

using namespace std;

// 허용된 문자 검사
bool isValidChar(char c) {
    return isdigit(c) || c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')';
}

// 괄호 검사
bool checkParentheses(const string& s) {
    stack<char> st;
    for (char c : s) {
        if (c == '(') st.push(c);
        else if (c == ')') {
            if (st.empty()) return false;
            st.pop();
        }
    }
    return st.empty();
}

// 전체 수식 검사 (핵심)
bool isValidExpression(const string& s) {
    if (s.empty()) return false;

    char prev = 0; // 이전 문자

    for (int i = 0; i < s.size(); i++) {
        char curr = s[i];

        // 1. 허용되지 않은 문자
        if (!isValidChar(curr)) return false;

        // 2. 연산자 검사
        if (curr == '+' || curr == '-' || curr == '*' || curr == '/') {
            // 맨 앞 or 맨 뒤에 오면 안됨
            if (i == 0 || i == s.size() - 1) return false;

            // 이전이 연산자면 안됨
            if (prev == '+' || prev == '-' || prev == '*' || prev == '/')
                return false;

            // 바로 다음도 연산자면 안됨
            char next = s[i + 1];
            if (next == '+' || next == '-' || next == '*' || next == '/')
                return false;

            // ( 다음에 연산자 오는 것도 금지 → "(+3)" 같은거
            if (prev == '(') return false;

            // 연산자 다음에 ')' 오는 것도 금지 → "3+)"
            if (next == ')') return false;
        }

        // 3. '(' 다음 검사
        if (curr == '(') {
            // 바로 뒤가 연산자면 안됨
            if (i + 1 < s.size()) {
                char next = s[i + 1];
                if (next == '+' || next == '*' || next == '/')
                    return false;
            }
        }

        // 4. ')' 앞 검사
        if (curr == ')') {
            // 바로 앞이 연산자면 안됨
            if (prev == '+' || prev == '-' || prev == '*' || prev == '/')
                return false;
        }

        prev = curr;
    }

    // 5. 괄호 짝 검사
    if (!checkParentheses(s)) return false;

    return true;
}

int main() {
    string input;
    cin >> input;

    if (isValidExpression(input)) {
        cout << "올바른 수식입니다!" << endl;
    }
    else {
        cout << "잘못된 수식입니다!" << endl;
    }

    return 0;
}