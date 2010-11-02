#pragma once

#include "Neuron.h"

class Layer	
{
public:
	size_t size() const { return valores_de_saida.size(); }
	//WORD nEntradas_por_Neuronio;
	Layer(WORD nNeu, WORD nEntradasNeuronio, LayerType tipo_camada);
	~Layer();
	LayerType m_LayerType;
	void DefineLR(double lr);

	const std::vector<double> &FeedForward(const std::vector<double> &values);

	std::vector<std::unique_ptr<Neuron>> neuro;
	friend class NeuralNetwork;

//protected:
	std::vector<double> valores_de_saida; // Vetor de saídas
};
