#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <exception>

// Basic Thread & Detach Example
// DETACHED THREAD CAN BE EXTREMELY DANGEROUS and ERROR PRONE therefore try not use it !!!

// creating thread ID variable and 
// will assign it to masterthread (t1) in main to track only
std::thread::id masterThread;  

void doSomething(int num, char c)
{
    try {
        std::default_random_engine dre(42*c);
        std::uniform_int_distribution<int> id(10,1000);
        for(std::size_t i{0}; i<num; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(id(dre)));
            std::cout.put(c).flush();
            }
            if(std::this_thread::get_id()==masterThread) {
                std::cout<<"\nmasterThread: "<<masterThread<<'\n';
            } else {
                std::cout<<"\nactive thread: "<<std::this_thread::get_id()<<'\n';
            } 
                
    } catch(const std::exception& e) {                                 // catch Thread exception
        std::cerr<<"\nTHREAD_EXCEPTION: (thread: "
                <<std::this_thread::get_id()<<"), "<<e.what()<<'\n';     // get thread id
    } catch(...) {
        std::cerr<<"\nTHREAD_ EXCEPTION: (thread: "                   // catch Thread exception
                 <<std::this_thread::get_id()<<")\n";                 // get thread id
    } 
}

int main()
{
    try {
        // create a thread object t1 and assign functions; 
        // Threads are started right away no need for launch policy 
        //(callables, lamdas..etc) and arguments..
        std::thread t1(doSomething, 5, '.');                                //print 5 dots in seperate thread
        std::cout<<"- started foreground thread: "<<t1.get_id()<<'\n';      //print thread ID 
        masterThread=t1.get_id();
        
         // creating 5 seperate thread; each prints 5 of characters
        for(std::size_t i{0}; i<5; ++i) {
            std::thread t(doSomething, 5, 'a'+i);                                           
            std::cout<<"- detach thread started at background, thread: "<<t.get_id()<<'\n'; // print thread id
            t.detach();         // detach thread to background; no control over the thread 
                                // if main terminates or throws exception 
                                // before detached thread complete then all threads terminated
        }
        
        std::cin.get();        // wait for input (press return; enter)
        
        std::cout<<"\n-join foreground thread "<<t1.get_id()<<'\n';
        t1.join();            // wait for t1 thread to finish
        
        // class id has a default constructor that yields a unique ID representing “no thread”:
        std::cout<<"ID of \"nothread\":"<<std::thread::id()<<'\n';  // the value of this ID might change every time
                                                                    // use get_id() for a specifics thread ID 
                                                                    // or this_thread::get_id() for the active thread
                                                                    
    } catch(std::exception& e) {
        std::cerr<<"\nEXCEPTION: "<<"), "<<e.what()<<'\n';
                 
    } catch(...) {
        std::cerr<<"\nEXCEPTION: \n";
    }
    
    std::cout<<"\nFinishing main program..\n";

 return 0;
}


/* Beware of Detached Threads
Detached threads can easily become a problem if they use nonlocal resources. 
 * The problem is that you lose control of a detached thread and 
    have no easy way to find out whether and how long it runs. 
 * make sure that a detached thread does not access any objects after their lifetime has ended. 
 * passing variables and objects to a thread by reference is always a risk. 
 * Passing arguments by value is strongly recommended.
 * the lifetime problem also applies to global and static objects, because when the program exits,
  * the detached thread might still run, which means that it might access global or static objects 
  * that are already destroyed or under destruction. Unfortunately, this would result in undefined behavior.
    
So, as a general rule for detached threads, take into account the following:

• Detached threads should prefer to access local copies only.
• If a detached thread uses a global or static object, you should do one of the following:
– Ensure that these global/static objects are not destroyed before all detached threads accessing 
 * them are finished (or finished accessing them). One approach to ensure this is to use condition variables (see Section 18.6, page 1003), which the detached threads use to signal that they have finished. Before leaving main() or calling exit(), you’d have to set these condition variables then to signal that a destruction is possible.9
– End the program by calling quick_exit(), which was introduced exactly for this reason 
 * to end a program without calling the destructors for global and static objects (see Section 5.8.2, page 162)
 * std::cin, std::cout, and std::cerr and the other global stream objects (see Sec- tion 15.2.2, page 751)
    according to the standard “are not destroyed during program execution,” access to these objects 
    in detached threads should introduce no undefined behavior. However, other problems, 
    such as interleaved characters, might occur.
     
    Nevertheless, as a rule of thumb;
     * only safe way to terminate a detached thread is with one of the “...at_thread_exit()” functions, 
     * which force the main thread to wait for the detached thread to truly finish. 
     * “Detached threads is one of those things that should be moved into the chapter on dangerous features 
     * that almost no one needs.”
 */