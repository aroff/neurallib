#pragma once
#include "datapattern.h"
#include "layer.h"
#include "neuron.h"

class NeuralNetwork
{
public:
	NeuralNetwork(Layer &inputLayer, Layer &hidden, Layer &output);
	~NeuralNetwork();

	static NeuralNetwork Create(WORD n_inputs, WORD n_hidden, WORD n_outputs);

	void setLearningRate(double lr);
	void Estimate(const std::vector<DataPattern> &pattern);

protected:
	void BackPropagation(const std::vector<double> &values);
	void UpdateWeights(void);
	double Learn(const std::vector<DataPattern> &pattern);
	WORD UpdateLambda(void);
	std::vector<double> FeedForward(const std::vector<double> &values);

	std::vector<double> m_OutputValues;
	double last_error;
	double m_MeanSquaredError;
	bool m_WeightElimination;
	double CCSaidaMedio;
	double CCOcultaMedio;
	double GetError(DataPattern **p, WORD NumPad);
	double m_Momentum;
	double m_DeltaLambda;
	double m_CutDown;
	double m_Gamma;

	double CC_Saida, CC_Oculta;
	double m_Lambda, m_Scale;
	double m_HistoricalMSE;
	double m_PruneThreshold;
	double m_MaximumError;
	WORD DelCnt;

	double *q;
	double *p;

	double dOut[MAXSIZE][MAXSIZE], dHid[MAXSIZE][MAXSIZE];	// Max 5 neu saídas e 50 neu de camada oculta
	double dOutOld[MAXSIZE][MAXSIZE], dHidOld[MAXSIZE][MAXSIZE];	// Max 5 neu saídas e 50 neu de camada oculta

	Layer &m_InputLayer;
	Layer &m_HiddenLayer;
	Layer &m_OutputLayer;
};

