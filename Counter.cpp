// COUNTER.CPP

#include "Counter.h"

// sprite == "digits"
Counter::Counter(int counterDigit) {
	SetSprite("digits");
	GetSprite().setTextureRect(sf::IntRect((counterDigit * 21), 0, 21, 32));
}