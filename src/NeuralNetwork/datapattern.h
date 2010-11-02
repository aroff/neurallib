#pragma once
#include <fstream>
#include <vector>

class DataPattern
{
public:
	std::vector<double> m_Input;
	std::vector<double> m_Output;
	DataPattern() {

	}

	DataPattern(WORD nEnt, WORD nSai);
	~DataPattern();

	void Load(std::ifstream &infile);

private:
	void DefineEntrada(WORD idx, double value) { m_Input[idx] = value; }
	void DefineSaida(WORD idx, double value) { m_Output[idx] = value; }
	double LerEntrada(WORD idx) { return m_Input[idx]; }
	double LerSaida(WORD idx) { return m_Output[idx]; }
};

