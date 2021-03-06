#include <stdio.h>
#define STACK_SIZE 100
int stack[STACK_SIZE];
int top;
void init_stack(){
    top = -1; // empty stack
}

int push(int value){
    if (top >= STACK_SIZE -1 ){
/* this status is that "STACK-OVERFLOW"
 * NOTE that it is an array stack. */
        printf("\n - STACK OVERFLOW. - \n");
        return -1;
    }
    stack[++top] = value;
    return value;
}

int pop(){
    if(top < 0) {
        printf("\n - UNDERFLOW - \n");
        return -1;
    }
    return stack[top--];
    // return the value and adjust the index(top)
}

void print_stack(void) {
    int i;
    printf("\n Stack contents : Top --> Bottom\n");
    for (i = top; i >= 0; i--)
        printf("%-6d", stack[i]);
}

int get_stack_top(){
    return (top < 0) ? -1 : stack[top];
    // empty stack이 아닐 시에 stack 최상위값 반환.
    // pop과 다름. stack 최상위에 있는 값만 출력하고 top 변화 없음 유의.
}
int is_stack_empty(){
    return (top<0);
}
int is_operator(int ch){ //ascii 코드로 비교하는 것 유의
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}
int precedence(int op){ //연산자 우선순위 부여
    if (op == '(') return 0;
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    else return 3;
}
/* case 1. '(' 문자는 스택에 push
 * case 2. 피연산자 그대로 postfix 배열에 저장.
 * case 3. 연산자는 스택에서 *infix 자신보다 우선 순위가 높은 연산자는 pop하여 postfix 배열에 저장하고,
 *    자신보다 우선순위가 낮은 연산자를 만났을 때에는 멈추고 자신을 스택에 push.
 * case 4. ')'를 만나면 스택에서 '('를 만날 때까지 pop해서 postfix에 저장
 */
void infix_to_postfix(char *infix, char *postfix){// 각각 중위표기, 후위표기 배열
    init_stack();
    while (*infix) { // *infix : 현재 처리하고자 하는 문자
        if (*infix == '(') { // case 1.
            push(*infix); infix++; // equal to push(*infix++);
        }
        else if (*infix == ')') { // case 4.
            while (get_stack_top() != '(') { // '('를 만날 때까지
                *postfix++ = pop(); *postfix++ = ' ';
                /*stack에서 pop하여 postfix가 가리키는 곳의 값을 바꿔줌*/
            }
            pop();
            /* 위의 while문이 끝났을 때 '('는 아직 stack에 있으므로,
             * stack에서 빼줘야함. */
            infix++;
        }
        else if (is_operator(*infix)) { // case 3.
            while (!is_stack_empty() &&
                   precedence(get_stack_top())>=precedence(*infix)){
                /* *infix보다 스택 최상위값의 우선순위가 더 높을 때 동안
                 * 스택에서 pop하여 postfix 배열에 저장.*/
                *postfix++ = pop(); *postfix++ = ' ';
            }
            /*스택이 비었거나, *infix가 자신보다 우선순위가 낮은 연산자를 만났을 때
             * while문 탈출. 자신을 스택에 push*/
            push(*infix);
            infix++;
        }
        else if (*infix >= '0' && *infix <= '9') { // case 4.
            do {
                *postfix++ = *infix++;
            } while (*infix >= '0' && *infix <= '9'); *postfix++ = ' ';
        }
        else infix++; }
    while (!is_stack_empty()) {
        *postfix++ = pop(); *postfix++ = ' ';
    }
    postfix--; *postfix = 0;
}

int main() {

    return 0;
}