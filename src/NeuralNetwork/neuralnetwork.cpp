#include "stdafx.h"
#include "neuralnetwork.h"
#include <iomanip>
#include <fstream>

void NeuralNetwork::setLearningRate(double lr)
{
	m_HiddenLayer.setLearningRate(lr);
	m_OutputLayer.setLearningRate(lr);
}

void NeuralNetwork::BackPropagation(const std::vector<double> &values)
{
	WORD j, k;

	memset(p, 0, sizeof(double)*m_OutputLayer.size());
	memset(q, 0, sizeof(double)*m_HiddenLayer.size());
	CCOcultaMedio = CCSaidaMedio = 0;


	for (k = 0; k < m_OutputLayer.size(); k++)
	{
		p[k] = (m_OutputLayer.m_OutputValues[k] - values[k]) *
			m_OutputLayer.m_OutputValues[k] * (1 - m_OutputLayer.m_OutputValues[k]);

		for (j = 0; j < m_HiddenLayer.size(); j++)
		{
			if (m_OutputLayer.m_Neurons[k]->deletado[j])
				break;
			q[j] = q[j] + p[k] * m_OutputLayer.m_Neurons[k]->m_Weights[j];
			/////////
			CC_Saida = 2 * m_OutputLayer.m_Neurons[k]->m_Weights[j] / ((pow(m_Scale, 2)*
				(1 + (pow(m_OutputLayer.m_Neurons[k]->m_Weights[j], 2) / pow(m_Scale, 2))))) -
				2 * pow(m_OutputLayer.m_Neurons[k]->m_Weights[j], 3) / (pow(m_Scale, 4) *
					pow(1 + pow(m_OutputLayer.m_Neurons[k]->m_Weights[j], 2) / pow(m_Scale, 2), 2));
			/////////
			dOut[j][k] = m_Momentum * (dOut[j][k] + p[k] * m_HiddenLayer.m_OutputValues[j] + m_Lambda * CC_Saida) + ((1 - m_Momentum)*dOutOld[j][k]);
			dOutOld[j][k] = dOut[j][k];
			CCSaidaMedio += CC_Saida / (m_HiddenLayer.size()*m_OutputLayer.size());
		}
	}

	for (j = 0; j < m_HiddenLayer.size(); j++)
	{
		q[j] = q[j] * m_HiddenLayer.m_OutputValues[j] * (1 - m_HiddenLayer.m_OutputValues[j]);


		for (WORD i = 0; i < m_InputLayer.size(); i++)
		{
			if (m_HiddenLayer.m_Neurons[j]->deletado[i])
				break;
			CC_Oculta = 2 * m_HiddenLayer.m_Neurons[j]->m_Weights[i] / ((pow(m_Scale, 2)*
				(1 + (pow(m_HiddenLayer.m_Neurons[j]->m_Weights[i], 2) / pow(m_Scale, 2))))) -
				2 * pow(m_HiddenLayer.m_Neurons[j]->m_Weights[i], 3) / (pow(m_Scale, 4) *
					pow(1 + pow(m_HiddenLayer.m_Neurons[j]->m_Weights[i], 2) / pow(m_Scale, 2), 2));

			dHid[i][j] = m_Momentum * (dHid[i][j] + q[j] * m_InputLayer.m_OutputValues[i] + m_Lambda * CC_Oculta) + ((1 - m_Momentum)*dHidOld[j][k]);
			dHidOld[j][k] = dHid[j][k];

			CCOcultaMedio += CC_Oculta / (m_InputLayer.size() * m_HiddenLayer.size());
		}
	}
}

NeuralNetwork NeuralNetwork::Create(WORD n_inputs, WORD n_hidden, WORD n_outputs) {
	
	Layer inputLayer(n_inputs, n_inputs, ENTRADA);
	Layer hiddenLayer(n_hidden, n_inputs, OCULTA);
	Layer OutputLayer(n_outputs, n_hidden, SAIDA);

	NeuralNetwork r(inputLayer, hiddenLayer, OutputLayer);

	return r;
}

NeuralNetwork::NeuralNetwork(Layer &inputLayer, Layer &hidden, Layer &output)	:
		m_InputLayer(inputLayer)
	,	m_HiddenLayer(hidden)
	,	m_OutputLayer (output)

{
	m_OutputValues.resize(m_OutputLayer.size());

	p = new double[m_OutputLayer.size()];
	q = new double[m_HiddenLayer.size()];

	CC_Oculta = CC_Saida = 0;
	m_Lambda = 0;
	CCSaidaMedio = 0;
	CCOcultaMedio = 0;
	m_DeltaLambda = 0.000001;
	m_Scale = 0.9;
	m_Gamma = 0.99;
	DelCnt = 0; // Total de pesos deletados
	m_PruneThreshold = 0.0001;
	m_CutDown = 0.9;
	m_Momentum = 0.9;
	m_MaximumError = 0;
	m_HistoricalMSE = 0;
	m_WeightElimination = 0;

	memset(dOut, 0, sizeof(dOut));
	memset(dHid, 0, sizeof(dHid));

	memset(dOutOld, 0, sizeof(dOutOld));
	memset(dHidOld, 0, sizeof(dHidOld));
	setLearningRate(0.5);
}

NeuralNetwork::~NeuralNetwork()
{
	
}

std::vector<double> NeuralNetwork::FeedForward(const std::vector<double> &values)
{
	auto i = m_InputLayer.FeedForward(values);
	auto h = m_HiddenLayer.FeedForward(i);
	auto o = m_OutputLayer.FeedForward(h);
	return o;
}

void NeuralNetwork::UpdateWeights(void)
{
	for (WORD j = 0; j < m_HiddenLayer.size(); j++)
		for (WORD i = 0; i < m_InputLayer.size(); i++)
			if (!m_HiddenLayer.m_Neurons[j]->deletado[i])
			{
				m_HiddenLayer.m_Neurons[j]->m_Weights[i] = m_HiddenLayer.m_Neurons[j]->m_Weights[i] -
					m_HiddenLayer.m_Neurons[j]->m_LearningRate * dHid[i][j];
				if ((fabs((float)m_HiddenLayer.m_Neurons[j]->m_Weights[i]) < m_PruneThreshold) && (m_WeightElimination) && (!m_HiddenLayer.m_Neurons[j]->deletado[i]))
				{
					m_HiddenLayer.m_Neurons[j]->m_Weights[i] = 0;
					m_HiddenLayer.m_Neurons[j]->deletado[i] = 1;
					DelCnt++;
				}
			}
	// Saida
	for (WORD k = 0; k < m_OutputLayer.size(); k++)
		for (WORD j = 0; j < m_HiddenLayer.size(); j++)
			if (!m_OutputLayer.m_Neurons[k]->deletado[j])
			{
				m_OutputLayer.m_Neurons[k]->m_Weights[j] = m_OutputLayer.m_Neurons[k]->m_Weights[j] -
					m_OutputLayer.m_Neurons[k]->m_LearningRate * dOut[j][k];
				if ((fabs((float)m_OutputLayer.m_Neurons[k]->m_Weights[j]) < m_PruneThreshold) && (m_WeightElimination) && (!m_OutputLayer.m_Neurons[k]->deletado[j]))
				{
					m_OutputLayer.m_Neurons[k]->m_Weights[j] = 0;
					m_OutputLayer.m_Neurons[k]->deletado[j] = 1;
					DelCnt++;
				}
			}


	memset(dOut, 0, sizeof(dOut));
	memset(dHid, 0, sizeof(dHid));
}

double NeuralNetwork::Learn(const std::vector<DataPattern> &patterns)
{
	m_MeanSquaredError = 0;
	
	for (auto p : patterns) {
		auto values = FeedForward(p.getInput());
		m_MeanSquaredError += pow(values[0] - p.getOutput(0), 2);
		BackPropagation(p.getOutput());
	}
	m_MeanSquaredError /= patterns.size();

	m_HistoricalMSE = m_Gamma * m_HistoricalMSE + (1 - 0.99) * m_MeanSquaredError;
	return m_MeanSquaredError;
}

double NeuralNetwork::GetError(DataPattern **p, WORD NumPad)
{
	double erro = 0;
	for (WORD n = 0; n < NumPad; n++)
	{
		FeedForward(p[n]->getInput());
		erro += pow(m_OutputLayer.m_OutputValues[0] - p[n]->getOutput(0), 2) / NumPad;
	}
	return erro;
}

WORD NeuralNetwork::UpdateLambda(void)
{
	m_WeightElimination = 1;
	double erro_total = m_MeanSquaredError;


	if (erro_total < m_MaximumError)	// Erro est� abaixo do crit�rio
		m_Lambda = m_Lambda + m_DeltaLambda; // Lambda += 10e-6

	if (erro_total < last_error) // Erro est� caindo
		m_Lambda = m_Lambda + m_DeltaLambda; // Lambda += 10e-6

	if (erro_total > last_error) // Erro maior que o �ltimo erro
	{
		if (erro_total < m_HistoricalMSE)	// Erro menor que a m�dia hist�rica
		{
			m_Lambda = m_Lambda - m_DeltaLambda; // Reduz um pouco: Lambda -= 10e-6
			if (m_Lambda < 0)	// Se Lambda negativo: Lambda = 0
				m_Lambda = 0;
		}

		if (erro_total > m_HistoricalMSE) // Erro maior que a m�dia hist�rica
		{
			m_Lambda = m_CutDown * m_Lambda; // Cutdown lambda
		}
	}
	return 0;
}

void NeuralNetwork::Estimate(const std::vector<DataPattern> &p) {

	double erro_total = 0, last_error = 0;
	WORD cnt = 0;
	std::ofstream log("log.txt", std::ios::trunc);

	while (cnt < 4000)
	{
		cnt++;

		last_error = erro_total;
		erro_total = 0;
		m_MeanSquaredError = 0;

		erro_total = Learn(p);

		log << std::setprecision(15) << erro_total << "\tLbd: " << m_Lambda << "  ";

		for (WORD y = 0; y < m_HiddenLayer.m_Neurons.size(); y++)
			for (WORD x = 0; x < m_InputLayer.m_Neurons.size(); x++)
				log << "ON" << y << "P" << x << " " << m_HiddenLayer.m_Neurons[y]->m_Weights[x] << " ";

		for (WORD y = 0; y < m_OutputLayer.m_Neurons.size(); y++)
			for (WORD x = 0; x < m_HiddenLayer.m_Neurons.size(); x++)
				log << "SN" << y << "P" << x << " " << m_OutputLayer.m_Neurons[y]->m_Weights[x] << " ";

		log << std::endl;

		UpdateWeights();
	}


	for (WORD i = 0; i < p.size(); i++)
		FeedForward(p[i].getInput());
}