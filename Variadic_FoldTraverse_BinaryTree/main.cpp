#include <iostream>
#include <memory>


struct Node {
    int value;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
//    Node* left;
//    Node* right;

    Node(int i=0): value{i}, left{nullptr}, right{nullptr} {}
};



auto left=&Node::left;
auto right=&Node::right;

// traverse works with raw pointers
template<typename T, typename... TP>
constexpr auto traverse(T np, TP... paths) {
    return (np ->* ... ->* paths);       // np ->* paths1 ->* paths2 ...
}






int main()
{
//    Node* root=new Node(0);
//    root->left=new Node(1);
//    root->left->right=new Node(2);
//    root->right=new Node(4);
//    root->right->left=new Node(45);
//    root->right->right=new Node(55);
    
    std::shared_ptr<Node> root=std::make_shared<Node>(0);
    root->left=std::make_shared<Node>(1);
    root->left->right=std::make_shared<Node>(2);
    
        
    std::cout<<root->value<<'\n';
    std::cout<<root->left->value<<'\n';
    std::cout<<root->left->right->value<<'\n';
    
    std::cout<<(&left)<<'\n';
 
//    std::cout<<root->right->value<<'\n';
//    std::cout<<root->right->right->value<<'\n';
//    std::cout<<root->right->left->value<<'\n';


//   auto node=traverse(root, left, right);
//    
//    auto node2=traverse(root, right, left);
//    
//    std::cout<<node->value<<'\n';
//    std::cout<<node2->value<<'\n';
//    

// if raw pointers used all nodes created on the heap needs to be deleted    
// before the program ends; root has to be deleted last ; 
// all sub childs has to be deleted first then the parents
//      delete root->left->right;
//      delete root->left;     
//      delete root->right->right;
//      delete root->right->left;
//      delete root;                // delete the root last

    return 0;
}
