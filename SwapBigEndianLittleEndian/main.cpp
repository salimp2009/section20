#include <iostream>
#include <ios>
#include <bitset>

// integer endian swapping
struct U32
{
  std::int32_t  m_a;
  std::int16_t  m_b;
  std::int32_t  m_c;  

};

std::int16_t swap_int16(std::int16_t value)
{
    return ((value & 0x00FF)<<8)
           |((value & 0xFF00)>>8);
}

std::int32_t swap_int32(std::int32_t value)
{
    return  ((value & 0x000000FF)<<24)
           |((value & 0x0000FF00)<<8)
           |((value & 0x00FF0000)>>8)
           |((value & 0xFF000000)>>24);           
}

// floating point endian swapping
union U32F32                            // create a union with integer and float values (32 bits)
{
    std::int32_t m_asU32;
    float        m_asF32;
};

float swapF32(float value)              // function to swap endian of floating value
{
    U32F32 u;
    u.m_asF32=value;                    // assign floating value to union elements of float type 
    
    u.m_asU32 = swap_int32(u.m_asU32);  // swap union element as an integer 
                                        // the returned value will be swapped as an integer
    return u.m_asF32;                   // return union elements value as float 
}                                       // (it is already swappe)


int main()
{
    U32 example;
    
    example.m_a=1;          // 32 bit integer
    example.m_b=44;         // 16 bit integer
    example.m_c=44;         // 32 bit integer
    
    std::cout<<std::showbase<<std::dec;
    std::cout<<std::hex<<example.m_a<<'\n';
    std::cout<<std::hex<<example.m_b<<'\n';
    std::cout<<std::hex<<example.m_c<<'\n';
    
    std::cout<<std::bitset<32>(example.m_a)<<'\n';
    std::cout<<std::bitset<16>(example.m_b)<<'\n';
    std::cout<<std::bitset<32>(example.m_c)<<'\n';
    
    
    example.m_a=swap_int32(example.m_a);
    example.m_b=swap_int16(example.m_b);
    example.m_c=swap_int32(example.m_c);
    
    std::cout<<std::hex<<example.m_a<<'\n';
    std::cout<<std::hex<<example.m_b<<'\n';
    std::cout<<std::hex<<example.m_c<<'\n';
    
    std::cout<<std::bitset<32>(example.m_a)<<'\n';
    std::cout<<std::bitset<16>(example.m_b)<<'\n';
    std::cout<<std::bitset<32>(example.m_c)<<'\n';
    
    std::cout<<std::bitset<32>(0x00FF)<<'\n';
    std::cout<<'\n';
    
    float fl=2.3435345345345;
    float fl1=fl/2;
    
    std::cout<<fl1<<'\n';
    fl=swapF32(fl);
    std::cout<<std::bitset<32>(fl)<<'\n';
 
 return 0;
}