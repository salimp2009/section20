#include <iostream>
// Binary Tree Structure 
// Using Folding Expressions to Traverse the tree

struct Node 
{
    int value;
    Node* left;
    Node* right;
    Node(int v=0): value{v}, left{nullptr}, right{nullptr} { }
};

auto left=&Node::left;
auto right=&Node::right;

// Traverse tree; using fold expressions
template<typename T, typename... TP>
Node* traverse(T np, TP... paths) {
    return (np->* ... ->* paths);           // equals to; np->*paths1->*paths2->*...
}

int main()
{
    Node* root=new Node{0};                 // create a new binary tree on heap with root=0
    root->left=new Node{1};                 // create the left child node from parent root
    root->left->right=new Node{2};          // create the right child node of the left parent
    
    Node* node=traverse(root, left, right); // traverse from to left child to the right child
    
    std::cout<<node->value<<'\n';
    
    

 
    
    delete root;
 
 return 0;
}