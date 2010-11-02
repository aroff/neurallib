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

	void Estimate(const std::vector<DataPattern> &pattern);
	void setLearningRate(double lr);
	std::vector<double> valores_de_saida;
	double last_error;
	double m_MeanSquaredError;


	Layer &m_InputLayer;
	Layer &m_HiddenLayer;
	Layer &m_OutputLayer;

	std::vector<double> FeedForward(const std::vector<double> &values);
	void BackPropagation(const std::vector<double> &values);
	void UpdateWeights(void);

	double CC_Saida, CC_Oculta;
	double Lambda, Escala;
	double m_HistoricalMSE;
	double ValorPoda;
	double Erro_Maximo;
	WORD DelCnt;
	double Learn(const std::vector<DataPattern> &pattern);
	WORD UpdateLambda(void);

protected:
	BOOL m_WeightElimination;
	double CCSaidaMedio;
	double CCOcultaMedio;
	double GetError(DataPattern **p, WORD NumPad);
	double Momentum;
	double DeltaLambda;
	double CutDown;
	double m_Gamma;

	double *derivadas_oculta;	// Derivadas do erro em relação ao xxxxxx

	double *q;
	double *p;

	double dOut[MAXSIZE][MAXSIZE], dHid[MAXSIZE][MAXSIZE];	// Max 5 neu saídas e 50 neu de camada oculta
	double dOutOld[MAXSIZE][MAXSIZE], dHidOld[MAXSIZE][MAXSIZE];	// Max 5 neu saídas e 50 neu de camada oculta


};

