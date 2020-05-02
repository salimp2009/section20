#include <iostream>
#include <xmmintrin.h>
#include <thread>

union Mat44
{
    float c[4][4];    // components
    __m128 row[4];    // each __mm128 hold 4 values and this one is an array wih size;                       
                      // it will hold 4 vectors with 4 values for x,y,z,w
};

__m128  MulVecMatSse(const __m128& v, const Mat44& M)
{
    // first transpose v
    __m128 vX= _mm_shuffle_ps(v, v, 0x00);  // (vx, vx, vx, vx);   // each x component of 4 matrix will be stored vX using shuffle
    __m128 vY= _mm_shuffle_ps(v, v, 0x55);  // (vy, vy, vy, vy); 
    __m128 vZ= _mm_shuffle_ps(v, v, 0xAA);  // (vz, vz, vz, vz);
    __m128 vW= _mm_shuffle_ps(v, v, 0xFF);  // (vz, vz, vz, vz);

    __m128 r =         _mm_mul_ps(vX, M.row[0]);
     r = _mm_add_ps(r, _mm_mul_ps(vY, M.row[1]));
     r = _mm_add_ps(r, _mm_mul_ps(vZ, M.row[2]));
     r = _mm_add_ps(r, _mm_mul_ps(vW, M.row[3]));
     return r;
}

void MulMatMatSse(Mat44& R, const Mat44& A, const Mat44 & B)
{
    R.row[0]=MulVecMatSse(A.row[0], B);
    R.row[1]=MulVecMatSse(A.row[1], B);
    R.row[2]=MulVecMatSse(A.row[2], B);
    R.row[3]=MulVecMatSse(A.row[3], B);
}

int main()
{
    Mat44 r;
    Mat44 a;
    Mat44 b;
    
    a.row[0]={0,1,2,3};
    a.row[1]={4,5,6,7};
    a.row[2]={8,9,10,11};
    a.row[3]={12,13,14,15};
    
    b.row[0]={0,1,2,3};
    b.row[1]={4,5,6,7};
    b.row[2]={8,9,10,11};
    b.row[3]={12,13,14,15};
    
    MulMatMatSse(r, a, b);
    
  // printf("r[0]= %0.0f\n r[1]= %0.0f\n r[2]= %0.0f\n r[3]= %0.0f\n", r.row[0], r.row[1], r.row[2], r.row[3]);
    
    for (int i{ 0 }; i < 4; ++i) {
		std::cout << "row: [";
		for (int j{ 0 }; j < 4; ++j) {
			std::cout << r.c[i][j] << " ";
		}
		std::cout << "]\n";
    }
    
    
    // results;
//    row: [56 62 68 74 ]      // the elements first row 1st matrix(a) multiplied by the element of the first coloumn of 2nd matrix(b); 
//    row: [152 174 196 218 ]  
//    row: [248 286 324 362 ]
//    row: [344 398 452 506 ]

    return 0;
}
