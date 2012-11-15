#include "BST.h"
#include <iostream>
#include <list>
template <typename T>
BST<T>::BST() {
  root = 0;
}

template <typename T>
BST<T>::~BST() {
  postOrderDelete(root);
}


template <typename T>
bool BST<T>::find(T v) {
  Node<T>* temp = new Node<T>(v);
  root = temp;  
  return true;
}

template <typename T>
void BST<T>::insert(T v) {
  Node<T>* newNode = new Node<T>(v);
  Node<T>** curr = &root;
  Node<T>* critNode;
  bool critNodeFound = false;
  while (*curr != 0) {
    if ((*curr)->getBalance() != 0) {
      critNodeFound = true;
      critNode = (*curr);
    }
    if (v < (*curr)->getValue()) {
      curr = &((*curr)->getLeftChild());
    } else if (v > (*curr)->getValue()) {
      curr = &((*curr)->getRightChild());
    } else return;
  } 
  *curr = newNode;
  Node<T>* critNodeChild;
  Node<T>* critNodeChildChild;
  Node<T>* node;
  int d1, d2; //d3;
  if (critNodeFound == false) {
    node = root;
  } else {
    if (v < critNode->getValue()) {
      d1 = -1;
      critNodeChild = critNode->getLeftChild();
    } else if (v > critNode->getValue()){
      d1 = 1;
      critNodeChild = critNode->getRightChild();
    } else {
      d1 = 0;
      critNodeChild = critNode;
    }
    if (critNode->getBalance() != d1) {
      critNode->setBalance(0);
      node = newNode;
    } else {
      if (v < critNodeChild->getValue()) {
	d2 = -1;
	critNodeChildChild = critNodeChild->getLeftChild();
      } else if (v > critNodeChild->getValue()) {
	d2 = 1;
	critNodeChildChild = critNodeChild->getRightChild();
      } else {
	d2 = 0;
	critNodeChildChild = critNodeChild;
      }
      if (d2 == d1) {
	critNode->setBalance(0);
	node = critNodeChildChild;
	rotate(critNode, -d1);
      } else {

      }
    }
  }
}

template <typename T>
void BST<T>::remove(T v) {  // using in-order successor
  Node<T>** curr = &root;
  while(curr != 0 && (*curr)->getValue() != v) {
    if(v > (*curr)->getValue())
      curr = &((*curr)->getRightChild());
    else 
      curr = &((*curr)->getLeftChild());
  }
  if(curr != 0) {
    Node<T>* nodeToRemove = *curr;
    if(nodeToRemove->getLeftChild() == 0 && nodeToRemove->getRightChild() == 0)
 {
      delete nodeToRemove;
      *curr = 0;
    } else if (nodeToRemove->getLeftChild() == 0) {
      *curr = nodeToRemove->getRightChild();
      delete nodeToRemove;
    } else if (nodeToRemove->getRightChild() == 0) {
      *curr = nodeToRemove->getLeftChild();
      delete nodeToRemove;
    } else {
      Node<T>* ios = nodeToRemove->getRightChild();
      while(ios->getLeftChild() != 0) {
	ios = ios->getLeftChild();
      }
      ios->setLeftChild(*(nodeToRemove->getLeftChild()));
      *curr = nodeToRemove->getRightChild();
      delete nodeToRemove;
    }
  }
}

template<typename T>
void BST<T>::rotate(Node<T>* t, int d) {
  Node<T>* curr;
  if (d == -1 ) {  // rotate left
    curr = t->getRightChild();
    t->setRightChild(*(curr->getLeftChild()));
    curr->setLeftChild(*t);
  } else { // rotate right
    curr = t->getLeftChild();
    t->setLeftChild(*(curr->getRightChild()));
    curr->setRightChild(*t);
  }
}

template<typename T>
void BST<T>::postOrderDelete(Node<T>* t) {
  if (t != 0) {
    postOrderDelete(t->getLeftChild());
    postOrderDelete(t->getRightChild());
    delete t;
  }
}

template <typename T>
void BST<T>::print() {
  traversalPrint(root);
}

template <typename T>
void BST<T>::traversalPrint(Node<T>* root) {
  if(root != 0) {

    traversalPrint(root->getLeftChild());

    traversalPrint(root->getRightChild());
    std::cout << root->getValue() << std::endl;
  }
}

template <typename T>
void BST<T>::printTree() {
  std::list<Node<T>* > queue;
  queue.push_front(root);
  int currentLevel = 1;
  int nextLevel = 0;
  while(!queue.empty()){
    Node<T>* val = queue.front();
    std::cout << val->getValue() << " ";
    queue.pop_front();
    currentLevel = currentLevel - 1;
    
    if(val->getLeftChild()!=0){
    queue.push_back(val->getLeftChild());
    nextLevel++;
    }
    if(val->getRightChild()!=0){
    queue.push_back(val->getRightChild());
    nextLevel++;
    }
    if(currentLevel == 0) {
      std::cout << std::endl;
      currentLevel = nextLevel;
      nextLevel = 0;
    }
  }
}

template class BST<int>;
template class BST<double>;
template class BST<std::string>;
