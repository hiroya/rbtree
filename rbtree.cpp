#include "rbtree.h"
#include <stdlib.h>
#include <time.h>

using namespace std;

RBTree::RBTree(){
}
RBTree::~RBTree(){
  deleteAll(_root);
}
void RBTree::deleteAll(Node *node){
  if(node != NULL){
    Node *leftNode = node->leftNode;
    Node *rightNode = node->rightNode;

    deleteAll(node->leftNode);
    deleteAll(node->rightNode);
    
    delete node;
  }

}
RBTree::Node* RBTree::initNode(int value){
  
  Node *node = new Node;
  node->value = value;
  node->leftNode = NULL;
  node->rightNode = NULL;
  node->color = RED; // when you insert new node, insert the node with RED

  return node;
}

void RBTree::insert(int value){
  _root = recursive_insertion(_root, value);
  _root->color = BLACK; // always black
}

RBTree::Node* RBTree::recursive_insertion(Node *node, int value){

  if(node == NULL){
    return initNode(value);
  }
  
  // right insertion
  if(node->value < value){
    node->rightNode = recursive_insertion(node->rightNode, value);
  // lef insertion
  }else if(node->value > value){
    node->leftNode = recursive_insertion(node->leftNode, value);
  }

  //right rotation
  if(is_red(node->rightNode)){ //2 nodes
    node = left_rotation(node);
  }
  // left rotation
  if(is_red(node->leftNode) && is_red(node->leftNode->leftNode)){ //3 nodes
    node = right_rotation(node);
  }
  // flip colors (RED -> BLACK, BLACK -> RED)
  if(is_red(node->leftNode) && is_red(node->rightNode)){ //split 4 nodes
    flip_colors(node);
  }
  
  return node; 
}

RBTree::Node* RBTree::left_rotation(Node *node){
  //left rotation
  cout << "left rotation: " << node->value << endl;
  Node *x = node->rightNode;
  node->rightNode = x->leftNode;
  x->leftNode = node;
  x->color = node->color;
  node->color = RED;
  
  return x;
}

RBTree::Node* RBTree::right_rotation(Node *node){
  //right rotation
  cout << "right rotation: " << node->value << endl;
  Node *x = node->leftNode;
  node->leftNode = x->rightNode;
  x->rightNode = node;
  x->color = node->color;
  node->color = RED;
  
  return x;
}

void RBTree::flip_colors(Node *node){
  node->color == RED?node->color = BLACK : node->color = RED;
  node->leftNode->color == RED?node->leftNode->color = BLACK : node->leftNode->color = RED;
  node->rightNode->color == RED?node->rightNode->color = BLACK : node->rightNode->color = RED;
}

bool RBTree::is_red(Node *node){
  return node != NULL && node->color == RED;
}

void RBTree::run_test(){
  print_node(_root, 0);
}

void RBTree::search(int value){
  RBTree::Node *node = recursive_search(_root, value);
  if(node != NULL){
    cout << "found!" << endl;
  }else{
    cout << "not found" << endl;
  }
}
RBTree::Node* RBTree::recursive_search(Node *node, int value){

  if(node != NULL){
    if(node->value > value){
      node = recursive_search(node->leftNode, value);
    }else if(node->value < value){
      node = recursive_search(node->rightNode, value);
    }else if(node->value == value){
      return node;
    }
  }

  return node;
}

void RBTree::print_node(Node *node, int height){
  if(node != NULL){
    print_node(node->rightNode, height + 1);
    int i = height;
    while(i > 0){
      cout << "       ";
      i--;
    }
    cout << (node->color == RED ? "R":"B") << ":" << node->value << "(" << height << ")" << endl;
    print_node(node->leftNode, height + 1);
  }
  
}

int RBTree::test_rb_properties(Node *node){
  if(node != NULL && node->color == RED){
    if(node->leftNode->color == RED || node->rightNode->color == RED){
      cout << "property violation error (1)" << endl;
      test_rb_properties(node->leftNode);
      test_rb_properties(node->rightNode);
      return -1;
    }
  }

  return 0;
}

//main
int main(int argc, char **argv){

  //int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  
  RBTree *rb = new RBTree;

  srand((unsigned)time(NULL));
  for(int i = 0; i < 100; i++){
    int n = rand() % 50000;
    rb->insert(n);
  }
  rb->run_test();

  
  int num;
  do{
    cout << "Enter an integer." << endl;
    cin >> num;
    rb->search(num);
  }while(num != 0);
  
  
  delete rb;
  
  return 0;
}
