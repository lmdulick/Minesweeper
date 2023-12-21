// Board_Nums.CPP

#include "Board_Nums.h"

Board_Nums::Board_Nums(int number) {
	if (number == 1)
		SetSprite("number_1");
	if (number == 2)
		SetSprite("number_2");
	if (number == 3)
		SetSprite("number_3");
	if (number == 4)
		SetSprite("number_4");
	if (number == 5)
		SetSprite("number_5");
	if (number == 6)
		SetSprite("number_6");
	if (number == 7)
		SetSprite("number_7");
	if (number == 8)
		SetSprite("number_8");
}