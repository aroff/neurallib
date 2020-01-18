#pragma once

#include "Neuron.h"

class Layer	
{
public:
	Layer(size_t n_neurons, size_t n_inputs, LayerType layerType);
	~Layer();
	void setLearningRate(double lr);
	size_t size() const { return m_OutputValues.size(); }

	const std::vector<double> &FeedForward(const std::vector<double> &values);

protected:
	std::vector<std::unique_ptr<Neuron>> m_Neurons;
	friend class NeuralNetwork;
	LayerType m_LayerType;
	std::vector<double> m_OutputValues; // output values
};
