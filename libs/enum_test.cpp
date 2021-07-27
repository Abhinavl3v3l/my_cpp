#include <iostream>
#include "enum_test.hpp"

enum_test::enum_test(/* args */)
{
	cout << "IN \n"; 
}

enum_test::~enum_test()
{
	cout << "OUT \n" ;
}

void enum_test::fun(){

		// examples of bad use of plain enums:
		Color color = Color::red;
		Card card = Card::green_card;

		int num = color; // no problem

		if (color == Card::red_card) // no problem (bad)
			cout << "bad" << endl;

		if (card == Color::green) // no problem (bad)
			cout << "bad" << endl;

		// examples of good use of enum classes (safe)
		Animal a = Animal::deer;
		Mammal m = Mammal::deer;

		int num2 = a; // error
		if (m == a)	  // error (good)
			cout << "bad" << endl;

		if (a == Mammal::deer) // error (good)
			cout << "bad" << endl;
	
	return;
	}
