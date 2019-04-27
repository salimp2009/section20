#include <iostream>
#include <thread>
#include <atomic>
#include <cassert>
#include <memory>

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
        std::shared_ptr<T> data;
        node* next;
        node(T const& data): data{std::make_shared<T>(data)} { }
    };
    std::atomic<node*>head;
public:
    void push(T const& data) {
        node* const new_node=new node(data);
        new_node->next=head.load();
        while(!head.compare_exchange_weak(new_node->next, new_node));
    }
    
    std::shared_ptr<T> pop() {
        assert(head!=nullptr);
        node* old_head=head.load();
        while(old_head && !head.compare_exchange_weak(old_head, old_head->next));
        return old_head ? old_head->data : std::shared_ptr<T>();
    }
    
    
 
};
    


int main()
{
    lock_free_stack<int>lf_stack;
    std::thread t2(&lock_free_stack<int>::push, &lf_stack, 20);
    std::thread t1(&lock_free_stack<int>::push, &lf_stack, 10);
    std::thread t3(&lock_free_stack<int>::pop, &lf_stack);
    
    
    t1.join();
    t2.join();
    t3.join();
    
    std::cout<<*(lf_stack.pop())<<'\n';
    
 return 0;
}