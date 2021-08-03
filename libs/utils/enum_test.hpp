#include <iostream>

using namespace::std;

class enum_test
{
private:
	/* data */
public:
	enum_test(/* args */);
	~enum_test();
	enum Color
	{
		red,
		green,
		blue
	}; // plain enum
	enum Card
	{
		red_card,
		green_card,
		yellow_card
	}; // another plain enum
	enum class Animal
	{
		dog,
		deer,
		cat,
		bird,
		human
	}; // enum class
	enum class Mammal
	{
		kangaroo,
		deer,
		human
	}; // another enum class
	void fun();
};
