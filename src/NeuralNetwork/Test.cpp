#include "stdafx.h"
#include "Test.h"

#include "neuralnetwork.h"


Test::Test()
{
}


Test::~Test()
{
}

NeuralNetwork Test::Test1() {
	int n_inputs = 2, n_hidden = 3, n_outputs = 1;

	NeuralNetwork r = NeuralNetwork::Create(n_inputs, n_hidden, n_outputs);

	// Create XOR problem data pattern
	std::vector<DataPattern> p;
	p.resize(4);

	// 0, 1 -> 0
	p[0] = DataPattern(n_inputs, n_outputs);
	p[0].m_Input = { 0, 1 };
	p[0].m_Output = { 0 };

	// 1, 0 -> 0
	p[1] = DataPattern(n_inputs, n_outputs);
	p[1].m_Input = { 1, 0 };
	p[1].m_Output = { 0 };

	// 1, 1 -> 1
	p[2] = DataPattern(n_inputs, n_outputs);
	p[2].m_Input = { 1, 1 };
	p[2].m_Output = { 1 };

	// 0, 0 -> 1
	p[3] = DataPattern(n_inputs, n_outputs);
	p[3].m_Input = { 0, 0 };
	p[3].m_Output = { 1 };

	r.Estimate(p); // Estimate neural network parameters

	return r;
}