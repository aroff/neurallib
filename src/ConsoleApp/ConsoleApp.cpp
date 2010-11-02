// ConsoleApp.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include "pch.h"
#include <iostream>

// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração

// Dicas para Começar: 
//   1. Use a janela do Gerenciador de Soluções para adicionar/gerenciar arquivos
//   2. Use a janela do Team Explorer para conectar-se ao controle do código-fonte
//   3. Use a janela de Saída para ver mensagens de saída do build e outras mensagens
//   4. Use a janela Lista de Erros para exibir erros
//   5. Ir Para o Projeto > Adicionar Novo Item para criar novos arquivos de código, ou Projeto > Adicionar Item Existente para adicionar arquivos de código existentes ao projeto
//   6. No futuro, para abrir este projeto novamente, vá para Arquivo > Abrir > Projeto e selecione o arquivo. sln

#include <memory.h>
#include <iomanip>
#include <math.h>
#include <fstream>
#include <iosfwd>
#include <stdlib.h>

#include <neuralnetwork/neuralnetwork.h>
#include <neuralnetwork/test.h>


int main(void)
{
	Test t;
	auto xx = t.Test1();

	return 0;

	//WORD nPad = 0;
	//double erro_total = 1, last_error = 0;
	//WORD i, n;
	//WORD cnt = 0;
	//DataPattern *p[50];
	//WORD NumEntradas, NumOcultos, NumSaidas;

	//std::ifstream infile("teste.pad");

	//infile >> NumEntradas;
	//infile >> NumOcultos;
	//infile >> NumSaidas;

	//nPad = 0;
	//while (!infile.eof())
	//{
	//	p[nPad] = new DataPattern(NumEntradas, NumSaidas);
	//	p[nPad]->Load(infile);
	//	nPad++;
	//}


	//NeuralNetwork r = NeuralNetwork::Create(NumEntradas, NumOcultos, NumSaidas);	// 2 Entradas, 3 Ocultos, 1 saída

	//r.Erro_Maximo = 0.1;

	//std::ofstream log("log.txt", std::ios::trunc);


	//while (cnt < 4000)
	//{
	//	cnt++;

	//	last_error = erro_total;
	//	erro_total = 0;

	//	for (n = 0; n < nPad; n++)
	//	{
	//		//cout << "Padrão: " << p[n]->entradas[0]<< " - " ;

	//		r.FeedForward(p[n]->m_Input);

	//		//cout << setprecision(5)<< "Saida: " << p[n]->saidas[0] << " -> "  << r.Saida->valores_de_saida [0] <<endl;

	//		r.m_MeanSquaredError = pow(r.Saida.valores_de_saida[0] - p[n]->m_Output[0], 2) / nPad;
	//		// +pow(r.Saida->valores_de_saida [1] - p[n]->saidas[1],2);


	//		r.BackPropagation(p[n]->m_Output);

	//		erro_total += r.m_MeanSquaredError;
	//	}

	//	r.m_HistoricalMSE = 0.99 * r.m_HistoricalMSE + (1 - 0.99) * erro_total;

	//	if (cnt > 1000)
	//	{
	//		if (erro_total < r.Erro_Maximo)	// Erro está abaixo do critério
	//			r.Lambda = r.Lambda + 0.000001; // Lambda += 10e-6

	//		if (erro_total < last_error) // Erro está caindo
	//			r.Lambda = r.Lambda + 0.000001; // Lambda += 10e-6

	//		if (erro_total > last_error) // Erro maior que o último erro
	//		{
	//			if (erro_total < r.m_HistoricalMSE)	// Erro menor que a média histórica
	//			{
	//				r.Lambda = r.Lambda - 0.000001; // Reduz um pouco: Lambda -= 10e-6
	//				if (r.Lambda < 0)	// Se Lambda negativo: Lambda = 0
	//					r.Lambda = 0;
	//			}

	//			if (erro_total > r.m_HistoricalMSE) // Erro maior que a média histórica
	//			{
	//				r.Lambda = 0.9 * r.Lambda; // Cutdown lambda
	//			}
	//		}

	//	} // fim do if(cnt ...

	//	r.setLearningRate(0.5); // Define Learning_rate

	//	//cout << "Cnt: " << cnt << "  - Erro Médio: "<< setprecision(17) << erro_total << endl;
	//	//cout << setprecision(5) << erro_total << "\tLbd: " << r.Lambda;
	//	//cout << setprecision(5) << " " << r.Oculta.neuro[0]->pesos[0] << " " << r.Oculta.neuro[0]->pesos[1] << " " << r.Oculta.neuro[1]->pesos[0] << " " << r.Oculta.neuro[1]->pesos[1] <<endl;

	//	log << std::setprecision(15) << erro_total << "\tLbd: " << r.Lambda << "  ";

	//	for (WORD y = 0; y < NumOcultos; y++)
	//		for (WORD x = 0; x < NumEntradas; x++)
	//			log << "ON" << y << "P" << x << " " << r.Oculta.neuro[y].m_Weights[x] << " ";

	//	for (WORD y = 0; y < NumSaidas; y++)
	//		for (WORD x = 0; x < NumOcultos; x++)
	//			log << "SN" << y << "P" << x << " " << r.Oculta.neuro[y].m_Weights[x] << " ";

	//	log << std::endl;


	//	///////////////////////////////////////// Oculta

	//	for (WORD j = 0; j < r.Oculta.size(); j++)
	//		for (i = 0; i < r.Entrada.size(); i++)
	//			r.Oculta.neuro[j].m_Weights[i] = r.Oculta.neuro[j].m_Weights[i] -
	//			r.Oculta.neuro[j].m_LearningRate * r.dHid[i][j];
	//	// Saida
	//	for (WORD k = 0; k < r.Saida.size(); k++)
	//		for (WORD j = 0; j < r.Oculta.size(); j++)
	//			r.Saida.neuro[k].m_Weights[j] = r.Saida.neuro[k].m_Weights[j] -
	//			r.Saida.neuro[k].m_LearningRate * r.dOut[j][k];


	//	memset(r.dOut, 0, sizeof(r.dOut));
	//	memset(r.dHid, 0, sizeof(r.dHid));

	//	////////////////////////////////////////////////////////////
	//	return 0;
	//}


	//for (i = 0; i < nPad; i++)
	//{
	//	r.FeedForward(p[i]->m_Input);
	//	//cout << "Saida1: " << r.Saida->valores_de_saida [0] <<endl;
	//	//<< 			"Saida2: " << r.Saida->valores_de_saida [1] <<endl;
	//}

}

//void _alex(void)
//{
//	double erro_total = 0, last_error = 0;
//	WORD nPad = 0;
//	WORD i;
//	WORD cnt = 0;
//	std::vector<DataPattern> p;
//	WORD NumEntradas, NumOcultos, NumSaidas;
//
//	std::ifstream infile("teste.pad");
//
//	infile >> NumEntradas;
//	infile >> NumOcultos;
//	infile >> NumSaidas;
//
//	nPad = 0;
//	while (!infile.eof())
//	{
//		p[nPad] = DataPattern(NumEntradas, NumSaidas);
//		p[nPad].Load(infile);
//		nPad++;
//	}
//
//
//	NeuralNetwork r = NeuralNetwork::Create(NumEntradas, NumOcultos, NumSaidas);
//
//	std::ofstream log("log.txt", std::ios::trunc);
//
//	while (cnt < 4000)
//	{
//		cnt++;
//
//		last_error = erro_total;
//		erro_total = 0;
//		r.m_MeanSquaredError = 0;
//
//		erro_total = r.Learn(p);
//		/*for (WORD n=0;n<nPad;n++)
//			{
//			r.FeedForward(p[n]->entradas, r.nEntradas);
//			r.emq += pow(r.Saida->valores_de_saida [0] - p[n]->saidas[0],2)/nPad;
//			r.BackPropagation(p[n]->saidas);
//			}
//
//		erro_total = r.emq;		*/
//
//		r.setLearningRate(0.5); // Define Learning_rate
//
//		log << std::setprecision(15) << erro_total << "\tLbd: " << r.Lambda << "  ";
//
//		for (WORD y = 0; y < NumOcultos; y++)
//			for (WORD x = 0; x < NumEntradas; x++)
//				log << "ON" << y << "P" << x << " " << r.Oculta.neuro[y].m_Weights[x] << " ";
//
//		for (WORD y = 0; y < NumSaidas; y++)
//			for (WORD x = 0; x < NumOcultos; x++)
//				log << "SN" << y << "P" << x << " " << r.Oculta.neuro[y].m_Weights[x] << " ";
//
//		log << std::endl;
//
//		///////////////////////////////////////// Oculta
//		r.UpdateWeights();
//		/*
//		for(WORD j=0;j<r.Oculta.nNeuronios;j++)
//			for(i=0;i<r.Entrada->nNeuronios;i++)
//				r.Oculta.neuro[j]->pesos[i] = r.Oculta.neuro[j]->pesos[i] -
//					r.Oculta.neuro[j]->learning_rate * r.dHid[i][j];
//		// Saida
//		for(WORD k=0;k<r.Saida->nNeuronios;k++)
//			for(j=0;j<r.Oculta.nNeuronios;j++)
//				r.Saida->neuro[k]->pesos[j] = r.Saida->neuro[k]->pesos[j] -
//					r.Saida->neuro[k]->learning_rate * r.dOut[j][k];
//
//
//		memset(r.dOut, 0, sizeof(r.dOut));
//		memset(r.dHid, 0, sizeof(r.dHid));
//*/
//	}
//
//
//	for (i = 0; i < nPad; i++)
//		r.FeedForward(p[i].m_Input);
//
//}
