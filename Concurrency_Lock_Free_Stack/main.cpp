#include <iostream>
#include <atomic>
#include <thread>
#include <memory>
#include <cstdio>
//#include <core.h>
//#include <format.h>
//#include <format-inl.h>


// Example from C++ Concurrency in Action 2nd Version and made some modifications

template<typename T>
class lock_free_stack
{
private:
  struct Node {
      std::shared_ptr<T>data;
      Node* next;
      Node(T data): data{std::make_shared<T>(std::move(data))}, next{nullptr} {}
  };
  
  std::atomic<Node*>head; 
  std::atomic<unsigned>threads_in_pop;      // counter to determine threads in pop()
  std::atomic<Node*>to_be_deleted;
  
static void delete_nodes(Node* nodes) {
		while (nodes) {
			Node* next = nodes->next;
			delete nodes;
			nodes = next;
		}
	}
	
	void try_reclaim(Node* old_head) 
	{
		if (threads_in_pop == 1) 
		{																// first check if there is only one thread
			Node* nodes_to_delete = to_be_deleted.exchange(nullptr);	// if only thread, deletion is safe so change the value of atomic to nullptr
			if (!--threads_in_pop) 
			{
				delete_nodes(nodes_to_delete);						   // check if there are any threads after the first check; if none then safe to delete
			}
			else if (nodes_to_delete) 
			{
				chain_pending_nodes(nodes_to_delete);
			}
			delete old_head;
		}
		else
		{
			chain_pending_node(old_head);
			--threads_in_pop;
		}
	}

	void chain_pending_nodes(Node* nodes) 
	{
		Node* last = nodes;
		while (Node* const next = last->next)
		{
			last = next;
		}
		chain_pending_nodes(nodes, last);
	}
	
	void chain_pending_nodes(Node* first, Node* last)
	{
		last->next = to_be_deleted;
		while (!to_be_deleted.compare_exchange_weak(last->next, first));
	}

	void chain_pending_node(Node* n) 
	{
		chain_pending_nodes(n, n);
	}
  
public:
    lock_free_stack()=default;
    
    void push(T data) 
    {
        auto const new_node=new Node(std::move(data));
        new_node->next=head.load();
        // check if the head has not changed by another thread, if true and replace the head with the new node
        while(!head.compare_exchange_weak(new_node->next, new_node));   
    }
    
    std::shared_ptr<T> pop() 
    {
        ++threads_in_pop;
        Node* old_head=head.load();
        while(old_head && !head.compare_exchange_weak(old_head, old_head->next)); 
        std::shared_ptr<T>res;                            // create shared pointer to store the data before deleting old_head
        if(old_head) res.swap(old_head->data);               // store the data in res
        try_reclaim(old_head);                               // send old_head to delete list ; to avoid leaks;
        //auto delete_ptr=std::make_unique<Node>(old_head);  // alternative to reclaim ; if a unique_ptr own the old_head
                                                             // it might delete the old head upon exit automatically
        return res;                                          // return the old_head->data stored in res
    }
    
    const std::shared_ptr<T> get_head() const& { return head.load()->data;}

};


int main()
{
    lock_free_stack<int> lockfreeStack;
    
    lockfreeStack.push(20);
    lockfreeStack.push(30);
    printf("head=%02i\n", *lockfreeStack.get_head());
    
//     this causes exception error; when the function static void delete_nodes(Node* nodes) 
//     tries to assign nodes=next after deleting nodes ???????
 
//     lockfreeStack.pop();
//    printf("new head=%02i\n", *lockfreeStack.get_head());

//lock_free_stack<int>lf_stack;
//	std::thread t2(&lock_free_stack<int>::push, &lf_stack, 20);
//	std::thread t1(&lock_free_stack<int>::push, &lf_stack, 10);
//	std::thread t3(&lock_free_stack<int>::pop, &lf_stack);
//
//	t1.join();
//	t2.join();
//	t3.join();

    return 0;
}
