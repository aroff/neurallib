#include "stdafx.h"
#include "layer.h"
#include "neuron.h"

Layer::Layer(WORD n_neurons, WORD n_inputs, LayerType layerType)
{
	m_LayerType = layerType;

	m_OutputValues.resize(n_neurons);
	m_Neurons.resize(n_neurons);
	for(auto &n : m_Neurons) 
		n = NeuronFactory::Create(n_inputs, layerType);
}

Layer::~Layer()
{
}

const std::vector<double> &Layer::FeedForward(const std::vector<double> &values)
{
	for (unsigned int i = 0; i < m_OutputValues.size(); i++)
		m_OutputValues[i] = m_Neurons[i]->FeedForward(values);
	
	return m_OutputValues;
}

void Layer::setLearningRate(double lr)
{
	for (auto &n : m_Neurons)
		n->setLearningRate(lr);
}
