#include <iostream>
#include <algorithm>
#include <list>
#include <forward_list>
#include <vector>
#include <numeric>
#include <iterator>
#include <deque>
#include <array>
#include <tuple>
#include <string>
#include <typeinfo>
#include <type_traits>
#include <functional>
#include <numeric>
template<typename T, class Cont=std::vector<int>>
void display(Cont elem)
{
   for(const T& i:elem)
        std::cout<<i<<" ";
    std::cout<<'\n';
}

// second version of display for any container
// No need to pass type info; auto deduces the type from passed container
// this is more efficient that the previous one
template<typename Cont>
void display2(Cont elem)
{
    for(const typename Cont::value_type & i: elem)  // alternative wat determining the Container type by using type_traits
    //for(const auto& i:elem)                       // using auto to create a iterator & determine the type of container 
        std::cout<<i<<" ";
    std::cout<<'\n';
}

// templated find before function for Forward_Lists
// forward list does not have interface to insert before or other 'before' operations
// find before search thru the list and once the Predicate lambda returns true
// it returns an iterator to the position before the item
template<typename InputIterator, typename Pred>
InputIterator find_before_if(InputIterator first, InputIterator last, Pred pred)
{
    if(first==last) return first;
    InputIterator next{first};
    ++next;
    while(next!=last && !pred(*next)) {
        ++next;
        ++first;
    }   
    return first;
}

void STL_Array()
{
    std::cout<<"-------------------STL Array-------------------------\n";
    // default constructor does not create empty container
    // therefore for fundemantal types the initial value might be undefined
    // when nothing is passed to initialize;
    // alternative std::array<int, 5>x{}
    std::array<int, 5>arr1{1,3,5,7, 9};
    std::copy(arr1.begin(), arr1.end(),
            std::ostream_iterator<int>(std::cout, " "));
    
    
    std::array<int, 5>arr2{};
    std::cout<<'\n';
    for(const auto& elem:arr2)
        std::cout<<elem<<" ";
    std::cout<<'\n';
    
    display<int>(arr1);
    
    // Since C++17 automatic type and size deduction from arguments is OK
    std::array arr3{10,20,30,40};
    for(const auto& elem:arr3)
        std::cout<<elem<<" ";
    std::cout<<'\n';
    
    std::cout<<"original addresses of arr1 elements: \n";
    for(const auto& elem:arr1)
        std::cout<<&elem<<" ";
    std::cout<<'\n';
    
    arr2=std::move(arr1);
     for(const auto& elem:arr2)
        std::cout<<elem<<" ";
    std::cout<<'\n';
    
    std::cout<<"addresseses of arr2 & arr1 elements after arr2=std::move(arr1):  \n";
    for(const auto& elem:arr2)          // the address of arr2 element are still same only values are changes
        std::cout<<&elem<<" ";
    std::cout<<'\n';
    
    for(const auto& elem:arr1)          // the addresses of arr1 elements are still valid
        std::cout<<&elem<<" ";
    std::cout<<'\n';
    
    arr1[2]=300;                        // direct access but no range check better to use .at() for range checnking
   // arr1.at(8);                       // runtime range checking ; throws exception
    std::cout<<arr1[8]<<'\n';           // no range cheking; not safe to use directly better to use with assert to check range             
    
    std::cout<<arr1[2]<<'\n';
    
    //std::get<>() helper function is defined in <array> but also it is in <iterator> as well
    std::cout<<std::get<2>(arr1)<<'\n';
    std::cout<<arr2.front()<<", "<<arr2.back()<<'\n';   
    // Note: The effect of calling front() or back() on a zero-sized array is undefined
    
    // std::array<> uses std::tuple<> interface so some of the commands can be used for arrays;
    // tuple_size<>::value, tuple_element<>::type and std::get<>
    
    typedef std::array<std::string, 5> String_Array;        // create an alias 
    
    String_Array arr4={"Salim", "Didem", "Demir", "Sema"};
    
    std::cout<<"std::tuple_size<>::value: "<<std::tuple_size<decltype(arr4)>::value<<'\n';
    
    std::cout<<typeid(std::tuple_element<1, String_Array>::type).name()<<'\n';
    
    // Example to apply transform algo on std::array<>;
    // multiply each element of container 1 with container 2 and write to destination container
    
    // creating an alias T and determine the type from another array using tuple_element interface
    // the value inside tuple_element<0,...> refers to element since tuples can have different types of elements
    // for array it refers to array elements also but it will always be same since array elements are one type only
    // and that value cannot be equal or greater than size of the array size
    typedef std::tuple_element<0, decltype(arr1)>::type T;
    
    // creating and empty array of type with the size info of another array
    std::array<T, arr1.size()>arr1_2;          
    
    // testing...
    std::cout<<"arr1_2.size()"<<arr1_2.size()<<", arr1.begin(): "<<*arr1.begin()<<'\n';
    
    std::cout<<typeid(std::tuple_element<0, decltype(arr1)>::type).name()<<'\n';
    
    auto result=std::accumulate(arr1.begin(), arr1.end(), 0);
    
    std::cout<<"Accumulate result : "<<result<<'\n';
    std::transform(arr1.begin(), arr1.end(),                // source 1 container
                   arr2.begin(),                            // source 2 container
                   arr1_2.begin(),                          // destination container
                 //  std::multiplies<int>());
                    [](int x, int y){ return x*y;});      // operation to be applied on each member of source1 & source2 
                                                        // the returned value will be inserted into destination containr
    std::cout<<"arr1_2: ";
    int pos{0};
    for(const auto& elem:arr1_2) {
        ++pos;
        std::cout<<elem<<(pos<5 ?  ' ': '\n');
    }
    

}

void STL_Vector()
{
    std::cout<<"-------------------STL Vector-------------------------\n";
    std::vector<int>vec1(80, 20);               // creates a vector with 80 elements  with a value of 20   
    std::cout<<vec1.capacity()<<'\n';       // check number of elements with default allocator    
    vec1.reserve(100);
    std::cout<<vec1.capacity()<<'\n';       // return the number of elements that can be held 
    auto p=vec1.data();                      // data() return the underlying element for storage; 
                                            // it returns a pointer
    std::cout<<*p<<'\n';                    // print the first element similar to vec1[0]
    *p=50;                                  // change the value of first element
     *(p+1)=100;                            // access and change the 2nd element                            
    for(const auto& v:vec1)
        std::cout<<v<<" ";
        
    
    std::cout<<std::boolalpha<<std::is_pointer<decltype(p)>::value<<'\n';   // return true
    
    std::cout<<'\n';
}

void STL_Deque()
{   // A deque is similar to vector but composed of individual blocks and open at end and front
/*  a deque should be preferred if the following are true:
//  • You insert and remove elements at both ends (this is the classic case for a queue).
//    Accessing elements and iterating is a little bit slower 
//  • You don’t refer to elements of the container. (remove/insert other than at end or front 
      invalidates iterators
//  • It is important that the container frees memory when it is no longer used (however, the standard
//    does not guarantee that this happens).
//  In systems that have size limitations for blocks of memory (for example, some PC systems),
//  a deque might contain more elements because it uses more than one block of memory. 
//  Thus, max_size() might be larger for deques.
*/
    std::cout<<"-------------------STL Deque-------------------------\n";
    std::deque<int>deq1{10,20,40,50};
    for(const auto& i:deq1)
        std::cout<<i<<" ";
     std::cout<<'\n';
     
     display<int>(deq1);
   
    std::deque<std::string> coll;
    coll.assign({"Salim", "Didem", "Demir","Sema"});
    for(const auto& i:coll)
        std::cout<<i<<" ";
     std::cout<<'\n';
    
    coll.push_front("Semsi");
    coll.push_back("Pamukcu Family");
    for(const auto& i:coll)
        std::cout<<i<<" ";
     std::cout<<'\n';
     
    coll.pop_front();       // removes the element but does not return anything
    coll.pop_back();
    coll[0].at(0)='s';
    std::transform(coll.begin(), coll.end(),
                    coll.begin(),
                    [](auto s){ return s+" Pamukcu";});
    
    for(const auto& i:coll)
        std::cout<<i<<" ";
     std::cout<<'\n';
     
     std::cout<<"Coll size(): "<<coll.size()<<", max_size: "<<coll.max_size()<<'\n';
     coll.shrink_to_fit();
     std::cout<<"\nmax_size: "<<coll.max_size()<<'\n';
     
     coll.resize(6,"Semsi Pamukcu");            // resize to a given number of elements; if new
                                                // elements to be added then the given value assigned to element
     std::copy(coll.begin(), coll.end(),
            std::ostream_iterator<std::string>(std::cout, "\n"));
    std::cout<<'\n';
}

void STL_List()
{
// A list manages its elements as a doubly linked list
/* a list differs in several major ways from arrays, vectors, and deques:
//  • A list does not provide random access. For example, to access the fifth element, you must navigate the first four elements, following the chain of links. Thus, accessing an arbitrary element using a list is slow. However, you can navigate through the list from both end. So accessing both
//    the first and the last elements is fast.
//  • Inserting and removing elements is fast at each position (provided you are there), and not only at
//    one or both ends. You can always insert and delete an element in constant time, because no other
//    elements have to be moved. Internally, only some pointer values are manipulated.
//  • Inserting and deleting elements does not invalidate pointers, references, and iterators to other
//    elements.
//  • A list supports exception handling in such a way that almost every operation succeeds or is a
//   no-op. Thus, you can’t get into an intermediate state in which only half of the operation is complete.
    
     */
    std::cout<<"-------------------STL List-------------------------\n";
    std::list<int>list1(10);                            // create a list with 10 elements initialises with zero
    std::iota(list1.begin(), list1.end(), 3);           // if the list has no element list1.begin() and list1.end() will give runtime error 
    display<int>(list1);
    
    std::list<int>list2(10);
    std::iota(list2.rbegin(), list2.rend(), 3);
    
    display<int>(list2);
    
    auto it1=std::find(list1.begin(), list1.end(), 7);              // finds specfified value and return the position
    list1.insert(it1,100);                                          // insert the given element in front of the given position
    
    list1.insert(std::find(list1.begin(), list1.end(), 100), 300);  // alternative way combining insert and find
    display<int>(list1);                                    
    
    std::cout<<"Position of "<<*it1<<" did not change"<<'\n';       // adding or removing does not invalidate iterators
    
    std::advance(it1,-2);                                           // helper function for iterator moving from a given position to
    std::cout<<"Iterator moved to 2 elements front:"<<*it1<<'\n';   // advance changes the position of the iterator                                                           // number of element it can forward or backwards depending on the container
                                                                    // list does not have random to acces to an element
    ++it1;                                                          // pointer aritmetic is limited to ++ and -- overloads
    ++it1;                                                          // additional helper std::next() & std::distance()
    std::cout<<"Moving back 2 elements by pointer arithmetic: "<<*it1<<'\n';                                                             
    
    // moving all elements in list2 to list1 infront of a given position
    // before the position in list is determined by std::find; in front of element with value 300
    // then pass info of the other list to be inserted and the range this also works for one element too
    // since list does iterator manipulation only splice is a very efficient operation
    list1.splice(std::find(list1.begin(), list1.end(), 300), list2, list2.begin(), list2.end());
    display<int>(list1);
    display<int>(list2);
    
    list1.sort();               // sort list1 with less than operator <
    display<int>(list1);
    
    list1.unique();             // removed duplicates of consecutive elements
    display<int>(list1);
}

void STL_Forward_List()
{
    std::cout<<"-------------------STL Forward List-------------------------\n";
    /*• A forward list does not provide random access and uses a forward iterator
//      For example, to access the fifth element, you must navigate the first four elements.
//      using a forward list to access an arbitrary element is slow.
        No back() or push_back(). Only front() is possible
//    • Inserting and removing elements is fast at each position, if you are there. You can always insert
//      and delete an element in constant time, because no other elements have to be moved. Internally,
//      only some pointer values are manipulated.
//    • Inserting and deleting elements does not invalidate iterators, references, and pointers to other
//      elements.
//    • A forward list supports exception handling in such a way that almost every operation succeeds
//      or is a no-op. Thus, you can’t get into an intermediate state in which only half of the operation is
//      complete.
//    • Forward lists provide many special member functions for moving and removing elements. These
//      member functions are faster versions of general algorithms, 
//      because they only redirect pointers rather than copy and move the values. 
//      However, when element positions are involved, you have to pass the preceding position, 
//      and the member function has the suffix _after in its name.
     */
     
     std::forward_list<int>fwl1{1,3,5,6,9};
     std::forward_list<int>fwl2;
     
     // front() does not check if the list is empty
     // if the list is empty using front() is undefined behaviour
     // assert(fwl2.front()); // gives run-time error
     assert(fwl1.front());               
     std::cout<<"first element, front(): "<<fwl1.front()<<'\n';
     
     std::copy(fwl1.begin(), fwl1.end(),
            std::ostream_iterator<int>(std::cout, " "));
     std::cout<<'\n';
    
    for(const auto& i: fwl1)
        std::cout<<i<<" ";
    std::cout<<'\n';
     
     display<int>(fwl1);
     // to get the size info you need the number elements front first one to the last
     std::cout<<"forward_list fwl1 size: "<<std::distance(fwl1.begin(), fwl1.end())<<'\n'; 
     
     fwl2.insert_after(fwl2.before_begin(), {77,88,99,100});
     display<int>(fwl2);
     display<int, std::forward_list<int>>(fwl2);
     
     fwl2.push_front(105);
     display<int>(fwl2);
     fwl2.pop_front();      // does not return the element just removes
     display<int>(fwl2);
     
     fwl2.remove(88);       // removes the given value
     fwl2.remove_if([](int x) {return x%3==0;});
     display<int>(fwl2);
     
     fwl2.resize(6, 55);    // resizes to first value and if the list needs to grow 
                            // new elements are added with the given second value
    display<int>(fwl2);
    
    std::forward_list<int>fwl3{1,3,55, 25, 45, 4,5,7,9,8};
    display<int>(fwl3);
    auto it_pos_before=fwl3.before_begin();
   // ++it_pos_before;
   //std::cout<<"dereference of it_pos_before: "<<*it_pos_before<<'\n';
   // std::cout<<"it_pos_before: "<<it_pos_before<<", &it_pos_before:"<<&it_pos_before<<'\n';
             
    // if we need to insert before an element
    // we need to use before_begin and iterate it until our predicate criteria is satisfied
    // when the lambda returns true the value of it_pos_before will refer to the element before
    // since we capture by reference we can use the new value to insert before
    
    std::find_if(fwl3.begin(), fwl3.end(), 
              [&it_pos_before](int value){ 
                  if(value%2!=0) ++it_pos_before;
                  return value%2==0;});
    fwl3.insert_after(it_pos_before, 5555);
    display<int>(fwl3);
    
    // we can turn this into a template function so we dont have to write the whole
    // we can just pass our list and lambda function into the find_before() function
    // using custom find_before_if() function to insert before
    auto pos_before=find_before_if(fwl3.before_begin(), fwl3.end(),
                                    [](int value){ return value%2==0;});
    fwl3.insert_after(pos_before, 88888);
    display<int>(fwl3);
    display2(fwl3);
    display2(fwl2);
     
     // to move elements from fwl2 into fwl3 
     // fwl3.begin()= destination pos
     // fwl2 = source list
     // fwl2.before_begin= source position range start
     // fwl2.end()= source position range end
//    fwl3.splice_after(fwl3.begin(), fwl2, fwl2.before_begin(), fwl2.end());
//    display2(fwl3);
//    display2(fwl2);
    
      
      // to move elements from fwl3 to fwl2
      fwl3.splice_after(++fwl2.begin(), fwl2, fwl3.before_begin(), fwl3.end());
     display2(fwl3);
     display2(fwl2);
    
    // error in visual studio; from Microsoft Developer; just experimenting 
    // if it works in Clang, in Microsoft lambda has to be mmodified as (auto*i)
    // otherwise it crashes according to MS Developer Blog
    const auto d = [](auto i) { delete i; };
    const auto s = std::shared_ptr<int*>(new int*(new int(42)), d);
    std::cout<<**s<<'\n';
}
int main()
{
//   STL_Array();
//   STL_Vector();
//   STL_Deque();
//   STL_List();
     STL_Forward_List();

    return 0;
}
