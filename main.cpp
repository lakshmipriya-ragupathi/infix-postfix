//
//  main.cpp
//  week_11_oops
//
//  Created by Ragupathi on 18/10/2022.
//


#include <iostream>
using namespace std;
/*
 Write a C++ program to convert an infix to a postfix expression with queues implemented using a singly linked list. Handle all boundary conditions using exception handling (try-catch-throw). Implement the following Menus

 Get Infix Expression
 Print Infix Expression
 Print Postfix Expression
 Exit
 
 
 //check for infix:
 first character is alpha/bracket
 no operator is preceeded or suceeded by another
 equal number of open and closing paranthesie
 
 Hint: What data structure do you use for conversion of infix to postfix?
 stacks
 */

//SHUNTING YARD ALGORITHM

class node{
private:
    char val;
    node *next;
    
public:
    node * head = NULL;
    node * newnode(char c);
    void push_queue(char c);
    char stack_head();
    void enqueue(char c);
    char dequeue();
    void display();
    bool isEmpty();
};

node * node::newnode(char c){
    node *newNode;
    newNode = new node;
    newNode->val = c;
    newNode->next = NULL;
    return newNode;
}

void node::enqueue(char c){
    node *temp = head;
    if(temp == NULL){
        node * insert = newnode(c);
        insert->next = head;
        head = insert;
    }
    else{
    while(temp->next != NULL){
        temp = temp->next;
    }
    node *insert = newnode(c);
    temp->next = insert;
    }
}

 char node::dequeue(){
     try{
         
     node *temp = head;
         if(temp == NULL){
             throw temp;
         }
     head = head->next;
     char ret = temp->val;
     delete temp;
     return ret;
         
     }
     catch(...){
         cout << "queue/stack is empty" << endl;
     }
     return NULL;
 }

bool node::isEmpty(){
    if(head == NULL){
        return true;
    }
    else{
        return false;
    }
}

void  node::push_queue( char c){
    node queue2;
    node *temp = head;
    if(isEmpty() == true){
        enqueue(c);
        return;
    }
    
    while(isEmpty() != true){
        char popped = dequeue();
        queue2.enqueue(popped);
        //cout << "here : ";
        //queue2.display();
        temp = head;
    }
    char popped = dequeue();
    queue2.enqueue(popped);
    enqueue(c);
    node *temp1 = queue2.head;
    while(queue2.isEmpty() != true){
        char popped =queue2.dequeue();
        enqueue(popped);
        temp1 = head;
    }
    
}


char node::stack_head(){
    return head->val;
}

void node::display(){
    node *temp = head;
    while(temp != NULL){
        cout << temp->val;
        temp = temp->next;
    }
}


void infix_postfix(string s, node stack, node queue){
    int flag = 0;
    for(int i=0; i<s.length(); ++i){
        if(s[i] != '(' && s[i] != ')' && s[i] != '^' && s[i] != '*' && s[i] != '+' && s[i] != '-' && s[i] != '/') {
            queue.enqueue(s[i]);
        }
        if(stack.isEmpty() == true){
            if (s[i] == '^' ||  s[i] == '*' || s[i] == '/' || s[i] == '+' || s[i] == '-'){
                stack.push_queue(s[i]);
                flag = 1;
            }
        }
        else if(s[i] == '('){
            stack.push_queue(s[i]);
        }
        
        else if(s[i] == ')'){
            char stack_top = stack.stack_head();
            while(stack_top != '(' && stack.isEmpty() == false){
                char dequeueped = stack.dequeue();
                queue.enqueue(dequeueped);
                if(stack.isEmpty() == false){
                stack_top = stack.stack_head();
                }
            }
        }
        
        else if(s[i] == '^'){
            stack.push_queue(s[i]);
        }
        
        else if(s[i] == '*'){
            char top = stack.stack_head();
            if(top != '^'){
                stack.push_queue(s[i]);
            }
            else{
                char dequeueped = stack.dequeue();
                queue.enqueue(dequeueped);
                stack.push_queue(s[i]);
            }
        }
        else if(s[i] == '/'){
            char top = stack.stack_head();
            if(top != '^' && top != '*'){
                stack.push_queue(s[i]);
            }
            else{
                char dequeueped = stack.dequeue();
                queue.enqueue(dequeueped);
                stack.push_queue(s[i]);
            }
        }
        
        else if(s[i] == '+'){
            char top = stack.stack_head();
            if(top != '^' && top != '*' && top != '/'){
                stack.push_queue(s[i]);
            }
            else{
                char dequeueped = stack.dequeue();
                queue.enqueue(dequeueped);
                stack.push_queue(s[i]);
            }
        }
        
        else if(s[i] == '-'){
            char top = stack.stack_head();
            if(top != '^' && top != '*' && top != '/' && top != '+'){
                stack.push_queue(s[i]);
            }
            else{
                char dequeueped = stack.dequeue();
                queue.enqueue(dequeueped);
                stack.push_queue(s[i]);
            }
        }
    }
    if(stack.isEmpty() != true){
    char top = stack.stack_head();
    while(stack.isEmpty() != true){
        if(top != '('){
        queue.enqueue(top);
        }
        stack.dequeue();
        if(stack.isEmpty() == false && stack.stack_head() != '('){
        top = stack.stack_head();
        }
    }
    }
    queue.display();
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
    node stack_paranthesis;
    try{
        int alpha_count = 0, operator_count = 0;
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
            stack_paranthesis.push_queue(s[i]);
        }
        if(s[i] == ')'){
            if(stack_paranthesis.isEmpty() == true){
                flag = 1;
                throw s[i];
            }
            else{
            stack_paranthesis.dequeue();
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
    node stack, queue;
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
                infix_postfix(infix, stack, queue);
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
