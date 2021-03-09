/*
    RedBlack.h

    Declaration File for Red-Black Class

*/
//===========================================
#ifndef REDBLACK_H_INCLUDED
#define REDBLACK_H_INCLUDED


//===========================================
// Included Dependencies
#include "Node.h"
#include <iostream>
#include <queue>

using std::cout;
using std::endl;
using std::queue;
//===========================================
class RedBlackTree
{
private:
  // root of tree
  Node* root;

protected:
  // Rotates Given Node Left
  void rotateLeft(Node* x)
  {
    // New parent will be x's right child
    Node* tempNode = x->rightChild;

    // Updates root if current node is root
    if (x == root)
    {
      root = tempNode;
    }
    x->moveDown(tempNode);

    // Connects x with new parent's left child
    x->rightChild = tempNode->leftChild;

    // Connects new parent's left child with node if it isn't NULL
    if(tempNode->leftChild != nullptr)
    {
      tempNode->leftChild->parent = x;
    }
    // Connects new parent with x
    tempNode->leftChild = x;
  }

  // Rotates Given Node Right
  void rotateRight(Node* x)
  {
    // New parent will be x's left child
    Node* tempNode = x->leftChild;

    // updates root if current node is root
    if(x == root)
    {
      root = tempNode;
    }
    x->moveDown(tempNode);

    // Connects x with new parent's right child
    x->leftChild = tempNode->rightChild;

    // Connects new parent's right child with node if it isn't NULL
    if(tempNode->rightChild != nullptr)
    {
      tempNode->rightChild->parent = x;
    }
    // Connects new parent with x
    tempNode->rightChild = x;
  }

  // Swaps color of two nodes
  void swapColors(Node* col1, Node* col2)
  {
    bool temp;
    temp = col1->color;
    col1->color = col2->color;
    col2->color = temp;
  }

  // Swaps Values/Data between two nodes
  void swapData(Node* x, Node* v)
  {
    int temp;
    temp = x->data;
    x->data = v->data;
    v->data = temp;
  }

  // Fix R-R at given node
  void fixRedRed(Node* x)
  {
    // If x is root; Color BLACK and return
    if(x == root)
    {
      x->color = BLACK;
      return;
    }

    // Initialize parent, grandparent, & uncle
    Node* parent = x->parent;
    Node* grandparent = parent->parent;
    Node* uncle = x->uncle();

    if(parent->color != BLACK)
    {
      if(uncle != nullptr && uncle->color == RED)
      {
        // Uncle is red; Recolor and Recurse
        parent->color = BLACK;
        uncle->color = BLACK;
        grandparent->color = RED;
        fixRedRed(grandparent);
      }
      else
      {
        // Perform LR, LL, RL, RR
        if(parent->isOnLeft())
        {
          if(x->isOnLeft())
          {
            // For LR
            swapColors(parent, grandparent);
          }
          else
          {
            rotateLeft(parent);
            swapColors(x, grandparent);
          }
          // For LL & LR
          rotateRight(grandparent);
        }
        else
        {
          if(x->isOnLeft())
          {
            // For RL
            rotateRight(parent);
            swapColors(x, grandparent);
          }
          else
          {
            swapColors(parent, grandparent);
          }

          // For RR & RL
          rotateLeft(grandparent);
        }
      }
    }
  }

  // Finds node that has no left child in subtree of given node
  Node* successor(Node* x)
  {
    Node* temp = x;

    while (temp->leftChild != nullptr)
    {
      temp = temp->leftChild;
    }

    return temp;
  }

  // Finds node that replaces deleted node in BST
  Node* BSTreplace(Node* x)
  {
    // 2 Children
    if(x->leftChild != nullptr and x->rightChild != nullptr)
    {
      return successor(x->rightChild);
    }

    // Leaf
    if(x->leftChild == nullptr and x->rightChild == nullptr)
    {
      return nullptr;
    }

    // 1 Child
    if(x->leftChild != nullptr)
    {
      return x->leftChild;
    }
    else
    {
      return x->rightChild;
    }
  }

  // Deletes Given Node
  void deleteNodeHelper(Node* v)
  {
    Node* u = BSTreplace(v);

    // True when u and v are both BLACK
    bool uvBLACK = ((u == nullptr || u->color == BLACK) && (v->color == BLACK));
    Node* parent = v->parent;

    if(u == nullptr)
    {
      // u is NULL, so v is Leaf
      if(v == root)
      {
        // v is root, making root NULL
        root = nullptr;
      }
      else
      {
        // u & v; both BLACK
        if(uvBLACK)
        {
          // v is Leaf; Fix double BLACK at v
          fixDoubleBlack(v);
        }
        else
        {
          // u or v is RED
          if(v->sibling() != nullptr)
          {
            // sibling is not NULL, make it RED
            v->sibling()->color = RED;
          }
        }

        // Delete v from tree
        if(v->isOnLeft())
        {
          parent->leftChild = nullptr;
        }
        else
        {
          parent->rightChild = nullptr;
        }
      }
      delete v;
      return;
    }

    else if(v->leftChild == nullptr || v->rightChild == nullptr)
    {
      // v - 1 Child
      if(v == root)
      {
        // v is root; Assign data of u to v & delete u
        v->data = u->data;
        v->leftChild = v->rightChild = nullptr;
        delete u;
      }
      else
      {
        // Detach v from tree & move u up
        if(v->isOnLeft())
        {
          parent->leftChild = u;
        }
        else
        {
          parent->rightChild = u;
        }
        delete v;
        u->parent = parent;
        if (uvBLACK)
        {
          // u & v both BLACK; Fix double BLACK at u
          fixDoubleBlack(u);
        }
        else
        {
          // u or v is RED; Color u BLACK
          u->color = BLACK;
        }
      }
      return;
    }
    else
    {
      // v - 2 Children; swap data with Successor and Recurse
      swapData(u, v);
      deleteNodeHelper(u);
    }
  }

  void fixDoubleBlack(Node* x)
  {
    if(x == root)
    {
      // Reached root
      return;
    }

    Node* sibling = x->sibling();
    Node* parent = x->parent;

    if(sibling == nullptr)
    {
      // No Sibling; Double BLACK pushed up
      fixDoubleBlack(parent);
    }
    else
    {
      if(sibling->color == RED)
      {
        // Sibling RED
        parent->color = RED;
        sibling->color = BLACK;
        if(sibling->isOnLeft())
        {
          // Left Case
          rotateRight(parent);
        }
        else
        {
          // Right Case
          rotateLeft(parent);
        }
        fixDoubleBlack(x);
      }
      else
      {
        // Sibling BLACK
        if(sibling->hasRedChild())
        {
          // Atleast 1 RED Child
          if(sibling->leftChild != nullptr && sibling->leftChild->color == RED)
          {
            if(sibling->isOnLeft())
            {
              // LL
              sibling->leftChild->color = sibling->color;
              sibling->color = parent->color;
              rotateRight(parent);
            }
            else
            {
              // RL
              sibling->leftChild->color = parent->color;
              rotateRight(sibling);
              rotateLeft(parent);
            }
          }
          else
          {
            if(sibling->isOnLeft())
            {
              // LR
              sibling->rightChild->color = parent->color;
              rotateLeft(sibling);
              rotateRight(parent);
            }
            else
            {
              // RR
              sibling->rightChild->color = sibling->color;
              sibling->color = parent->color;
              rotateLeft(parent);
            }
          }
          parent->color = BLACK;
        }
        else
        {
          // 2 BLACK Children
          sibling->color = RED;
          if(parent->color == BLACK)
          {
            fixDoubleBlack(parent);
          }
          else
          {
            parent->color = BLACK;
          }
        }
      }
    }
  }

  // Prints Lvl Order
  void levelOrderHelper(Node* x)
  {
    if(x == nullptr)
    {
      // Return if node is NULL
      return;
    }

    // Queue for Lvl Order
    queue <Node*> q;
    Node *curr;

    // Push x
    q.push(x);

    while(!q.empty())
    {
      // Dequeue
      curr = q.front();
      q.pop();

      // Print Node Data
      cout << curr->data << " ";

      // Push Children to Queue
      if(curr->leftChild != nullptr)
      {
        q.push(curr->leftChild);
      }
      if(curr->rightChild != nullptr)
      {
        q.push(curr->rightChild);
      }
    }
  }

  // Traverse tree in Inorder
  void inOrderHelper(Node* x)
  {
    if (x == nullptr)
    {
      return;
    }

    inOrderHelper(x->leftChild);
    cout << x->data << " ";
    inOrderHelper(x->rightChild);
  }

  Node* searchTreeHelper(Node* node, int key)
  {
      if(node == nullptr || key == node->data)
      {
          return node;
      }
      else if(key < node->data)
      {
          return searchTreeHelper(node->leftChild, key);
      }
      else
      {
          return searchTreeHelper(node->rightChild, key);
      }
  }

public:
  // Default Constructor
  RedBlackTree()
  {
    root = nullptr;
  }

  // Function Call for root
  Node* getRoot()
  {
    return root;
  }

  // Searches for Given Data
  // If found returns node (used for delete)
  // Else returns last node while traversing (used in insert)
  Node* search(int n)
{
  Node* temp = root;
  while(temp != nullptr)
  {
    if(n < temp->data)
    {
      if(temp->leftChild == nullptr)
      {
        break;
      }
      else
      {
        temp = temp->leftChild;
      }
    }
    else if(n == temp->data)
    {
      break;
    }
    else
    {
      if(temp->rightChild == nullptr)
      {
        break;
      }
      else
      {
        temp = temp->rightChild;
      }
    }
  }

  return temp;
}

  // Searches Tree for node
  bool searchTree(int n)
  {
    Node* temp = searchTreeHelper(this->root, n);

    if(temp == nullptr)
    {
      return 0;
    }
    else if(temp->data == n)
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }

  // Inserts new node to tree
  void insert(int);

  // Function Deletes node with given data
  void deleteNode(int);

  // Prints Inorder of the tree
  void printInOrder();

  // Prints Lvl Order of tree
  void printLevelOrder();
};


#endif REDBLACK_H_INCLUDED
