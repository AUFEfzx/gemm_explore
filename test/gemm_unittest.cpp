#include "gemm.h"

//Test1: A simple 3*3 matrix multiplication
void Test3x3MatrixMulti(){
    float data_a[9] = {2,3,4,5,6,7,2,3,4};
    Matrixf input_a(std::make_pair(3,3));
    input_a.SetData(data_a, 9);
    // PrintMatrix(input_a);

    float data_b[9] = {2,1,1,1,2,1,1,1,2};
    Matrixf input_b(std::make_pair(3,3));
    input_b.SetData(data_b, 9);
    // PrintMatrix(input_b);

    Matrixf output_rst(std::make_pair(3,3));
    Multiplication(input_a,input_b,output_rst);
    PrintMatrix(output_rst);

    // expect matrix rst is 
    // [ 11.000000 12.000000 13.000000 
    // 23.000000 24.000000 25.000000 
    // 11.000000 12.000000 13.000000  ]
}


int main(){
    Test3x3MatrixMulti();
 
    return 0;
}