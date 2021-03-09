/*
    Node.hpp

    Declaration File for Node Class

*/
//=========================================
#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

//=========================================
// Colors for the nodes
enum COLOR { RED, BLACK };

class Node
{
public:
  int data;
  bool color;
  Node* parent;
  Node* leftChild;
  Node* rightChild;


  Node(int data) // ": data(data)" <-- Could be used (erase "this->" pters"
  {
    this->data = data;
    parent = nullptr;
    leftChild = nullptr;
    rightChild = nullptr;

    // Node is created & is red at insertion
    this->color = RED;
  }

  // Returns pter to Uncle Node
  Node* uncle()
  {
    // If no Parent/Grandparent, then no Uncle
    if(parent == nullptr || parent->parent == nullptr)
    {
      return nullptr;
    }

    if(parent->isOnLeft())
    {
      // Uncle on rightChild
      return parent->parent->rightChild;
    }
    else
    {
      // Uncle on leftChild
      return parent->parent->leftChild;
    }
  }

  // Checks if node is Left Child
  bool isOnLeft()
  {
    return this == parent->leftChild;
  }

  // Returns pter to Sibling Node
  Node* sibling()
  {
    // If no Parent then Sibling NULL
    if(parent == nullptr)
    {
      return nullptr;
    }

    if(isOnLeft())
    {
      return parent->rightChild;
    }

    return parent->leftChild;
  }

  // Moves node down and moves Given Node in its place
  void moveDown(Node* tempNode)
  {
    if(parent != nullptr)
    {
      if(isOnLeft())
      {
        parent->leftChild = tempNode;
      }
      else
      {
        parent->rightChild = tempNode;
      }
    }
    tempNode->parent = parent;
    parent = tempNode;
  }

  bool hasRedChild()
  {
    return(leftChild != nullptr && leftChild->color == RED) || (rightChild != nullptr && rightChild->color == RED);
  }
};


#endif //NODE_H_INCLUDED
