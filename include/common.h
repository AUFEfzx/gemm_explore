#pragma once

#ifdef _MSC_VER
#ifdef GEMM_EXPORTS
#define GEMM_API __declspec(dllexport)
#else
#define GEMM_API
#endif
#else /* _MSC_VER */
#ifdef GEMM_EXPORTS
#define GEMM_API __attribute__((visibility("default")))
#else
#define GEMM_API
#endif
#endif


