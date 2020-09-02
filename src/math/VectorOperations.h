#pragma once

#include <vector>
#include <stdexcept>

namespace snspd::math {

  // Allow vectors to be added
  template <typename T>
  [[nodiscard]] std::vector<T> operator+(const std::vector<T> &lhs, const std::vector<T> &rhs) {

    // Check that the vectors have the same length
    if (lhs.size() != rhs.size()) {
      throw std::invalid_argument("Vectors need to have the same size to be added.");
    }

    std::vector<T> res(lhs.size());

    for (std::size_t i = 0; i < lhs.size(); ++i) {
      res.at(i) = lhs.at(i) + rhs.at(i);
    }

    return res;
  }

  // Allow vectors to be subtracted
  template <typename T>
  [[nodiscard]] std::vector<T> operator-(const std::vector<T> &lhs, const std::vector<T> &rhs) {

    // Check that the vectors have the same length
    if (lhs.size() != rhs.size()) {
      throw std::invalid_argument("Vectors need to have the same size to be subtracted.");
    }

    std::vector<T> res(lhs.size());

    for (std::size_t i = 0; i < lhs.size(); ++i) {
      res.at(i) = lhs.at(i) - rhs.at(i);
    }

    return res;
  }

  // Allow vectors to be multiplied with a scalar
  template <typename T>
  [[nodiscard]] std::vector<T> operator*(const std::vector<T> &vec, const T &scalar) {

    std::vector<T> res(vec.size());

    for (std::size_t i = 0; i < vec.size(); ++i) {
      res.at(i) = vec.at(i) * scalar;
    }

    return res;
  }

  // Allow vectors to be multiplied with a scalar
  template <typename T>
  [[nodiscard]] std::vector<T> operator*(const T &scalar, const std::vector<T> &vec) {
    return vec * scalar;
  }

  // Allow vectors to be multiplied component-wise
  template <typename T>
  [[nodiscard]] std::vector<T> operator*(const std::vector<T> &lhs, const std::vector<T> &rhs) {

    if (lhs.size() != rhs.size()) {
      throw std::invalid_argument("Vectors need to have the same length when doing component-wise multiplication.");
    }

    std::vector<T> res(lhs.size());

    for (std::size_t i = 0; i < lhs.size(); ++i) {
      res.at(i) = lhs.at(i) * rhs.at(i);
    }

    return res;
  }

  // Computes sine of a vector
  template <typename T>
  [[nodiscard]] std::vector<T> sin(const std::vector<T> &vec) {
    std::vector<T> res(vec.size());

    for (std::size_t i = 0; i < vec.size(); ++i) {
      res.at(i) = std::sin(vec.at(i));
    }

    return res;
  }

  // Computes the shifted difference of two vectors
  // The result is: (vec1[0], vec1[1] - vec2[0], vec1[2] - vec2[1], ..., -vec2[n])
  template <typename T>
  [[nodiscard]] std::vector<T> shifted_diff(const std::vector<T> &vec1, const std::vector<T> &vec2) {

    if (vec1.size() != vec2.size()) {
      throw std::invalid_argument("Vectors need to have the same length to be used in shifted difference.");
    }

    std::vector<T> res(vec1.size() + 1);

    // Get the first component
    res.at(0) = vec1.at(0);

    for (std::size_t i = 1; i < vec1.size() - 1; ++i) {
      res.at(i) = vec1.at(i) - vec2.at(i - 1);
    }

    res.at(vec1.size() - 1) = - vec2.at(vec1.size() - 1);

    return res;
  }
}
