#include <iostream>
#include <x86intrin.h>  // for clang
// #include <xmmintrin.h> // for windows; but it works in clang too !!
#include <cassert>

void DotArrays_SSE_Transpose(int count, float r[], const float a[], const float b[])
{
    assert(count%4==0);
    for(int i{0}; i<count; i+=4)
    {                                           // __m128 values;
        __m128 vaX = _mm_load_ps(&a[(i+0)*4]);  // a[0,1,2,3]
        __m128 vaY = _mm_load_ps(&a[(i+1)*4]);  // a[4,5,6,7]
        __m128 vaZ= _mm_load_ps(&a[(i+2)*4]);   // a[8,9,10,11]
        __m128 vaW= _mm_load_ps(&a[(i+3)*4]);   // a[12,13,14,15]

        __m128 vbX = _mm_load_ps(&b[(i+0)*4]);  // b[0,1,2,3]
        __m128 vbY = _mm_load_ps(&b[(i+1)*4]);  // b[4,5,6,7]
        __m128 vbZ= _mm_load_ps(&b[(i+2)*4]);   // b[8,9,10,11]
        __m128 vbW= _mm_load_ps(&b[(i+3)*4]);   // b[12,13,14,15]

        _MM_TRANSPOSE4_PS(vaX, vaY, vaZ, vaW);   // __m128 values after the transpose;
                                                // vaX:  a[0,4,8,12]
                                                // vaY:  a[1,5,9,13]
                                                // vaZ:  a[2,6,10,14]
                                                // vaW:  a[3,7,11,15]
        _MM_TRANSPOSE4_PS(vbX, vbY, vbZ, vbW);
                                                // vbX:  b[0,4,8,12]
                                                // vbY:  b[1,5,9,13]
                                                // vbZ:  b[2,6,10,14]
                                                // vbW:  b[3,7,11,15]
        
        __m128 result;
        
        result = _mm_mul_ps(vaX, vbX);          
        result = _mm_add_ps(result, _mm_mul_ps(vaY, vbY));
        result = _mm_add_ps(result, _mm_mul_ps(vaZ, vbZ));
        result = _mm_add_ps(result, _mm_mul_ps(vaW, vbW));
        
        _mm_store_ps(&r[i], result);
    }
}

void DotArrays_SSE(int count, float r[], const float a[], const float b[])
{
    assert(count%4==0);
    for(int i{0}; i<count; i+=4)
    {
        __m128 vaX = _mm_load_ps(&a[(i+0)*4]); // a[0,1,2,3]
        __m128 vaY = _mm_load_ps(&a[(i+1)*4]); // a[4,5,6,7]
        __m128 vaZ= _mm_load_ps(&a[(i+2)*4]);  // a[8,9,10,11]
        __m128 vaW= _mm_load_ps(&a[(i+3)*4]);  // a[12,13,14,15]

        __m128 vbX = _mm_load_ps(&b[(i+0)*4]); // b[0,1,2,3]
        __m128 vbY = _mm_load_ps(&b[(i+1)*4]); // b[4,5,6,7]
        __m128 vbZ= _mm_load_ps(&b[(i+2)*4]);  // b[8,9,10,11]
        __m128 vbW= _mm_load_ps(&b[(i+3)*4]);  // b[12,13,14,15]
        
        __m128 result;
        
        result = _mm_mul_ps(vaX, vbX);
        result = _mm_add_ps(result, _mm_mul_ps(vaY, vbY));
        result = _mm_add_ps(result, _mm_mul_ps(vaZ, vbZ));
        result = _mm_add_ps(result, _mm_mul_ps(vaW, vbW));
        
        _mm_store_ps(&r[i], result);
    }
}


int main()
{
    alignas(16) float a[16]={0.0f,1.0f,2.0f,3.0f,
                            4.0f,5.0f,6.0f,7.0f,
                            8.0f,9.0f,10.0f,11.0f,
                            12.0f,13.0f,14.0f,15.0f};
                            
    alignas(16) float b[16]={0.0f,1.0f,2.0f,3.0f,
                            4.0f,5.0f,6.0f,7.0f,
                            8.0f,9.0f,10.0f,11.0f,
                            12.0f,13.0f,14.0f,15.0f};
    int count{4};
    
    alignas(16) float r[4];
    alignas(16) float r2[4];
    DotArrays_SSE(count, &r[0], &a[0], &b[0]);

    std::cout<<"\nr: [";
    for(const auto elem:r)
        std::cout<<elem<<" ";
    std::cout<<"]\n";
    
     DotArrays_SSE_Transpose(count, &r2[0], &a[0], &b[0]);

    std::cout<<"\nr-Transposed: [";
    for(const auto elem:r2)
        std::cout<<elem<<" ";
    std::cout<<"]\n";
    
    std::cout<<'\n';

 return 0;
}