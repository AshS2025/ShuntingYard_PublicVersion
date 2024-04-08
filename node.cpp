#include <iostream>
#include <cstring>
#include "node.h"


//main constructor
Node:: Node() {
}

Node:: Node(char Data){
  data = Data;
  next = NULL;
  right = NULL;
  left = NULL;
}

char Node:: getData(){
  return data;
}

void Node:: setData(char Data){
  data = Data;
}

Node* Node:: getNext(){
  return next;
}

void Node:: setNext(Node* Next){
  next = Next;
}

Node* Node:: getRight(){
  return right;
}

void Node:: setRight(Node* Right){
  right = Right;
}

Node* Node:: getLeft(){
  return left;
}

void Node:: setLeft(Node* Left){
  left = Left;
}



