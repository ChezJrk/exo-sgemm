#include <cblas.h>
#include <gtest/gtest.h>
#include <sgemm.h>

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <random>
#include <vector>

static std::vector<float> gen_matrix(long m, long n) {
  static std::random_device rd;
  static std::mt19937 rng{rd()};
  std::uniform_real_distribution<> rv{-1.0f, 1.0f};

  std::vector<float> mat(m * n);
  std::generate(std::begin(mat), std::end(mat), [&]() { return rv(rng); });

  return mat;
}

static void sgemm_ref(const float *a, const float *b, float *c, int n) {
  cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,  // layout
      n, n, n,                                            // m, n, k
      1.0,                                                // alpha
      a, n,                                               // A (lda)
      b, n,                                               // B (ldb)
      1.0,                                                // beta
      c, n                                                // C (ldc)
  );
}

static bool all_close(
    const std::vector<float> &actual_v, const std::vector<float> &expected_v) {
  if (actual_v.size() != expected_v.size()) {
    return false;
  }
  int n = actual_v.size();
  for (int i = 0; i < n; i++) {
    float expected = expected_v[i];
    float actual = actual_v[i];
    double relerr = fabsf(actual - expected) / expected;
    if (relerr > 1e-3 * n) {
      return false;
    }
  }
  return true;
}

class SgemmTestFixture : public ::testing::TestWithParam<int> {};

TEST_P(SgemmTestFixture, ErrorIsSmall) {
  int n = GetParam();
  auto a = gen_matrix(n, n);
  auto b = gen_matrix(n, n);
  auto c_exo = gen_matrix(n, n);
  auto c_mkl = c_exo;
  sgemm_exo(nullptr, n, n, n, a.data(), b.data(), c_exo.data());
  sgemm_ref(a.data(), b.data(), c_mkl.data(), n);
  ASSERT_TRUE(all_close(c_exo, c_mkl));
}

INSTANTIATE_TEST_SUITE_P(SgemmTests, SgemmTestFixture,
    ::testing::Values(64, 192, 221, 256, 320, 397, 412, 448, 512, 576, 704, 732,
        832, 911, 960, 1024, 1088, 1216, 1344, 1472, 1600, 1728, 1856, 1984,
        2048));
