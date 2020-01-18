#include "stdafx.h"
#include "datapattern.h"

DataPattern::DataPattern() {

}

DataPattern::DataPattern(const std::vector<double> &inputs, const std::vector<double> &outputs)	:
		m_Input(inputs)
	,	m_Output(outputs)
{
}

void DataPattern::Load(std::ifstream &infile)
{
	int ch;

	for (size_t i = 0; i < (m_Input.size()); i++)
		infile >> m_Input[i];

	for (size_t i = 0; i < m_Output.size(); i++)
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
