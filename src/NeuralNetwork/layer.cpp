#include "stdafx.h"
#include "layer.h"
#include "neuron.h"

Layer::Layer(WORD n_neurons, WORD n_inputs, LayerType layerType)
{
	m_LayerType = layerType;

	valores_de_saida.resize(n_neurons);
	neuro.resize(n_neurons);
	for(auto &n : neuro) 
		n = NeuronFactory::Create(n_inputs, layerType);
}

Layer::~Layer()
{
}


const std::vector<double> &Layer::FeedForward(const std::vector<double> &values)
{
	for (unsigned int i = 0; i < valores_de_saida.size(); i++)
		valores_de_saida[i] = neuro[i]->FeedForward(values);
	
	return valores_de_saida;
}

void Layer::DefineLR(double lr)
{
	for (auto &n : neuro)
		n->setLearningRate(lr);
}
