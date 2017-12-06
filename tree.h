#ifndef TREE_H
#define TREE_H

  // Each node is either a leaf or a nonleaf.  Type
  // NodeKind has just two values: leaf and nonleaf.

  enum NodeKind {leaf, nonleaf};

  // An object of type Node is node in a Huffman tree.
  // The variables are as follows.
  //
  // kind   tells whether the node is a leaf.
  //
  // ch     is the character stored in a leaf.
  //        It should only be used for leaves.
  //
  // left
  // right  These are the left and right subtrees.
  //        They should only be used for nonleaves.

  struct Node 
  {
    NodeKind kind;
    char     ch;
    Node*    left;
    Node*    right;

    // Create a leaf holding character c.

    Node(char c)
    {
      kind = leaf;
      ch   = c;
    }

    // Create a nonleaf with left subtree L
    // and right subtree R.

    Node(Node* L, Node *R)
    {
      kind  = nonleaf;
      left  = L;
      right = R;
    }      
  };

  typedef Node* Tree;

#endif
