#include <iostream>
using namespace std;

#define MAX 100

class StackArray {
    int top;
public:
    int a[MAX];
    StackArray() { top = -1; }
    
    bool push(int x) {
        if (top >= (MAX - 1)) {
            return false;
        } else {
            a[++top] = x;
            return true;
        }
    }
    
    int pop() {
        if (top < 0) {
            return -1;
        } else {
            return a[top--];
        }
    }
    
    bool isEmpty() {
        return (top < 0);
    }
};


struct Node {
    int data;
    Node* link;
};

class StackLL {
    Node* top;
public:
    StackLL() { top = NULL; }
    
    void push(int data) {
        Node* temp = new Node();
        if (!temp) {
            cout << "\nHeap Overflow";
            return;
        }
        temp->data = data;
        temp->link = top;
        top = temp;
    }
    
    int pop() {
        if (top == NULL) return -1;
        int x = top->data;
        Node* temp = top;
        top = top->link;
        delete temp;
        return x;
    }
    
    int peek() {
        if (top == NULL) return -1;
        return top->data;
    }
    
    bool isEmpty() {
        return (top == NULL);
    }
};

class CircularQueue {
    int front, rear, N;
    int* arr;
public:
    CircularQueue(int size) {
        N = size;
        arr = new int[N];
        front = -1;
        rear = -1;
    }
    
    ~CircularQueue() {
        delete[] arr;
    }
    
    bool isEmpty() {
        return (front == -1 && rear == -1);
    }
    
    bool isFull() {
        return ((rear + 1) % N == front);
    }
    
    void enqueue(int value) {
        if (isFull()) {
            cout << "Queue is full\n";
            return;
        } else if (isEmpty()) {
            front = 0;
            rear = 0;
        } else {
            rear = (rear + 1) % N;
        }
        arr[rear] = value;
    }
    
    int dequeue() {
        if (isEmpty()) {
            return -1;
        }
        int x = arr[front];
        if (front == rear) {
            front = -1;
            rear = -1;
        } else {
            front = (front + 1) % N;
        }
        return x;
    }
    
    void display() {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return;
        }
        cout << "Circular Queue elements: ";
        int i = front;
        while (true) {
            cout << arr[i] << " ";
            if (i == rear) break;
            i = (i + 1) % N;
        }
        cout << "\n";
    }
};

int main() {
    int n1, n2, val;
    StackArray s1, s2;
    
  
    cout << "Enter size of Stack 1: ";
    cin >> n1;
    cout << "Enter elements for Stack 1 (bottom-to-top order):\n";
    for (int i = 0; i < n1; i++) {
        cin >> val;
        s1.push(val);
    }
    
  
    cout << "Enter size of Stack 2: ";
    cin >> n2;
    cout << "Enter elements for Stack 2 (bottom-to-top order):\n";
    for (int i = 0; i < n2; i++) {
        cin >> val;
        s2.push(val);
    }
    
   
    StackArray temp1, temp2;
    while (!s1.isEmpty()) {
        temp1.push(s1.pop());
    }
    while (!s2.isEmpty()) {
        temp2.push(s2.pop());
    }
    
   
    StackLL s3;
    
   
    while (!temp1.isEmpty() || !temp2.isEmpty()) {
        if (!temp1.isEmpty()) {
            s3.push(temp1.pop());
        }
        if (!temp2.isEmpty()) {
            s3.push(temp2.pop());
        }
    }
    
  
    StackLL sortedStack;
    while (!s3.isEmpty()) {
        int current = s3.pop();
        
       
        while (!sortedStack.isEmpty() && sortedStack.peek() < current) {
            s3.push(sortedStack.pop());
        }
        sortedStack.push(current);
    }
    
  
    CircularQueue cq(n1 + n2);
    
  
    while (!sortedStack.isEmpty()) {
        cq.enqueue(sortedStack.pop());
    }
    
    cout << "\n";
    cq.display();
    
    return 0;
}
