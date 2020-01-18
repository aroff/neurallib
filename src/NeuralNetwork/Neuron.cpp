#include "stdafx.h"
#include "neuron.h"
#include <stdlib.h>
#include <math.h>
#include <memory.h>

#include <numeric>
#include <random>
#include <algorithm>
#include <functional>
#include <cassert>

Neuron::~Neuron()
{
}

InputNeuron::InputNeuron(WORD n_inputs) : 
	Neuron(n_inputs)
{
	assert(n_inputs > 0);
	m_Weights.resize(n_inputs);
	std::fill(m_Weights.begin(), m_Weights.end(), 0.0);
}

ProcessingNeuron::ProcessingNeuron(WORD n_inputs) :
	Neuron(n_inputs)
{
	assert(n_inputs > 0);
	m_Weights.resize(n_inputs);

	// First create an instance of an engine.
	std::random_device rd;

	// Specify the engine and distribution.
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dist{ -1.0, 1.0 };

	auto f = [&dist, &gen]() {
		return dist(gen);
	};

	std::generate(m_Weights.begin(), m_Weights.end(), f);
}

std::unique_ptr <Neuron> NeuronFactory::Create(WORD n_inputs, LayerType layerType)
{
	std::unique_ptr <Neuron> x;
	switch (layerType) {
	case LayerType::ENTRADA:
		x = std::make_unique<InputNeuron>(n_inputs);
		break;

	default:
		x = std::make_unique<ProcessingNeuron>(n_inputs);
		break;
	}

	return x;
}

double Neuron::FeedForward(const std::vector<double> &values) const
{
	assert(m_Weights.size() > 0);

	double sum = std::inner_product(values.begin(), values.end(), m_Weights.begin(), 0.0);
	return Activation(sum);
}

double ProcessingNeuron::Activation(double value) const {
	return 1.0 / (1.0 + exp(-value));
}

double InputNeuron::Activation(double value) const
{
	return value;
}
