#include <iostream>

void hello_world(void)
{
	std::cout << "Hello world!\n";
}

void practice_1_15_2_2(void)
{
	int x = 5;
	int y = 7;
	char rep;

	std::cout << std::endl;
	std::cout << x + y << " " << x * y;
	std::cout << std::endl;
}

void listing_2_2(void)
{
	std::cout << "Hello there.\n";
	std::cout << "Here is 5: " << 5 << "\n";
	std::cout << "The manipulator std::endl ";
}

int main(void)
{
	char rep;

	listing_2_2();
	std::cin >> rep;

	return 0;
}