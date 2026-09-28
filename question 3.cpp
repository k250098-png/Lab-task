#include <iostream>
#include <string>
using namespace std;

#define MAX 100

class StringStack {
    int top;
    string a[MAX];
public:
    StringStack() { top = -1; }
    
    bool push(string x) {
        if (top >= (MAX - 1)) {
            cout << "Stack Overflow\n";
            return false;
        } else {
            a[++top] = x;
            return true;
        }
    }
    
    string pop() {
        if (top < 0) {
            return "";
        } else {
            return a[top--];
        }
    }
    
    string peek() {
        if (top < 0) {
            return "";
        } else {
            return a[top];
        }
    }
    
    bool isEmpty() {
        return (top < 0);
    }
};


int precedence(string c) {
    if (c == "^" || c == "sqrt" || c == "±") return 3;
    if (c == "*" || c == "/") return 2;
    if (c == "+" || c == "-") return 1;
    return -1;
}


bool isOperator(string c) {
    return (c == "+" || c == "-" || c == "*" || c == "/" || c == "^" || c == "sqrt" || c == "±");
}

bool isRightAssociative(string op) {
    return (op == "^" || op == "sqrt" || op == "±");
}

string infixToPostfix(string infix[], int size) {
    string postfix = "";
    StringStack s;
    
    for (int i = 0; i < size; i++) {
        string token = infix[i];
        
        if (!isOperator(token) && token != "(" && token != ")" && token != "[" && token != "]") {
            postfix += token + " ";
        } else if (token == "(" || token == "[") {
            s.push(token);
        } else if (token == ")" || token == "]") {
            string openBracket = (token == ")") ? "(" : "[";
            while (!s.isEmpty() && s.peek() != openBracket) {
                postfix += s.pop() + " ";
            }
            if (!s.isEmpty() && s.peek() == openBracket) {
                s.pop(); 
            }
        } else { 
            while (!s.isEmpty() && s.peek() != "(" && s.peek() != "[") {
                int precC = precedence(token);
                int precTop = precedence(s.peek());
                
                if (precC < precTop || (precC == precTop && !isRightAssociative(token))) {
                    postfix += s.pop() + " ";
                } else {
                    break;
                }
            }
            s.push(token);
        }
    }
    while (!s.isEmpty()) {
        postfix += s.pop() + " ";
    }
    return postfix;
}

string infixToPrefix(string infix[], int size) {
    string prefix = "";
    StringStack st;
    
    for (int i = size - 1; i >= 0; i--) {
        string token = infix[i];
        
        if (!isOperator(token) && token != "(" && token != ")" && token != "[" && token != "]") {
            prefix = token + " " + prefix;
        } else if (token == ")" || token == "]") {
            st.push(token);
        } else if (token == "(" || token == "[") {
            string closeBracket = (token == "(") ? ")" : "]";
            while (!st.isEmpty() && st.peek() != closeBracket) {
                prefix = st.pop() + " " + prefix;
            }
            if (!st.isEmpty() && st.peek() == closeBracket) {
                st.pop(); 
            }
        } else { 
            while (!st.isEmpty() && st.peek() != ")" && st.peek() != "]") {
                int precC = precedence(token);
                int precTop = precedence(st.peek());
                
                if (precTop > precC || (precTop == precC && isRightAssociative(token))) {
                    prefix = st.pop() + " " + prefix;
                } else {
                    break;
                }
            }
            st.push(token);
        }
    }
    while (!st.isEmpty()) {
        prefix = st.pop() + " " + prefix;
    }
    return prefix;
}

int main() {
  
    string exp1[] = {"±", "sqrt", "(", "(", "1", "-", "cos(θ)", ")", "/", "(", "1", "+", "cos(θ)", ")", ")"};
    int size1 = 15;
    

    string exp2[] = {"1", "-", "cos(θ)", "^", "2"};
    int size2 = 5;
    
    string exp3[] = {"(", "1", "/", "2", ")", "*", "[", "cos(α-β)", "-", "cos(α+β)", "]"};
    int size3 = 11;

    cout << "--- Double-Angle Formula RHS --- \n";
    cout << "Infix:   ± sqrt ( ( 1 - cos(θ) ) / ( 1 + cos(θ) ) )\n";
    cout << "Postfix: " << infixToPostfix(exp1, size1) << "\n";
    cout << "Prefix:  " << infixToPrefix(exp1, size1) << "\n\n";

    cout << "--- Pythagorean Identity RHS --- \n";
    cout << "Infix:   1 - cos(θ) ^ 2\n";
    cout << "Postfix: " << infixToPostfix(exp2, size2) << "\n";
    cout << "Prefix:  " << infixToPrefix(exp2, size2) << "\n\n";

    cout << "--- Product-to-Sum Identity RHS --- \n";
    cout << "Infix:   ( 1 / 2 ) * [ cos(α-β) - cos(α+β) ]\n";
    cout << "Postfix: " << infixToPostfix(exp3, size3) << "\n";
    cout << "Prefix:  " << infixToPrefix(exp3, size3) << "\n";

    return 0;
}
