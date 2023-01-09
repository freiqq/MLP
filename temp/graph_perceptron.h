#ifndef S21_MLP_CONTROLLER_GRAPH_PERCEPTRON_
#define S21_MLP_CONTROLLER_GRAPH_PERCEPTRON_

#include <random>
#include <utility>

#include "../Logs/TraceLogger.h"
#include "common.h"

namespace s21 {
class GraphNeuron {
private:
  double value_ = 0;
  double error_ = 0;
  double weight_delta_ = 0;

public:
  std::vector<GraphNeuron *> prev_links_;
  std::vector<double> weights_;

  GraphNeuron() {
    value_ = 0;
    error_ = 0;
    weight_delta_ = 0;
  };

  void set_value(double value) { value_ = value; }
  void set_error(double error) { error_ = error; }
  void set_weight_delta(double weight_delta) { weight_delta_ = weight_delta; }
  void set_prev_links(std::vector<GraphNeuron *> prev_links) {
    prev_links_ = std::move(prev_links);
  }
  double get_value() const { return value_; }
  double get_error() const { return error_; }
  double get_weight_delta() const { return weight_delta_; }
  std::vector<GraphNeuron *> get_prev_neurons() const { return prev_links_; }

  void InitWeights(int count_of_neurons);
  void CorrectingWeight(double weight_delta, double learning_rate);
  // temp
  void info() {
    printf("value: %f\terror: %f\t"
           "delta: %f\tweight: %f\n",
           value_, error_, weight_delta_, weights_[0]);
  }

private:
};

class GraphLayer {
  friend class GraphNeuron;

public:
  GraphLayer() = default;

  std::vector<GraphNeuron> get_neurons() { return neurons_; }

  void InitInputLayer(std::vector<int> neurons);
  void InitLayer(int count_of_neurons_on_prev_layer,
                 int count_neurons_on_current_layer);
  void GetNeuronsValue(GraphLayer layer);
  void Backpropagation();

  // temp
  void info() {
    printf("letter: %d\n", num_of_letter_);
    for (auto &i : neurons_) {
      i.info();
    }
  }

private:
  std::vector<GraphNeuron> neurons_;
  int num_of_letter_ = 0;
};
class GraphPerceptron {
  friend class GraphLayer;

public:
  GraphPerceptron() = default;

  void LearnPerceptron();

private:
  GraphLayer in_layer_;
  std::vector<GraphLayer> h_layers_;
  GraphLayer out_layer_;

  size_t count_of_layers_ = 2;
  int count_of_neurons_on_input_layer_ = 784;
  int count_of_neurons_on_hidden_layer_ = 26;
  int count_of_neurons_on_output_layer_ = 26;

  void InitLayers();
};
} // namespace s21

#endif // S21_MLP_CONTROLLER_GRAPH_PERCEPTRON_
