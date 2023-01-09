#include "graph_perceptron.h"

#include <ctime>
#include <random>

int main() {
  LOG_INIT
  LOG_TRACE
  clock_t startTime = clock();

  s21::GraphPerceptron perceptron;
  perceptron.LearnPerceptron();

  clock_t endTime = clock();

  long double elapsedTime =
      (endTime - startTime) / static_cast<long double>(CLOCKS_PER_SEC);
  std::cout << "Elapsed time: " << elapsedTime << " seconds" << std::endl;
  return 0;
}

namespace s21 {
void s21::GraphPerceptron::LearnPerceptron() {
  LOG_TRACE

  s21::Common train_data;
  InitLayers();

  for (auto &train_input_layer : train_data.Parser()) {
    in_layer_.InitInputLayer(train_input_layer);
    s21::GraphLayer supply_layer = in_layer_;
    for (auto &hidden_layer : h_layers_) {
      hidden_layer.GetNeuronsValue(supply_layer);
      supply_layer = hidden_layer;
    }
    out_layer_.GetNeuronsValue(supply_layer);
    //    out_layer_.info();
    out_layer_.Backpropagation();
    printf("------------------AFTER------------------\n");
    //    out_layer_.info();
  }
}

void s21::GraphPerceptron::InitLayers() {
  LOG_TRACE
  int count_neurons_on_prev_layer = count_of_neurons_on_input_layer_;
  for (int i = 0; i < count_of_layers_; ++i) {
    s21::GraphLayer hidden_layer;
    hidden_layer.InitLayer(count_neurons_on_prev_layer,
                           count_of_neurons_on_hidden_layer_);
    h_layers_.push_back(hidden_layer);
    count_neurons_on_prev_layer = count_of_neurons_on_hidden_layer_;
  }
  out_layer_.InitLayer(count_neurons_on_prev_layer,
                       count_of_neurons_on_output_layer_);
}

void s21::GraphLayer::InitLayer(int count_neurons_on_prev_layer,
                                int count_neurons_on_current_layer) {
  LOG_TRACE
  for (int i = 0; i < count_neurons_on_current_layer; ++i) {
    GraphNeuron neuron;
    neuron.InitWeights(count_neurons_on_prev_layer);
    neurons_.push_back(neuron);
  }
}

void s21::GraphLayer::InitInputLayer(std::vector<int> neurons) {
  LOG_TRACE
  num_of_letter_ = neurons[0] - 1;
  for (int i = 1; i < neurons.size(); ++i) {
    s21::GraphNeuron input_neuron;
    input_neuron.set_value(neurons[i]);
    neurons_.push_back(input_neuron);
  }
}

void s21::GraphLayer::GetNeuronsValue(GraphLayer layer) {
  LOG_TRACE
  num_of_letter_ = layer.num_of_letter_;
  for (auto &neuron : neurons_) {
    neuron.prev_links_.clear();
    double sum = 0;
    for (int j = 0; j < layer.neurons_.size(); ++j) {
      sum += neuron.weights_[j] * layer.neurons_[j].get_value();
      neuron.prev_links_.push_back(&layer.neurons_[j]);
    }
    neuron.set_value(pow((1 + exp(-sum)), -1));
  }
  neurons_[num_of_letter_].set_error(1);
}

void s21::GraphLayer::Backpropagation() {
  LOG_TRACE
  int err;
  double learning_rate = 0.1;
  for (int i = 0; i < neurons_.size(); ++i) {
    err = num_of_letter_ == i ? 1 : 0;
    neurons_[i].set_error(neurons_[i].get_value() - err);
    neurons_[i].set_weight_delta((1 - neurons_[i].get_value()) *
                                 neurons_[i].get_value() *
                                 neurons_[i].get_error());
    for (int j = 0; j < neurons_[i].get_prev_neurons().size(); ++j) {
      neurons_[i].weights_[j] = neurons_[i].weights_[j] -
                                neurons_[i].get_prev_neurons()[j]->get_value() *
                                    neurons_[i].get_weight_delta() *
                                    learning_rate;
      neurons_[i].prev_links_[j]->CorrectingWeight(
          neurons_[i].get_weight_delta(), learning_rate);
    }
  }
}

void s21::GraphNeuron::CorrectingWeight(double weight_delta,
                                        double learning_rate) {
  LOG_TRACE
//    std::cout << value_ << "\n";
//    value_ += 0.1;
  /// ?????????????????
//  info();
  weight_delta_ = weight_delta;
//  for (auto &weight : weights_) {
//    error_ = weight * weight_delta;
//    weight = weight - value_ * weight_delta * learning_rate;
//  }
  //    for (auto neuron : prev_links_) {
  //    neuron->CorrectingWeight(weight_delta, learning_rate);
  //  }
}

void s21::GraphNeuron::InitWeights(int count_of_neurons) {
  LOG_TRACE
  std::mt19937 gen(std::random_device{}());
  std::uniform_real_distribution<double> dist(-1, 1);
  for (int i = 0; i < count_of_neurons; ++i) {
    weights_.push_back(dist(gen));
  }
}
}; // namespace s21
