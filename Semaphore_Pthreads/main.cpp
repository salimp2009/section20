#include <iostream>
#include <pthread.h>
#include <thread>

// Basic class to create a Semaphore;

class Semaphore 
{
private:
    int               m_count;
    pthread_mutex_t   m_mutex;
    pthread_cond_t    m_cv;
public:
 explicit Semaphore(int initialCount)
 {
     m_count=initialCount;
     pthread_mutex_init(&m_mutex, nullptr);
     pthread_cond_init(&m_cv, nullptr);
 }
 
 void take()
 {
     pthread_mutex_lock(&m_mutex);
     //put the thread to sleep as long as
     //the count is zero
     while(m_count==0) 
        pthread_cond_wait(&m_cv, &m_mutex);
    --m_count;
    pthread_mutex_unlock(&m_mutex);
 }
 
 void give()
 {
     pthread_mutex_lock(&m_mutex);
     ++m_count;
     // if the count was zero before the 
     // increment, wake up a waiting thread
     if(m_count==1)
         pthread_cond_signal(&m_cv);
    pthread_mutex_unlock(&m_mutex);
 }

};

Semaphore semaphore{3};
//sem_t g_semUsed;                // POSIX semaphores; not used in the example
//sem_t g_semFree;                // POSIX semaphores; not used in the example

void workonResource() {
    semaphore.take();                                             // lock the critical section
    // shared resource
    std::cout<<"\nThread ID: "<<std::this_thread::get_id();  // do critical operations
    std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // just to experiment 
    semaphore.give();                                           // unlock so other threads can use it   
}

int main()
{
    std::thread t1(workonResource);
    std::thread t2(workonResource);
    std::thread t3(workonResource);
    std::thread t4(workonResource);
    std::cout<<"\nMain thread is also working...\n";
    
    t1.join();
    t2.join();
    t3.join();
    t4.join();
     std::cout<<"\nProgram finished...\n";

 return 0;
}