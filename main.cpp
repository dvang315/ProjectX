
#include "RedBlack.h"
#include <iostream>
#include <chrono>

using namespace std;

// Colors for the nodes
//enum COLOR { RED, BLACK };

int main()
{
  RedBlackTree tree;

  tree.insert(7);
  tree.insert(3);
  tree.insert(18);
  tree.insert(10);
  tree.insert(22);
  tree.insert(8);
  tree.insert(11);
  tree.insert(26);
  tree.insert(2);
  tree.insert(6);
  tree.insert(13);

  tree.printInOrder();
  tree.printLevelOrder();

  cout<<endl<<"Deleting 18, 11, 3, 10, 22"<<endl;

  tree.deleteNode(18);
  tree.deleteNode(11);
  tree.deleteNode(3);
  tree.deleteNode(10);
  tree.deleteNode(22);

  tree.printInOrder();
  tree.printLevelOrder();
  return 0;
}


/*
int main()
{

    // record start time
    auto start = chrono::high_resolution_clock::now();

    RedBlackTree x;
    for (int i = 0; i < 1000000; i++) {
        x.insert(i);
    }

    cout << x.searchTree(100000) << endl;

    // record end time
    auto finish = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = finish - start;
    cout << "Elapsed time: " << elapsed.count() << " s\n";

    return 0;
}
*/
