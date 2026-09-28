#include <iostream>
using namespace std;

#define MAX 100 

class Stack {
    int top;
public:
    int a[MAX]; 
    Stack() { top = -1; } 
    bool push(int x);
    int pop();
    bool isEmpty();
};

bool Stack::push(int x) {
    if (top >= (MAX - 1)) {
        cout << "Stack Overflow\n"; 
        return false;
    } else {
        a[++top] = x; 
        return true;
    }
}

int Stack::pop() {
    if (top < 0) {
        cout << "Stack Underflow\n"; 
        return 0;
    } else {
        int x = a[top--]; 
        return x;
    }
}

bool Stack::isEmpty() {
    return (top < 0); 
}

int main() {
    Stack s;
    int n, val;
    
    cout << "Enter the number of elements: ";
    cin >> n;
    
    if (n <= 0) {
        cout << "Invalid number of elements.\n";
        return 0;
    }

    cout << "Enter " << n << " elements (first element is the bottom):\n";
    for (int i = 0; i < n; i++) {
        cin >> val;
        s.push(val);
    }

    int max_val = -2147483648; 
    int min_val = 2147483647;  
    
    Stack tempStack;
    int count = 0;

    
    while (!s.isEmpty()) {
        int current = s.pop();
        if (current > max_val) max_val = current;
        if (current < min_val) min_val = current;
        tempStack.push(current);
        count++;
    }

    int current_idx = 0;
    int mid1 = -1, mid2 = -1;
    
  
    while (!tempStack.isEmpty()) {
        int current = tempStack.pop();
        
        if (count % 2 != 0) {
          
            if (current_idx == count / 2) {
                mid1 = current;
            }
        } else {
            
            if (current_idx == (count / 2) - 1) {
                mid1 = current;
            } else if (current_idx == count / 2) {
                mid2 = current;
            }
        }
        
        s.push(current);
        current_idx++;
    }

    cout << "\nMaximum value: " << max_val << "\n";
    cout << "Minimum value: " << min_val << "\n";

    if (count % 2 != 0) {
        cout << "Middle element: " << mid1 << "\n";
    } else {
        cout << "Middle elements (even count): " << mid1 << " and " << mid2 << "\n";
    }

    return 0;
}
