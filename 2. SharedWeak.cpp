#include "stdafx.h"
#include <iostream>
#include <memory>

class A
{
public:
	A(int v) : val(v) {};
	void print_val()
	{
		std::cout << "Value: " << val << std::endl;
	}
private:
	int val;
};

int main()
{
	A *aptr = new A(100);

	std::shared_ptr<A> sptr1(aptr);
	sptr1->print_val();

	std::shared_ptr<A> sptr2 = sptr1;
	sptr2->print_val();


	std::weak_ptr<A> wptr = sptr1;
	std::cout << "Shared count: " << wptr.use_count() << std::endl;

	sptr1.reset();
	std::cout << "Shared count: " << wptr.use_count() << std::endl;

	sptr2.reset();
	std::cout << "Shared count: " << wptr.use_count() << std::endl;

	std::cin.ignore();
	return 0;
}
