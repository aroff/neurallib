#include "stdafx.h"
#include "datapattern.h"



DataPattern::DataPattern(WORD n_inputs, WORD n_outputs)
{
	m_Input.resize(n_inputs);
	m_Output.resize(n_outputs);
}

void DataPattern::Load(std::ifstream &infile)
{
	WORD i;
	int ch;

	for (i = 0; i < (m_Input.size()); i++)
		infile >> m_Input[i];

	for (i = 0; i < m_Output.size(); i++)
		infile >> m_Output[i];


	ch = infile.peek();

	while (ch == '\n' || ch == EOF)
	{
		ch = infile.get();
		if (ch == EOF)
			break;
		ch = infile.peek();
	}
}

DataPattern::~DataPattern()
{
}

