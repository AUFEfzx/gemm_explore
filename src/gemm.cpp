#include "gemm.h"

Matrixf::Matrixf(const std::pair<int, int>& shape, MATRIX_INIT_TYPE type){
    data_.reset(new float[shape.first * shape.second], [](float *p)
                { if(nullptr!= p){delete[] p;} });

    for (int i{0}; i < (shape.first * shape.second); i++)
    {
        data_.get()[i] = 0;
    }

    shape_ = shape;
}

Matrixf::~Matrixf(){
    // if(nullptr != data_){
    //     delete[] data_;
    // }
}

void Matrixf::SetData(float* data, int len){
    if (len != shape_.first * shape_.second)
    {
        return;
    }

    for (int i{0}; i < len; i++)
    {
        data_.get()[i] = data[i];
    }
}

bool Multiplication(Matrixf m1, Matrixf m2, Matrixf dst){
    if (m1.shape_.second != m2.shape_.first)
    {
        printf("%s %d Multiplication input scale is invalid! m1 shape {%d %d}, m2 shape {%d %d} \n", __FILE__, __LINE__, m1.shape_.first, m1.shape_.second, m2.shape_.first, m2.shape_.second);
        return false;
    }

    if(dst.shape_.first != m1.shape_.first || dst.shape_.second != m2.shape_.second){
        printf("%s %d Multiplication output scale is invalid! m1 shape {%d %d}, m2 shape {%d %d} dst shape {%f %f} \n", __FILE__, __LINE__, m1.shape_.first, m1.shape_.second, m2.shape_.first, m2.shape_.second, dst.shape_.first, dst.shape_.second);
        return false;
    }
    
    for(int i{0}; i< (dst.shape_.first * dst.shape_.second); i++){
        dst.data_.get()[i] = 0;
    }

    for (int i{0}; i < m1.shape_.first; i++)
    {
        for (int j{0}; j < m2.shape_.second; j++)
        {
            for (int k{0}; k < m1.shape_.second; k++)
            {
                dst.data_.get()[i * dst.shape_.second + j] += m1.data_.get()[i * m1.shape_.second + k] * m2.data_.get()[k * m2.shape_.first + j];
            }
        }
    }
    return true;
}

void PrintMatrix(Matrixf m)
{
    printf("\n=========================== Matrix data is ============================\n");
    printf("[ ");
    for (int i{0}; i < m.shape_.first; i++)
    {
        for (int j{0}; j < m.shape_.second; j++)
        {
            printf("%f ", m.data_.get()[i * m.shape_.first + j]);
        }
        if (i != (m.shape_.first - 1))
        {
            printf("\n");
        }
    }
    printf(" ]\n");
}