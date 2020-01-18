#pragma once
#include <fstream>
#include <vector>

class DataPattern
{
public:
	DataPattern();
	DataPattern(const std::vector<double> &inputs, const std::vector<double> &outputs);
	~DataPattern();

	const std::vector<double> &getInput() const { return m_Input; }
	void setInput(size_t idx, double value) { m_Input[idx] = value; }
	double getInput(size_t idx) const { return m_Input[idx]; }
	
	const std::vector<double> &getOutput() const { return m_Output; }
	double getOutput(size_t idx) const { return m_Output[idx]; }
	void setOutput(size_t idx, double value) { m_Output[idx] = value; }

	void Load(std::ifstream &infile);

private:
	std::vector<double> m_Input;
	std::vector<double> m_Output;

};

