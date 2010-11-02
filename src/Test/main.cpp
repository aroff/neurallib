#include "stdafx.h"
#include "CppUnitTest.h"
#include <neuralnetwork/test.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{		
	TEST_CLASS(MainTest)
	{
	public:

		MainTest() {

		}
		
		TEST_METHOD(XORProblem)
		{
			Test t;
			auto r = t.Test1();
		}

	};
}