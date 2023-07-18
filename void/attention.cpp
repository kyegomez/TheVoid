#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <chrono>


// Define a function to perform the dot product of two vectors
double dot_product(const std::vector<double>& v1, const std::vector<double>& v2) {
    double result = 0.0;
    for (int i = 0; i < v1.size(); i++) {
        result += v1[i] * v2[i]; // Multiply corresponding elements and add to the result
    }
    return result;
}

// Define a function to perform the softmax operation on a vector
std::vector<double> softmax(const std::vector<double>& v) {
    std::vector<double> softmax_vals(v.size());
    double max_val = *max_element(v.begin(), v.end()); // Find the maximum value in the vector
    double sum = 0.0;

    // Compute the softmax values
    for (int i = 0; i < v.size(); i++) {
        softmax_vals[i] = exp(v[i] - max_val); // Subtract the maximum value for numerical stability
        sum += softmax_vals[i];
    }

    // Normalize the softmax values so they add up to 1
    for (int i = 0; i < softmax_vals.size(); i++) {
        softmax_vals[i] /= sum;
    }

    return softmax_vals;
}

// Define the attention mechanism
std::vector<double> attention(const std::vector<double>& query, const std::vector<std::vector<double>>& keys, const std::vector<std::vector<double>>& values) {
    std::vector<double> attention_scores(keys.size());

    // Compute the attention scores by taking the dot product of the query and each key
    for (int i = 0; i < keys.size(); i++) {
        attention_scores[i] = dot_product(query, keys[i]);
    }

    // Apply the softmax function to the attention scores
    std::vector<double> attention_probs = softmax(attention_scores);

    std::vector<double> output(values[0].size(), 0.0);

    // Compute the output by taking the weighted sum of the values
    for (int i = 0; i < values.size(); i++) {
        for (int j = 0; j < values[i].size(); j++) {
            output[j] += attention_probs[i] * values[i][j];
        }
    }

    return output;
}


int main() {
  // Define a query, keys, and values
  std::vector<double> query = {1.0, 2.0, 3.0};
  std::vector<std::vector<double>> keys = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.5, 4.0}};
  std::vector<std::vector<double>> values = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};

  // Start the clock
  auto start = std::chrono::high_resolution_clock::now();

  // Compute the attention output
  std::vector<double> output = attention(query, keys, values);

  // Stop the clock
  auto stop = std::chrono::high_resolution_clock::now();

  // Compute the duration in milliseconds
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

  // Print the output
  for (double val : output) {
      std::cout << val << " ";
  }
  std::cout << std::endl;

  // Print the duration
  std::cout << "Time taken by function: " << duration.count() << " milliseconds" << std::endl;

  return 0;
}