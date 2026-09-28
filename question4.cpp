#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

struct CharStack {
    int top;
    char a[MAX];
};

void initCharStack(struct CharStack* s) { s->top = -1; }
int isCharEmpty(struct CharStack* s) { return s->top == -1; }
void pushChar(struct CharStack* s, char x) { if (s->top < MAX - 1) s->a[++(s->top)] = x; }
char popChar(struct CharStack* s) { return isCharEmpty(s) ? '\0' : s->a[(s->top)--]; }
char peekChar(struct CharStack* s) { return isCharEmpty(s) ? '\0' : s->a[s->top]; }

struct IntStack {
    int top;
    int a[MAX];
};

void initIntStack(struct IntStack* s) { s->top = -1; }
void pushInt(struct IntStack* s, int x) { if (s->top < MAX - 1) s->a[++(s->top)] = x; }
int popInt(struct IntStack* s) { return (s->top == -1) ? 0 : s->a[(s->top)--]; }

int power(int base, int exp) {
    int res = 1;
    for (int i = 0; i < exp; i++) res *= base;
    return res;
}

int precedence(char c) {
    if (c == '^') return 3;
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return -1;
}

int evaluateCondition(char* cond, int x) {
    char op[3] = "";
    int val = 0, i = 0, j = 0;
    
    while (cond[i] != '\0') {
        if (cond[i] == '>' || cond[i] == '<' || cond[i] == '=' || cond[i] == '!') {
            op[j++] = cond[i];
            if (cond[i+1] == '=') {
                op[j++] = cond[i+1];
                i++;
            }
            break;
        }
        i++;
    }
    
    while (cond[i] != '\0') {
        if (isdigit(cond[i]) || cond[i] == '-') {
            val = atoi(&cond[i]);
            break;
        }
        i++;
    }
    
    if (strcmp(op, ">=") == 0) return x >= val;
    if (strcmp(op, "<=") == 0) return x <= val;
    if (strcmp(op, ">") == 0) return x > val;
    if (strcmp(op, "<") == 0) return x < val;
    if (strcmp(op, "==") == 0) return x == val;
    if (strcmp(op, "!=") == 0) return x != val;
    return 0;
}

void infixToPostfix(char* infix, char* postfix) {
    struct CharStack s;
    initCharStack(&s);
    int i = 0, j = 0;
    
    while (infix[i] != '\0') {
        if (infix[i] == ' ') { 
            i++; 
            continue; 
        }
        
        if (isalnum(infix[i])) { 
            while (isalnum(infix[i])) {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
            continue;
        } 
        else if (infix[i] == '(') {
            pushChar(&s, infix[i]);
        } 
        else if (infix[i] == ')') {
         
            while (!isCharEmpty(&s) && peekChar(&s) != '(') {
                postfix[j++] = popChar(&s);
                postfix[j++] = ' ';
            }
            popChar(&s); 
        } 
        else { 
          
            while (!isCharEmpty(&s) && peekChar(&s) != '(' && precedence(infix[i]) <= precedence(peekChar(&s))) {
                if (infix[i] == '^' && peekChar(&s) == '^') break; 
                postfix[j++] = popChar(&s);
                postfix[j++] = ' ';
            }
            pushChar(&s, infix[i]);
        }
        i++;
    }
    
  
    while (!isCharEmpty(&s)) {
        postfix[j++] = popChar(&s);
        postfix[j++] = ' ';
    }
    postfix[j] = '\0';
}

int evaluatePostfix(char* postfix, int x) {
    struct IntStack s;
    initIntStack(&s);
    int i = 0;
    
    while (postfix[i] != '\0') {
        if (postfix[i] == ' ') {
            i++;
            continue;
        }
        
        if (postfix[i] == 'x') {
            pushInt(&s, x);
            i++;
        } 
        else if (isdigit(postfix[i])) {
            int num = 0;
            while (isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            pushInt(&s, num);
        } 
        else {
            int val1 = popInt(&s);
            int val2 = popInt(&s);
            
            switch (postfix[i]) {
                case '+': pushInt(&s, val2 + val1); break;
                case '-': pushInt(&s, val2 - val1); break;
                case '*': pushInt(&s, val2 * val1); break;
                case '/': pushInt(&s, val2 / val1); break;
                case '^': pushInt(&s, power(val2, val1)); break;
            }
            i++;
        }
    }
    return popInt(&s);
}

int main() {
    char exp1[100], cond1[50];
    char exp2[100], cond2[50];
    int x;

    printf("Enter Expression 1: ");
    scanf(" %[^\n]", exp1);
    printf("Enter Condition 1: ");
    scanf(" %[^\n]", cond1);

    printf("Enter Expression 2: ");
    scanf(" %[^\n]", exp2);
    printf("Enter Condition 2: ");
    scanf(" %[^\n]", cond2);

    printf("Enter x: ");
    scanf("%d", &x);

    char* selectedExp = NULL;
    char* selectedCond = NULL;

    if (evaluateCondition(cond1, x)) {
        selectedExp = exp1;
        selectedCond = cond1;
    } else if (evaluateCondition(cond2, x)) {
        selectedExp = exp2;
        selectedCond = cond2;
    } else {
        printf("No condition satisfied for x = %d\n", x);
        return 1;
    }

    char postfix[100];
    infixToPostfix(selectedExp, postfix);
    int result = evaluatePostfix(postfix, x);

    printf("\nOutput:\n");
    printf("The program selects:\n");
    printf("Condition: %s\n", selectedCond);
    printf("Expression: %s\n", selectedExp);
    printf("Postfix Expression: %s\n", postfix);
    printf("Calculated Value: %d\n", result);

    return 0;
}
