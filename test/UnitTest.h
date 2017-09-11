#ifndef UNITTEST_H
#define UNITTEST_H
#include <vector>

class TestCase {
	public:
		TestCase(const char* case_name) : testcase_name(case_name) {}

		// run method for test case.
		virtual void Run() = 0;

		int nTestResult; // result of runnig test case.
		const char* testcase_name; // name of the test case.
};

class UnitTest {
	public:
		// get singleton
		static UnitTest* GetInstance();

		// register test case.
		TestCase* RegisterTestCase(TestCase* testcase);

		// run the test case.
		int Run();

		TestCase* CurrentTestCase; // 
		int nTestResult; // last result of tests.
		int nPassed; // num of passed cases.
		int nFailed; // num of failed cases.
	protected:
		std::vector<TestCase*> testcases_; // list of cases.
};

#define TESTCASE_NAME(testcase_name)  testcase_name##_TEST

#define UNIT_TEST_(testcase_name) \
class TESTCASE_NAME(testcase_name) : public TestCase \
{ \
public: \
    TESTCASE_NAME(testcase_name)(const char* case_name) : TestCase(case_name){}; \
    virtual void Run(); \
private: \
    static TestCase* const testcase_; \
}; \
\
TestCase* const TESTCASE_NAME(testcase_name) \
    ::testcase_ = UnitTest::GetInstance()->RegisterTestCase( \
        new TESTCASE_NAME(testcase_name)(#testcase_name)); \
void TESTCASE_NAME(testcase_name)::Run()

#define UTEST(testcase_name)  UNIT_TEST_(testcase_name)


#define RUN_ALL_TESTS()  UnitTest::GetInstance()->Run();

#define EXPECT_EQ(m, n) \
    if (m != n) \
    { \
        UnitTest::GetInstance()->CurrentTestCase->nTestResult = 0; \
        std::cout << "Failed" << std::endl; \
        std::cout << "Expect:" << m << std::endl; \
        std::cout << "Actual:" << n << std::endl; \
    }

#endif
