#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKENS 1000


struct CharStack {
    int top;
    char a[MAX_TOKENS];
};

void initStack(struct CharStack* s) { s->top = -1; }
int isEmpty(struct CharStack* s) { return s->top == -1; }
void push(struct CharStack* s, char x) { if (s->top < MAX_TOKENS - 1) s->a[++(s->top)] = x; }
char pop(struct CharStack* s) { return isEmpty(s) ? '\0' : s->a[(s->top)--]; }

int main() {
    int n;
    printf("Enter the number of terms n: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input.\n");
        return 1;
    }

   
    char infix[MAX_TOKENS][20];
    int tokenCount = 0;

    for (int i = 1; i <= n && tokenCount < MAX_TOKENS - 1; i++) {
        sprintf(infix[tokenCount++], "%d", 3 * i - 2); 
        if (i < n) {
            strcpy(infix[tokenCount++], "+");
        }
    }

   
    printf("Series: ");
    for (int i = 0; i < tokenCount; i++) {
        printf("%s ", infix[i]);
    }
    printf("\n");

  
    char postfix[MAX_TOKENS * 20] = "";
    struct CharStack s;
    initStack(&s);

    for (int i = 0; i < tokenCount; i++) {
        if (strcmp(infix[i], "+") == 0) {
           
            while (!isEmpty(&s)) {
                char op = pop(&s);
                char temp[4];
                sprintf(temp, "%c ", op);
                strcat(postfix, temp);
            }
            push(&s, '+');
        } else {
            strcat(postfix, infix[i]);
            strcat(postfix, " ");
        }
    }
   
    while (!isEmpty(&s)) {
        char op = pop(&s);
        char temp[4];
        sprintf(temp, "%c ", op);
        strcat(postfix, temp);
    }
    printf("Postfix: %s\n", postfix);

   
    char prefixArray[MAX_TOKENS][20];
    int pIdx = MAX_TOKENS - 1;
    initStack(&s);

    
    for (int i = tokenCount - 1; i >= 0; i--) {
        if (strcmp(infix[i], "+") == 0) {
           
            push(&s, '+');
        } else {
            strcpy(prefixArray[pIdx--], infix[i]);
        }
    }
  
    while (!isEmpty(&s)) {
        char op = pop(&s);
        char temp[2] = {op, '\0'};
        strcpy(prefixArray[pIdx--], temp);
    }

    printf("Prefix: ");
    for (int i = pIdx + 1; i < MAX_TOKENS; i++) {
        printf("%s ", prefixArray[i]);
    }
    printf("\n");

    return 0;
}
