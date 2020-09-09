#include <catch2/catch.hpp>
#include <iostream>
#include "../../src/math/TridiagonalMatrix.h"

TEST_CASE("Frobenius norm", "[tridiagonal_matrix]") {
  using mat = snspd::math::TridiagonalMatrix<double>;

  SECTION("Frobenius norm of an identity matrix") {
    std::size_t max_size{100};

    for (std::size_t i = 1; i < max_size; ++i) {
      auto eye = mat::eye(i);
      auto norm = eye.norm();
      REQUIRE(std::abs(norm - std::sqrt(static_cast<double>(i))) < 1e-7);
    }
  }

  SECTION("Frobenius norm of a diagonal matrix") {
    std::size_t max_size{100};

    std::vector<double> diagonal{};
    diagonal.reserve(max_size);

    double sign{-1};

    for (std::size_t i = 1; i < max_size; ++i) {

      diagonal.push_back(sign * static_cast<double>(i));
      sign *= -1.0;

      mat matrix(
          diagonal,
          std::vector<double>(diagonal.size() - 1),
          std::vector<double>(diagonal.size() - 1)
          );

      auto norm = matrix.norm();
      double expected = std::sqrt(static_cast<double>(i * (i + 1) * (2 * i + 1)) / 6);

      REQUIRE(std::abs(norm - expected) < 1e-7);
    }
  }

  SECTION("Frobenius norm of a non-diagonal matrix") {
    std::size_t max_size{100};

    std::vector<double> diagonal{};
    diagonal.reserve(max_size);

    double sign{-1};

    for (std::size_t i = 1; i < max_size; ++i) {

      diagonal.push_back(sign * static_cast<double>(i));
      sign *= -1.0;

      mat matrix(
          diagonal,
          std::vector<double>(diagonal.size() - 1, 1.0),
          std::vector<double>(diagonal.size() - 1, 1.0)
      );

      auto norm = matrix.norm();
      double expected = std::sqrt(static_cast<double>(i * (i + 1) * (2 * i + 1)) / 6
          + 2 * static_cast<double>(i - 1));

      REQUIRE(std::abs(norm - expected) < 1e-7);
    }
  }
}

TEST_CASE("Matrix multiplication", "[tridiagonal_matrix]") {
  using mat = snspd::math::TridiagonalMatrix<double>;
  using namespace snspd::math;

  SECTION("Multiplication with identity matrix gives the same vector") {

    std::size_t size{10};

    auto eye = mat::eye(size);

    std::vector<double> vec(size);

    for (std::size_t i = 0; i < size; ++i) {
      vec.at(i) = 1.0;

      REQUIRE(snspd::math::norm(eye * vec - vec) < 1e-7);
    }
  }

  SECTION("Multiplication with [1, 2; 3, 4] matrix") {
    mat matrix(2);
    matrix.set(mat::DIAG, 0, 1.0);
    matrix.set(mat::DIAG, 1, 4.0);
    matrix.set(mat::UPPER, 0, 2.0);
    matrix.set(mat::LOWER, 0, 3.0);

    auto res1 = matrix * std::vector<double>{1.0, 2.0};
    REQUIRE(norm(res1 - std::vector<double>{5.0, 11.0}) < 1e-7);

    auto res2 = matrix * std::vector<double>{-1.0, 3.0};
    REQUIRE(norm(res2 - std::vector<double>{5.0, 9.0}) < 1e-7);
  }
}
