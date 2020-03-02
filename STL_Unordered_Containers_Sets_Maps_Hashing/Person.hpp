#ifndef MY_PERSON_H
#define MY_PERSON_H

class Person
{
public:
    
    Person():first_name{}, last_name{} {}
    Person(std::string name, std::string lastname):first_name{std::move(name)}, last_name{std::move(lastname)}{}
    
    // string is a heavy container everytime we use get it will make an expensive copy
    // instead we can return by cont& which is safer; 
    // (although if auto is used const specifiers are decayed !!!)
    const std::string& firstname() const& {return first_name;}
    const std::string& lastname() const& {return last_name;}
    
    bool operator==(const Person& p2) const {
        
        return (last_name==p2.last_name &&
                first_name==p2.first_name);
    }
    
    bool operator()(const Person& p2) const {
        return *this==p2;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Person& p1) {
        return os<<"["<<p1.first_name<<", "<<p1.last_name<<"] ";
    }

private:  
    std::string first_name;
    std::string last_name;  
};

#endif // MY_PERSON_H
