#include <iostream>


using namespace std;


int main(int argc, char *argv[]){
	auto p = make_shared<int>(42);
	weak_ptr<int> wp(p);
	p.reset();

	if (shared_ptr<int> np = wp.lock()) {
		printf("%d", np);
		printf("aaaa\n");
	}
	else {
		printf("%d", np);
		printf("bbbbb\n");
	}


}