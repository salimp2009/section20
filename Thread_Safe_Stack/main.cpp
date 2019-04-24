#include <iostream>
#include <thread>
#include <atomic>

// Under Progress!!!!!!

// Example for Lock Free Stack from book Concurency in Action
// UNDER CONSTRUCTION; the example is not finished;
    // - needs pop() function
    // - needs to delete pointer on the heap
    // = needs memory_order semantics applied for better performance
// Lock free but it is not wait free since atomic.compare_exchange_weak() can fail constantly    

template<typename T>
class lock_free_stack {
private:
    struct node 
    {
        T data;
        node* next;
        node(T const& data): data{data} { }
    };
    std::atomic<node*>head;
public:
    void push(T const& data) {
        node* const new_node=new node(data);
        new_node->next=head.load();
        while(!head.compare_exchange_weak(new_node->next, new_node));
    } 
};
    


int main()
{
    

 
 return 0;
}