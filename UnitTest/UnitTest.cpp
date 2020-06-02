#include "pch.h"
#include "CppUnitTest.h"
#include "Sergey.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(addNode_contains)
		{
			Network test;
			test.addNode("A");
			test.addNode("B");
			test.addNode("C");
			test.addNode("D");
			Assert::AreEqual(false, test.contains("H"));
			Assert::AreEqual(true, test.contains("C"));
			test.addNode("H");
			Assert::AreEqual(true, test.contains("H"));
			try
			{
				test.addNode("3");
			}
			catch (const std::exception& ex)
			{
				Assert::AreEqual(ex.what(), "ERROR: this node already exists");
			}
		}

		TEST_METHOD(addChannel_Algorhytm)
		{
			Network test;
			test.addNode("A");
			test.addNode("B");
			test.addNode("C");
			test.addNode("D");
			int compare = 0;
			Assert::AreEqual(compare, test.Algorhytm(0, 1));
			test.addChannel("A", "B", 5);
			compare = 5;
			Assert::AreEqual(compare, test.Algorhytm(0, 1));
			try
			{
				test.Algorhytm(10, 1);
			}
			catch (const std::exception& ex)
			{
				Assert::AreEqual(ex.what(), "Out of range");
			}
			test.addChannel("A", "D", 10);
			test.addChannel("D", "B", 20);
			test.addChannel("B", "C", 90);
			test.addChannel("C", "D", 100);
			compare = 15;
			Assert::AreEqual(compare, test.Algorhytm(0, 1));
			compare = 20;
			Assert::AreEqual(compare, test.Algorhytm(2, 1));
			try
			{
				test.Algorhytm("E", "A");
			}
			catch (const std::exception& ex)
			{
				Assert::AreEqual(ex.what(), "Couldn't find this dot");
			}
		}
	};
}