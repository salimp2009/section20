#include <iostream>
#include <mutex>
#include <future>

// RECURSIVE MUTEX EXAMPLE; used yo avoid deadlocks
// recursive_mutex allows multiple locks by the same thread and 
// releases the lock when the last corresponding unlock() call is called:

class Database
{
private:
    std::recursive_mutex dbMutex;
    std::mutex db1Mutex;  // this Mutex is created to see a deadlock case
    
public:
    void createTable()
    {
        std::lock_guard<std::recursive_mutex>lg(dbMutex);
//      std::lock_guard<std::mutex>lg(db1Mutex);        // std::mutex is used to simulate a deadlock
        std::cout<<"\nCreating table....\n";              // but the function calling createtable should also
    }                                                     // also be using std::mutex for a deadlock situation

    void insertData()
    {
        std::lock_guard<std::recursive_mutex>lg(dbMutex);
        std::cout<<"\nInserting data....\n";
    }
    
    void createTableAndinsertData()
    {
        std::lock_guard<std::recursive_mutex>lg(dbMutex);
//      std::lock_guard<std::mutex>lg(db1Mutex);    // if std::mutex is used in both this function and 
        createTable();                              // if the called functionscreateTable or insertData uses also std::mutex
        insertData();                               // then 'deadlock'will occur 
                                                    // to avoid the deadlock std::recursive_mutex is an option
    }                                               // another option is to use std::unique_lock<>
};                                                  // std::unique_lock also knows when to or unlock whatever
                                                    // the type of mutex is; need to check whether Mutex is ready to lock
int main()                                          // by using bool() or std::lock() global function or .lock() member function
{
    Database db;
    db.createTableAndinsertData();

    std::cout<<"\nNoDeadLock with std::recursive_mutex...\n";
    std::cout<<'\n';
    
 return 0;
}