# Neural Library

This is a repo for building a multipurpose C++ 3-Layer Neural Network Library from scratch in C++. Original code was built in 1998 as part of author's Barchelor final project and was adapted to be compiled in modern compilers. 
This version was compiled in Visual Studio 2017.

## Simple Usage

Build a network with a C++ class and train it.

Exhibit below shows the solving of XOR problem with a Neural Network model.
The training procedure starts by calling Estimate method from the Neural Network class.

```C++
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
```

## Download or fork
```
$ git clone 
```

