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
	p[0] = DataPattern({ 0, 1 }, { 0 });

	// 1, 0 -> 0
	p[1] = DataPattern({ 1, 0 }, { 0 });

	// 1, 1 -> 1
	p[2] = DataPattern({ 1, 1 }, { 1 });

	// 0, 0 -> 1
	p[3] = DataPattern({ 0, 0 }, { 1 });

	r.Estimate(p); // Estimate neural network parameters

	return r;
}