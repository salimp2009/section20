#include <iostream>
#include <x86intrin.h>
#include <xmmintrin.h>

void TestAddSSE() {
    // arrays has to be aligned as 16-byte if XMMi registers are used
    //if AVX 256-bit YMMi registers are used alignas 32-byte (256-bits)
    // if 512-bit ZMMi registers are used alginas 64-byte (512-bits)
    
    // All dynamically allocated instances of a struct or class needs to be aligned manually
    // Arrays has to be aligned manually also
    
    // __m128 stores 4 floats at a time (x,y,z,w)
    // __m256 stores 8 floats at a time
    // __m512 stores 16 floats at a time
    
    alignas(16) float A[4];
    alignas(16) float A2[4];
    alignas(16) float B[8]={2.0f, 4.0f, 6.0f, 8.0f,
                            10.0f, 12.0f, 14.0f, 16.0f};
    
      // setting SIMD variable values with direct assignment
    __m128 a = _mm_set_ps(4.0f, 3.0f, 2.0f, 1.0f);      // the intrinsic _m_set_ps will read values backwards 1,2,3,4
    __m128 b = _mm_load_ps(&B[0]);                      // assigning values from an array; SSE read 4 values at a time; reads normal (no backwards)
    __m128 bY = _mm_load_ps(&B[4]);                     // read the next 4 values starting from the 4th element of the array
    
    // add vectors;
    __m128 result = _mm_add_ps(a,b);
    
    // multiply vectors;
    __m128 result2 = _mm_mul_ps(b, bY);
    
    //store result into empty array;
    _mm_store_ps(&A[0], result);
    _mm_store_ps(&A2[0], result2);
    
    // print add result
    std::cout<<"\nResult: [";
    for(const auto elem:A)
        std::cout<<elem<<" ";
    std::cout<<"]\n";
    
     // print multiply result
    std::cout<<"\nResult2: [";
    for(const auto elem2:A2)
        std::cout<<elem2<<" ";
    std::cout<<"]\n";
        
}

void DotArrays_SSE()
{
        alignas(16) float A[4];
        alignas(16) float B[4];
        
        alignas(16) float b[16]={0.0f, 1.0f, 2.0f, 3.0f,
                                4.0f, 5.0f, 6.0f, 7.0f,
                                8.0f, 9.0f, 10.0f, 11.0f,
                                12.0f, 13.0f, 14.0f, 15.0f };
        alignas(16) float a[16]={0.0f, 1.0f, 2.0f, 3.0f,
                                4.0f, 5.0f, 6.0f, 7.0f,
                                8.0f, 9.0f, 10.0f, 11.0f,
                                12.0f, 13.0f, 14.0f, 15.0f };
          
        int i{0};
                            
        __m128 vaX = _mm_load_ps(&a[(i+0)*4]); // a[0,4,8,12]    // _mm_load_ps loads 4 values at a time there the next
        __m128 vaY = _mm_load_ps(&a[(i+1)*4]); // a[1,5,9,13]    // when reading in a loop, on the next iteration of loop 
        __m128 vaZ= _mm_load_ps(&a[(i+2)*4]);  // a[2,6,10,14]   // reading has to start at the 4th, 8th or 12th element of array
        __m128 vaW= _mm_load_ps(&a[(i+3)*4]);  // a[3,7,11,15]   // to automate this in a loop we use (i+n)*4 so that on the
                                                                 // next iteration, it will start to read on multiplies of 4
                                                                

        __m128 vbX = _mm_load_ps(&b[(i+0)*4]); // b[0,4,8,12]
        __m128 vbY = _mm_load_ps(&b[(i+1)*4]); // b[1,5,9,13]
        __m128 vbZ= _mm_load_ps(&b[(i+2)*4]);  // b[2,6,10,14]
        __m128 vbW= _mm_load_ps(&b[(i+3)*4]);  // b[3,7,11,15] 
        
        _mm_store_ps(&A[i], vaY);
        _mm_store_ps(&B[i], vbZ);
        
        // print 
        std::cout<<"\nA[i]: [";
        for(const auto elem:A)
            std::cout<<elem<<" ";
        std::cout<<"]\n";
        
        // print 
        std::cout<<"\nB[i]: [";
        for(const auto elem:B)
            std::cout<<elem<<" ";
        std::cout<<"]\n";
       
}

int main()
{
    TestAddSSE(); 
    DotArrays_SSE();
    
 
 
 return 0;
}