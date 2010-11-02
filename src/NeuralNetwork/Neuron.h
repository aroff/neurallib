#pragma once
#include <vector>
#include <memory>

enum LayerType
{
	ENTRADA,
	OCULTA,
	SAIDA
};


class Neuron
{
public:

	~Neuron();

	void setLearningRate(double learningRate) { m_LearningRate = learningRate; }
	double getLearningRate() const { return m_LearningRate; }

	void setWeight(WORD idx, double value) { m_Weights[idx] = value; }
	double getWeight(WORD idx) const { return m_Weights[idx]; }

protected:
	friend class NeuralNetwork;
	friend class Layer;

	Neuron(WORD n_inputs) {
		deletado.resize(n_inputs, false);
	}


	double FeedForward(const std::vector<double> &values) const;
	virtual double Activation(double value) const = 0;

	std::vector<double> m_Weights;
	std::vector<bool> deletado;
	std::vector<double> m_Inputs;

	double m_LearningRate;
};

class InputNeuron : public Neuron {
public:
	InputNeuron(WORD n_inputs);
protected:
	virtual double Activation(double value) const;
};

class ProcessingNeuron : public Neuron {
public:
	ProcessingNeuron(WORD n_inputs);
protected:
	virtual double Activation(double value) const;
};

class NeuronFactory {
public:
	static std::unique_ptr  <Neuron> Create(WORD n_inputs, LayerType layerType);
};