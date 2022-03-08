#include <benchmark/benchmark.h>
#include <cblas.h>
#include <sgemm.h>

#include <random>
#include <vector>

#ifndef CBLAS_NAME
#error Must set CBLAS_NAME
#endif

// ----------------------------------------------------------------------------
// Utilities

// Source: http://www.netlib.org/lapack/lawnspdf/lawn41.pdf (p.120)
static double num_flops(long m, long n, long k) {
  return static_cast<double>(2 * m * n * k);
}

static std::vector<float> gen_matrix(long m, long n) {
  static std::random_device rd;
  static std::mt19937 rng{rd()};
  std::uniform_real_distribution<> rv{-1.0f, 1.0f};

  std::vector<float> mat(m * n);
  std::generate(std::begin(mat), std::end(mat), [&]() { return rv(rng); });

  return mat;
}

template <typename SgemmFn>
static void BM_square_sgemm(benchmark::State &state) {
  long n = state.range(0);
  auto a = gen_matrix(n, n);
  auto b = gen_matrix(n, n);
  auto c = gen_matrix(n, n);

  for ([[maybe_unused]] auto _ : state) {
    SgemmFn{}(a.data(), b.data(), c.data(), n);
  }

  state.counters["flops"] = benchmark::Counter(
      static_cast<double>(state.iterations()) * num_flops(n, n, n),  //
      benchmark::Counter::kIsRate,                                   //
      benchmark::Counter::kIs1000                                    //
  );
}

// ----------------------------------------------------------------------------
// MKL SGEMM benchmark

struct cblas_square {
  void operator()(const float *a, const float *b, float *c, int n) {
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,  // layout
        n, n, n,                                            // m, n, k
        1.0,                                                // alpha
        a, n,                                               // A (lda)
        b, n,                                               // B (ldb)
        1.0,                                                // beta
        c, n                                                // C (ldc)
    );
  }
};

BENCHMARK_TEMPLATE(BM_square_sgemm, cblas_square)
    ->Name("sgemm_" CBLAS_NAME)
    ->Arg(64)
    ->Arg(192)
    ->Arg(221)
    ->Arg(256)
    ->Arg(320)
    ->Arg(397)
    ->Arg(412)
    ->Arg(448)
    ->Arg(512)
    ->Arg(576)
    ->Arg(704)
    ->Arg(732)
    ->Arg(832)
    ->Arg(911)
    ->Arg(960)
    ->Arg(1024)
    ->Arg(1088)
    ->Arg(1216)
    ->Arg(1344)
    ->Arg(1472)
    ->Arg(1600)
    ->Arg(1728)
    ->Arg(1856)
    ->Arg(1984)
    ->Arg(2048);

// ----------------------------------------------------------------------------
// Exo SGEMM benchmark

struct exo_square {
  void operator()(float *a, float *b, float *c, int n) {
    sgemm_exo(nullptr, n, n, n, a, b, c);
  }
};

BENCHMARK_TEMPLATE(BM_square_sgemm, exo_square)
    ->Name("sgemm_exo")
    ->Arg(64)
    ->Arg(192)
    ->Arg(221)
    ->Arg(256)
    ->Arg(320)
    ->Arg(397)
    ->Arg(412)
    ->Arg(448)
    ->Arg(512)
    ->Arg(576)
    ->Arg(704)
    ->Arg(732)
    ->Arg(832)
    ->Arg(911)
    ->Arg(960)
    ->Arg(1024)
    ->Arg(1088)
    ->Arg(1216)
    ->Arg(1344)
    ->Arg(1472)
    ->Arg(1600)
    ->Arg(1728)
    ->Arg(1856)
    ->Arg(1984)
    ->Arg(2048);
