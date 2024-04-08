#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <cstring>

class Node {

 private:
 char data; //holds the number or operator
 Node* next; //for the shunting yard itself
 Node* right;
 Node* left;
 //rights and lefts for tree
 

 public:

 //constructors
 Node();
 Node(char Data);

 //getters and setters

 char getData();
 void setData(char Data);

 Node* getNext();
 void setNext(Node* Next);

 Node* getRight();
 void setRight(Node* Right);

 Node* getLeft();
 void setLeft(Node* Left);

};

#endif

