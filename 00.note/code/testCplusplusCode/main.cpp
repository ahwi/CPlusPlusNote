#include <iostream>
#include "Logic_helper.h"

using namespace std;

template<typename... Args>
void test_any(unsigned seconds, Args... args) 
{
	//unsigned secods = 10;

	for (int i = 0; i != seconds; ++i) {
		if (Logic::any([](bool *b) {return *b; }, args...)) {
			cout << "true" << endl;
		}
		else
		{
			cout << "false" << endl;
		}
	}

}

void test_logic_helper()
{

	unsigned seconds = 10;
	bool aa = false;
	bool *exit_flags = &aa;
	test_any(seconds, exit_flags);

}

void test_finally()
{
	cout << "start" << endl;
	{
		auto test = finally([&] {
			//int a = 1;
			cout << "finally" << endl;
		});
		cout << "aaa" << endl;
	}


		cout << "bbb" << endl;
}

int main(int argc, char *argv[])
{
	test_finally();
	return 0;
}