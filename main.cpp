/*
  
*/

#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

//initializations
void shuntingYard(char* infix, char* postfix);
Node* pop(Node* &top);
Node* peek(Node* &top);
void push(Node* newNode, Node* &top);
bool isOperator(char t);
int operatorOrder(char);
void enqueue(Node* &front, Node* &tail, Node*);
Node* dequeue(Node* &front);
void printInfix(Node*);
Node* expressionTree(char*, Node*&);
void printTree(Node*, int);
//main
int main(){

  cout << "do we even get to main?" << endl;
  
  char infix[100];
  Node* root = NULL;
  Node* top = NULL;
  Node* qfront = NULL;
  Node* qtail = NULL;

  bool running = true;
  char* postfix = new char[100];
  

  
  
  while (running == true){

      cout << "enter equation in infix. type QUIT to exit program." << endl;
      cin.getline(infix, 100);

      if ((strcmp("QUIT", infix)) == 0){
	cout << "exiting program" << endl;
	running = false;
      }

      else{
      
      shuntingYard(infix, postfix);
      cout << "translation done" << endl;
      expressionTree(postfix, root);
      cout << "printing tree now" << endl;
      printTree(root, 0);

    cout << "how do you want to print: prefix, postfix, infix" << endl;

    char printMethod[10];
    cin.getline(printMethod, 10);

    if (strcmp(printMethod, "infix") == 0){
      cout << root->getData() << endl;
      cout << root->getLeft()->getData() << endl;
      cout << root->getRight()->getData() << endl;
      printInfix(root);
      cout << " " << endl;
    }

    
    
  }

  
}

}

void shuntingYard(char* infix, char* postfix){
  Node* operstackhead = NULL;
  Node* quefront = NULL;
  Node* quetail = NULL;

  int i = 0;
  while (infix[i] != '\0'){
    int thing = infix[i];
    Node* token = new Node(thing);

    if (isdigit(thing)){
      enqueue (quefront, quetail, token);
    }

    if (thing == '('){
      push(token, operstackhead);
    }

    if (thing == ')'){
      
      /*figure out what to do
	update: figured it out
	pop everything from the stack until reach a left parantheses
	delete both parantheses 
       */

      Node* p = peek(operstackhead);

      while (p->getData() != '('){
	Node* poppy = pop(operstackhead);
	enqueue (quefront, quetail, poppy);
      }

      if (p->getData() == '('){
	Node* deletey = pop(operstackhead);
	delete deletey;
	delete token;
      }
      
    }

    if (isOperator(thing)){
      /*
	add to stack
	store order of current
	check order of next
	if current order > next order
	   pop everything and enqueue 
       
      Node* check = peek(operstackhead);

      
      if (check == NULL){
	push(new Node(thing), operstackhead);
      }

      else{
      int nextOrder = operatorOrder(check->getData());
      push(new Node(thing), operstackhead);
      int currentOrder = operatorOrder(thing);

      while (currentOrder >= nextOrder){
	  enqueue (quefront, quetail, pop(operstackhead));
	  nextOrder = operatorOrder(check->getNgetData());
	  currentorder = o
      }
    }
      */

      while(operstackhead != NULL && operatorOrder(peek(operstackhead)->getData()) >= operatorOrder(thing) && peek(operstackhead)->getData() != '(')
	enqueue (quefront, quetail, pop(operstackhead));
      push(new Node(thing), operstackhead);
    }
    

    i++;
  }

  //adding remaining operator in stack into postfix queue if equation is done being read
  Node* p = peek(operstackhead);
    while (p != NULL){
      enqueue(quefront, quetail, pop(operstackhead));
      p = peek(operstackhead);
    }
  
  
  
  //dequeueing into the postfix
  Node* current = quefront;
  int a = 0;
  while (current != NULL){
    postfix[a++] = current->getData();
    current = current->getNext();
  }
  postfix[a] = '\0';
  
  cout << postfix << endl;
 
}


//checking operator

bool isOperator (char t){
  if ((t == '+')||(t == '-')||(t == '*')||(t == '/') || (t == '^')){
    return true;
  }
  else {
    return false;
  }
}

//queue stuff
//front is the left most and tail is the most recently added

void enqueue(Node* &front, Node* &tail, Node* newNode) {
    if (front == nullptr) {
        front = tail = newNode;
    } else {
        tail->setNext(newNode);
        tail = newNode;
    }
}

Node* dequeue(Node* &front) {
    if (front == nullptr) {
        cerr << "Queue is empty\n";
        return nullptr;
    }
    Node* data = front;
    front = front->getNext();
    return data;

}


//Stack functions
//push, pop, peek

Node* pop (Node* &top){
  if (top == NULL){
    cout << "stack is empty" << endl;
    return NULL;
  }

  else {
    Node* popped = top;
    top = top->getNext();
    return popped;
  }
  
}

Node* peek (Node* &top){
  if (top == NULL){
    cout << "stack is empty" << endl;
    return NULL;
  }

  else {
    return top;
  }

}

void push (Node* newNode, Node* &top){
  if (top == NULL){
    newNode->setNext(NULL);
    top = newNode;
  }

  else{
    newNode->setNext(top);
    top = newNode;
  }
}

int operatorOrder (char oper){
  if ((oper == '+') || (oper == '-')){
    return 1;
  }
  if ((oper == '*') || (oper == '/')) {
    return 2;
  }
  if (oper == '^'){
    return 3;
  }
  else{
    return 0;
  }
  }




Node* expressionTree(char* postfix, Node* &head){
  /*
    

   */

  Node* tree = NULL;
  int a = 0;

  while (postfix[a] != '\0'){
    char character = postfix[a];
    Node* newN = new Node(character);
    cout << "we are looking at " << character << endl;
    if (isOperator(character) == false){
      newN->setLeft(NULL);
      newN->setRight(NULL);
    }

    else{ //hit an operator
      Node* right = pop(tree); //right = topmost
      Node* newRight = new Node (right->getData());
      Node* left = pop(tree); //left = second from top
      Node* newLeft = new Node (left->getData());
      newN->setLeft(newLeft);
      newN->setRight(newRight);
      cout << "left node: " << newN->getLeft()->getData() << endl;
      cout << "right node: " << newN->getRight()->getData() << endl;
    }

    push(newN, tree);
    a++;
  }

  return peek(tree);
}

void printInfix(Node* root){
  /*
    get left until get left is null
    print that thing
    
  */
  
  if (root->getLeft() != NULL){
    root = root->getLeft();
    cout << "root is now " << root->getData() << endl;
    printInfix(root);
  }

    char print = root->getData();
    cout << print;
  

  if (root->getRight() != NULL){
    root = root->getRight();
    cout << "root is now " << root->getData() << endl;
    printInfix(root);
  }   
  
}

void printPostfix(Node* root){
}

void printPrefix(Node* root){
}


void printTree(Node* root, int count){
  if (root == NULL){
    cout << "NOTHING IN THE TREE" << endl;
    return;
  }

  //iuterates to left of tree
  else if (root->getRight() != NULL){
    printTree(root->getRight(), count +1);
  }

  //prints out appropriate number of tabs
  for (int i = 0; i < count; i++){
    cout << '\t';
  }

  //prints
  cout << root->getData() << endl;
  //runs on the right side

  if (root->getLeft() != NULL){
    printTree (root->getLeft(), count + 1);
  }
}
