/*
    RedBlack.cpp

    Implementation File for Red-Black Class

*/
//=================================================
#include "RedBlack.h"

//=================================================
// Inserts new node to tree
void RedBlackTree::insert(int n)
{
  Node* newNode = new Node(n);
  if(root == nullptr)
  {
    // Inserts Data at root
    newNode->color = BLACK;
    root = newNode;
  }
  else
  {
    Node *temp = search(n);

    if(temp->data == n)
    {
      // Returns if data already exists
      return;
    }

    // If data not found; Search returns node where data is to be inserted
    // Connect new node to correct node
    newNode->parent = temp;

    if(n < temp->data)
    {
      temp->leftChild = newNode;
    }
    else
    {
      temp->rightChild = newNode;
    }

    // Fix RED RED Violation
    fixRedRed(newNode);
  }
}

// Function Deletes node with given data
void RedBlackTree::deleteNode(int n)
{
  if(root == nullptr)
  {
    // Tree is empty
    return;
  }

  Node* v = search(n);
  Node* u;

  if(v->data != n)
  {
    cout << "No node found to delete with data: " << n << endl;
    return;
  }

  deleteNodeHelper(v);
}

// Prints Inorder of the tree
void RedBlackTree::printInOrder()
{
  cout << "Inorder: " << endl;
  if(root == nullptr)
  {
    cout << "Tree is empty" << endl;
  }
  else
  {
    inOrderHelper(root);
  }
  cout << endl;
}

// Prints Lvl Order of tree
void RedBlackTree::printLevelOrder()
{
  cout << "Level Order: " << endl;
  if(root == nullptr)
  {
    cout << "Tree is empty" << endl;
  }
  else
  {
    levelOrderHelper(root);
  }
  cout << endl;
}
