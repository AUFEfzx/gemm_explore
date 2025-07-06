#pragma once
#include <vector>
#include <utility>
#include "common.h"

enum MATRIX_INIT_TYPE{
    MATRIX_ZEOR = 0,
    MATRIX_RANDOM = 0
};

GEMM_API class Matrixf{
public:
    Matrixf(const std::pair<int, int>& shape, MATRIX_INIT_TYPE type = MATRIX_ZEOR);
    // Matrixf(const Matrixf &) = delete;
    // Matrixf &operator=(const Matrixf &) = delete;
    // Matrixf(Matrixf &&) = delete;
    // Matrixf &operator=(Matrixf &&) = delete;
    ~Matrixf();

    void SetData(float* data, int len);
    friend bool Multiplication(Matrixf m1, Matrixf m2, Matrixf dst);
    friend void PrintMatrix(Matrixf m);

private:
    std::shared_ptr<float> data_{nullptr};
    std::pair<int, int> shape_;
};

GEMM_API bool Multiplication(Matrixf m1, Matrixf m2, Matrixf dst);
GEMM_API void PrintMatrix(Matrixf m);