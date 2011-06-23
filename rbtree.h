/*
 * rbtree.h
 * An implementation of LLRB
 */

#include <iostream>

class RBTree{

 public:
  enum Color{
    RED,
    BLACK
  };
  
  struct Node{
    Color color;
    Node *leftNode;
    Node *rightNode;
    Node *parent;
    int value;
  };
  
 public:
  RBTree();
  ~RBTree();
  void insert(int value);
  void search(int value);

  //debug
  void run_test();
  
 private:
  Node *_root;
  Node* initNode(int value);

  //insert
  Node* recursive_insertion(Node *parent, int value);
  Node* right_rotation(Node *node);
  Node* left_rotation(Node *node);
  bool is_red(Node *node);
  void flip_colors(Node *node);

  //search
  Node* recursive_search(Node *node, int value);

  //delete all memory allocated
  void deleteAll(Node *root);
  
  //debug
  void print_node(Node *node, int height);
  int test_rb_properties(Node *node);
};
