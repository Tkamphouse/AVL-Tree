//---------------------------------------------------------------------------
// NAME: 
// DATE: Fall 2021
// DESC: 
//---------------------------------------------------------------------------

#ifndef AVLMAP_H
#define AVLMAP_H

#include "map.h"
#include "arrayseq.h"


template<typename K, typename V>
class AVLMap : public Map<K,V>
{
public:

  // default constructor
  AVLMap();

  // copy constructor
  AVLMap(const AVLMap& rhs);

  // move constructor
  AVLMap(AVLMap&& rhs);

  // copy assignment
  AVLMap& operator=(const AVLMap& rhs);

  // move assignment
  AVLMap& operator=(AVLMap&& rhs);  

  // destructor
  ~AVLMap();
  
  // Returns the number of key-value pairs in the map
  int size() const;

  // Tests if the map is empty
  bool empty() const;

  // Allows values associated with a key to be updated. Throws
  // out_of_range if the given key is not in the collection.
  V& operator[](const K& key);

  // Returns the value for a given key. Throws out_of_range if the
  // given key is not in the collection. 
  const V& operator[](const K& key) const;

  // Extends the collection by adding the given key-value
  // pair. Assumes the key being added is not present in the
  // collection. Insert does not check if the key is present.
  void insert(const K& key, const V& value);

  // Shrinks the collection by removing the key-value pair with the
  // given key. Does not modify the collection if the collection does
  // not contain the key. Throws out_of_range if the given key is not
  // in the collection.
  void erase(const K& key);

  // Returns true if the key is in the collection, and false otherwise.
  bool contains(const K& key) const;

  // Returns the keys k in the collection such that k1 <= k <= k2
  ArraySeq<K> find_keys(const K& k1, const K& k2) const;

  // Returns the keys in the collection in ascending sorted order
  ArraySeq<K> sorted_keys() const;  

  // Returns the height of the binary search tree
  int height() const;

  // helper to print the tree for debugging
  void print() const;
  
private:

  // node for avl tree
  struct Node {
    K key;
    V value;
    Node* left;
    Node* right;
    int height;
  };

  // number of nodes
  int count = 0;

  // root node
  Node* root = nullptr;

  // clean up the tree and reset count to zero given subtree root
  void make_empty(Node* st_root);

  // copy assignment helper
  Node* copy(const Node* rhs_st_root) const;
  
  // erase helper
  Node* erase(const K& key, Node* st_root);

  // insert helper
  Node* insert(const K& key, const V& value, Node* st_root);
  
  // find_keys helper
  void find_keys(const K& k1, const K& k2, const Node* st_root,
                 ArraySeq<K>& keys) const;

  // sorted_keys helper
  void sorted_keys(const Node* st_root, ArraySeq<K>& keys) const;

  // rotations
  Node* right_rotate(Node* k2);
  Node* left_rotate(Node* k2);
  
  // rebalance
  Node* rebalance(Node* st_root);

  // print helper
  void print(std::string indent, const Node* st_root) const;
  
};


template<typename K, typename V>
void AVLMap<K,V>::print() const
{
  print(std::string(""), root);
}


template<typename K, typename V>
void AVLMap<K,V>::print(std::string indent, const Node* st_root) const
{
  if (!st_root)
    return;
  std::cout << st_root->key << " (" << st_root->height << ")" <<  std::endl;
  if (st_root->left) {
    std::cout << indent << " lft: ";
    print(indent + " ", st_root->left);
  }
  if (st_root->right) {
    std::cout << indent << " rgt: ";
    print(indent + " ", st_root->right);
  }
}


//----------------------------------------------------------------------
// TODO: Implement the above functions below
//----------------------------------------------------------------------


#endif
