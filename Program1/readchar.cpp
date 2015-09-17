//============================================================================
// Name        : readchar.cpp
// Description : demo reading characters using cin.get
//============================================================================

#include <iostream>

int main()
{
	char	ch;

	while( std::cin.good() ) {
		ch = std::cin.get();
		std::cout << ch;
	}


	return 0;
}