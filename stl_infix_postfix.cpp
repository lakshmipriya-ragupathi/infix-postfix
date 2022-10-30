//
//  main.cpp
//  stl_oops
//
//  Created by Ragupathi on 22/10/2022.
//

/*
 Write a C++ program to convert an infix to a postfix expression with queues implemented using a singly linked list. Handle all boundary conditions using exception handling (try-catch-throw). Implement the following Menus
 Get Infix Expression
 Print Infix Expression
 Print Postfix Expression
 Exit
 Hint: What data structure do you use to convert infix to postfix?
 Note:
 Use only STL
 No brackets are allowed in infix expressions
 Implement for +, -, *, and / operators only.
 Precedence of +, -  is less than the precedence of *, /
 Precedence + and - has the same precedence, * and / have the same precedence
 Associativity - left to right for all operators
 Minimum 1 exception handling statement. Handling of wrong infix expressions is mandatory
 */
#include <iostream>
#include<queue>
using namespace std;

void display(queue<char> q)
{
    queue<char> temp = q;
    while (!temp.empty()) {
        cout << temp.front();
        temp.pop();
    }
}
queue <char> push_queue(char a, queue<char> &q){
    queue<char> sup;
    q.swap(sup);
    q.push(a);
    while(!sup.empty()){
        q.push(sup.front());
        sup.pop();
    }
    return q;
}

void infix_postfix(string s){
    //push to stack if operator, enqueue if operand
    queue<char> queue, stack;
    int flag = 0;
    for(int i=0; i<s.length(); ++i){
        if(s[i] != '(' && s[i] != ')' && s[i] != '^' && s[i] != '*' && s[i] != '+' && s[i] != '-' && s[i] != '/') {
            queue.push(s[i]);
        }
        if(stack.empty() == true){
            if (s[i] == '^' ||  s[i] == '*' || s[i] == '/' || s[i] == '+' || s[i] == '-'){
                stack = push_queue(s[i], stack);
                flag = 1;
            }
        }
        
        else if(s[i] == '('){
            stack = push_queue(s[i], stack);
        }
        
        else if(s[i] == ')'){
            char stack_top = stack.front();
            while(stack_top != '(' && stack.empty() == false){
                queue.push(stack.front());
                stack.pop();
                if(stack.empty() == false){
                stack_top = stack.front();
                }
            }
        }
        else if(s[i] == '^'){
            stack = push_queue(s[i], stack);
        }
        else if(s[i] == '*'){
            char top = stack.front();
            if(top != '^'){
                stack = push_queue(s[i], stack);
            }
            else{
                char dequeueped = stack.front();
                stack.pop();
                queue.push(dequeueped);
                stack = push_queue(s[i], stack);
            }
        }
        else if(s[i] == '/'){
            char top = stack.front();
            if(top != '^' && top != '*'){
                stack = push_queue(s[i], stack);
            }
            else{
                char dequeueped = stack.front();
                stack.pop();
                queue.push(dequeueped);
                stack = push_queue(s[i], stack);
            }
        }
        else if(s[i] == '+'){
            char top = stack.front();
            if(top != '^' && top != '*' && top != '/'){
                stack = push_queue(s[i], stack);
            }
            else{
                char dequeueped = stack.front();
                stack.pop();
                queue.push(dequeueped);
                stack = push_queue(s[i], stack);
            }
        }
        
        else if(s[i] == '-'){
            char top = stack.front();
            if(top != '^' && top != '*' && top != '/' && top != '+'){
                stack = push_queue(s[i], stack);
            }
            else{
                char dequeueped = stack.front();
                stack.pop();
                queue.push(dequeueped);
                stack = push_queue(s[i], stack);
            }
        }
        
    }
    if(stack.empty() != true){
    char top = stack.front();
    while(stack.empty() != true){
        if(top != '('){
        queue.push(top);
        }
        stack.pop();
        if(stack.empty() == false && stack.front() != '('){
        top = stack.front();
        }
    }
    }
    display(queue);
}

int check(string s){
    int flag = 0;
    for(int i=0; i<s.length(); ++i){
        try{
            if(s[i] < 'A'){
                    if(s[i] != '-' && s[i] != '+' && s[i] != '(' && s[i] != ')' && s[i] != '*' && s[i] != '^' && s[i] != '/'){
                        flag = 1;
                        throw s[i];
                    }
            }
        }
        catch(char a){
            cout << "ONLY ALPHABETS ARE ALLOWED" << endl;
        }
    }
    return flag;
}
int infix_check(string s){
    int flag = 0;
    queue<char> stack;
    try{int alpha_count = 0, operator_count = 0;
        for(int i=0; i<s.length(); ++i){
            if(i == 0){
                if( s[0] < 'A' && s[i] != '('){
                    flag = 1;
                    throw s[i];
                }
            }
            if(s[i] == '-' || s[i] == '+' || s[i] == '*' || s[i] == '^' || s[i] == '/'){
                operator_count++;
            }
            if((s[i] >= 'a' && s[i] <= 'z' )||( s[i] >= 'A' && s[i] <= 'Z')){
                alpha_count++;
            }
            if(s[i] == '('){
                stack = push_queue(s[i], stack);
            }
            if(s[i] == ')'){
                if(stack.empty() == true){
                    flag = 1;
                    throw s[i];
                }
                else{
                stack.pop();
                }
            }
            if(((s[i] >= 'a' && s[i] <='z') || (s[i] >= 'A' && s[i] <= 'Z')) &&((s[i+1] >= 'a' && s[i+1] <='z' )||( s[i+1] >= 'A' && s[i+1] <= 'Z'))){
                flag = 1;
                throw s[i];
            }
            if((s[i] == '-' || s[i] == '+' || s[i] == '*' || s[i] == '^' || s[i] == '/') && (s[i+1] == '-' || s[i+1] == '+' || s[i+1] == '*' || s[i+1] == '^' || s[i+1] == '/')){
                flag = 1;
                throw s[i];
            }
        }
            
            if(alpha_count%2 == 0){
                if(operator_count%2 == 0){
                    flag = 1;
                    throw alpha_count;
                }
            }
            if(operator_count %2 != 0){
                if(alpha_count%2 != 0){
                    flag = 1;
                    throw operator_count;
                }
            }
            
        }
        catch(char a){
            cout << "invalid infix expression " << endl;
        }
        catch(int a){
            cout << "invalid infix expression : mistaching number of operands and operators" << endl;
        }
        return flag;
}

int main() {
    string infix;
    int option = 5, flag = 0;
    cout << "This program is to  convert an infix to a postfix expression" << endl;
    while(option != 4){
        cout << "\n1. Get Infix Expression\n2. Print Infix Expression\n3. Print Postfix Expression\n4. Exit" << endl;
        cin >> option;
        try{
            if(option < 0){
                throw option;
            }
        switch(option){
            case 1: {
                cout << "Please enter the infix expression : "; cin >> infix;
                flag = check(infix);
                flag = infix_check(infix);
                break;
            }
            case 2: {
                cout << "The infix expression : ";
                cout << infix << endl;
                break;
            }
            case 3: {
                if(flag == 0){
                cout << "The postfix expression is : ";
                infix_postfix(infix);
                break;
                }
                else{
                    cout << "please enter a valid infix expression " << endl;
                    break;
                }
            }
            case 4: {
                cout << "you've successfully exited the program :)" << endl;
                break;
            }
            default:{
                cout << "invaild choice!!" << endl;
            }
        }
        }
        catch(int ex){
            cout << "please enter positive integer within the range!!" << endl;
        }
    }
    return 0;
}
