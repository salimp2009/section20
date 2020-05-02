#include <iostream>
//#include <x86intrin.h>  // for clang
#include <xmmintrin.h> 
#include <algorithm>


void DotArrays_sse_transpose(int count, float r[], const float a[], const float b[])
{
    for(int i{0}; i<count; i+=4) 
    {
        // load the vector as they are in row major
        __m128 vaX = _mm_load_ps(&a[(i+0)*4]);  // a[0,1,2,3]
        __m128 vaY = _mm_load_ps(&a[(i+1)*4]);  // a[4,5,6,7]
        __m128 vaZ = _mm_load_ps(&a[(i+2)*4]);  // a[8,9,10,11]
        __m128 vaW = _mm_load_ps(&a[(i+3)*4]);  // a[12,13,14,15]
        
        __m128 vbX = _mm_load_ps(&b[(i+0)*4]);  // b[0,1,2,3]
        __m128 vbY = _mm_load_ps(&b[(i+1)*4]);  // b[4,5,6,7]
        __m128 vbZ = _mm_load_ps(&b[(i+2)*4]);  // b[8,9,10,11]
        __m128 vbW = _mm_load_ps(&b[(i+3)*4]);  // b[12,13,14,15]
        
        // transpose raw major to colum wise; each column is a vector and each row is one of the x,y,z,w coordinates (w dummy or identity 1)
        _MM_TRANSPOSE4_PS(vaX, vaY, vaZ,vaW );  // vaX=a[0,4,8,12]
                                               // vaY=a[1,5,9,12]
                                               // vaZ=a[2,6,10,13]
                                               // vaW=a[3,7,11,15]
                                               
       _MM_TRANSPOSE4_PS(vbX, vbY, vbZ,vbW );  // vbX=a[0,4,8,12]
                                               // vbY=a[1,5,9,12]
                                               // vbZ=a[2,6,10,13]
                                               // vbW=a[3,7,11,15]
      // declare a local variable
      __m128 result;
      
      // multiply & add each component of both matrix together and add to result and 
      // continue until every component is multiplied and added to the result
      result = _mm_mul_ps(vaX, vbX);
      result = _mm_add_ps(result, _mm_mul_ps(vaY, vbY));
      result = _mm_add_ps(result, _mm_mul_ps(vaZ, vbZ));
      result = _mm_add_ps(result, _mm_mul_ps(vaW, vbW)); 

    // load the calculated result vector into array r 
    // so the caller can retrieve the dot product result
    _mm_store_ps(&r[i], result);

    }
 
}

int main()
{
    // create two matrixes in two seperate array and initialize as row major
    
    alignas(16) float a[16]= {
                                0,1,2,3,
                                4, 5,6,7,
                                8,9,10,11,
                                12,13,14,15};
    alignas(16) float b[16]= {
                                0,1,2,3,
                                4, 5,6,7,
                                8,9,10,11,
                                12,13,14,15};
    
    alignas(16) constexpr float count{4}; 
    alignas(16) float r[4];
    alignas(16) float r2[4];
     
    DotArrays_sse_transpose(count, r, a, b);
    
   std::cout<<"\nr: [";
    for(const auto& elem:r)
        std::cout<<elem<<" ";
    std::cout<<"]\n";
    
    std::cout<<std::size(r);
    
    //std::memcpy(r2, r, sizeof r);
    
    std::copy(r, r+std::size(r), r2);
    
    std::cout<<"\nr2: [";
    for(const auto& elem:r2)
        printf(" %0.0f", elem);
       // std::cout<<elem<<" ";
    std::cout<<"]\n";

    return 0;
}