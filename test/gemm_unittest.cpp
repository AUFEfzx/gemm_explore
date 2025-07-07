#include <chrono>
#include <thread>
#include "gemm.h"
#include "cblas.h"

extern void dgemm_(char*, char*, int*, int*,int*, double*, double*, int*, double*, int*, double*, double*, int*);

void test_openblas_dgemm()
{

    int m = 3;
    int n = 3;
    int k = 3;
    int sizeofa = m * k;
    int sizeofb = k * n;
    int sizeofc = m * n;
    char ta = 'N';
    char tb = 'N';
    double alpha = 1.2;
    double beta = 0.001;

    struct timeval start, finish;
    double duration;

    double *A = (double *)malloc(sizeof(double) * sizeofa);
    double *B = (double *)malloc(sizeof(double) * sizeofb);
    double *C = (double *)malloc(sizeof(double) * sizeofc);

    srand((unsigned)time(NULL));
    int i;
    for (i = 0; i < sizeofa; i++)
        A[i] = i % 3 + 1; //(rand()%100)/10.0;

    for (i = 0; i < sizeofb; i++)
        B[i] = i % 3 + 1; //(rand()%100)/10.0;

    for (i = 0; i < sizeofc; i++)
        C[i] = i % 3 + 1; //(rand()%100)/10.0;

    dgemm_(&ta, &tb, &m, &n, &k, &alpha, A, &m, B, &k, &beta, C, &m);

    for(i=0;i<sizeofc;i++){
        printf("%llf  ",C[i]);
    }
    free(A);
    free(B);
    free(C);
}

class TimePoint
{
public:
    TimePoint() : begin_time_point_(std::chrono::high_resolution_clock::now()) {}

    TimePoint(const TimePoint &) = delete;
    TimePoint(TimePoint &&) = delete;
    TimePoint &operator=(const TimePoint &) = delete;
    TimePoint &operator=(TimePoint &&) = delete;

    void Reset() { begin_time_point_ = std::chrono::high_resolution_clock::now(); }

    // milliseconds
    int64_t Elapsed()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() -
                                                                     begin_time_point_)
            .count();
    }

    // microseconds
    int64_t ElapsedMicroseconds()
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() -
                                                                     begin_time_point_)
            .count();
    }

    // nanoseconds
    int64_t ElapsedNanoseconds()
    {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() -
                                                                    begin_time_point_)
            .count();
    }

    // next is static method
    static void Sleep(uint32_t msec)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(msec));
    }

    static uint64_t GetTimeStamp()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::system_clock::now().time_since_epoch())
            .count();
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> begin_time_point_;
};

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

// Test2
void Test100x100MatrixMulti() {
    const int N = 1000;
    const int TOTAL = N * N;
    
    float* data_a = new float[TOTAL];
    std::fill_n(data_a, TOTAL, 2.0f);
    Matrixf input_a(std::make_pair(N, N));
    input_a.SetData(data_a, TOTAL);
    
    float* data_b = new float[TOTAL];
    std::fill_n(data_b, TOTAL, 3.0f);
    Matrixf input_b(std::make_pair(N, N));
    input_b.SetData(data_b, TOTAL);
    
    Matrixf output_rst(std::make_pair(N, N));
    Multiplication(input_a, input_b, output_rst);
   
    // PrintMatrix(output_rst);
}

int main(){
    TimePoint t;
    Test100x100MatrixMulti();
    int64_t gemm_100x100_run_cost{t.Elapsed()};
    printf("gemm_100x100_run_cost is %d ms\n", gemm_100x100_run_cost);
    //mac air m1 core: gemm_100x100_run_cost is 3977 ms

    test_openblas_dgemm();

    return 0;
}