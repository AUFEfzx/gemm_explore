## 目标
设计一个无第三方依赖的裸矩阵乘法sdk，并针对多平台逐步对其进行性能优化。

## 核心实现
### 1、基础数据结构设计
矩阵设计
需要支持 int32_t, float32_t, float64_t等类型

Base设计： 
class Matrix<type>{
public:
    friend funcA()
    <!-- registeOpPlugin()
    execOp(std::string); -->


private:
    shape_info
    data_array
}

Derived设计：
    using Matrix<int32_t> MatrixI
    using Matrix<float32_t> MatrixF
    using Matrix<float64_t等类型> MatrixD

MatrixXf

算子设计
MatrixXf GEMMultiplication()
<!-- op设计 -->

### 2、接口设计
矩阵初始化
矩阵赋值初始化
矩阵随机初始化

矩阵乘法函数

### 3、测试设计
在test中尝试集成多种第三方库进行验证性能及精度，比如OpenBLAS、CBLAS、MKL（Math Kernel Library）、Eigen四个库进行比较。

结果
精度分析
性能分析


