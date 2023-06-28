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



struct aproxy {
    aproxy(int& r) : mPtr(&r) {}
    void operator = (int n) {
        if (n > 1 || n < 0) {
            throw "not binary digit";
        }
        *mPtr = n;
    }
    int * mPtr;
};

struct array1 {
    int mArray[10];
    aproxy operator[](int i) {
		mArray[i];
		cout << i << endl;
        return aproxy(mArray[i]);
    }
};


int main(int argc, char *argv[])
{
    try {
        array1 a;
        a[0] = 1;   // ok
        a[0] = 42;  // throws exception
    }
    catch (const char * e) {
        cout << e << endl;
    }
	//test_finally();
	while(1);
	return 0;
}