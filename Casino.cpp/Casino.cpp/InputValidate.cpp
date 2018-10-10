#include "InputValidate.hpp"

Validate::Validate()
{

}

int Validate::inputValidate(int min, int max)
{
	int temp = 0;

	cin >> temp;
	while (temp < min || temp > max || cin.fail())
	{
		if (cin.fail())
		{
			std::cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please enter a valid input: ";
		}

		else
		{
			cout << "Please enter an input between (" << min << " - " << max << "): ";
		}

		cin >> temp;
	}
	return temp;
}

Validate::~Validate()
{

}