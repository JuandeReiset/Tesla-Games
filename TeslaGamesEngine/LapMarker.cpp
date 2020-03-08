#include "LapMarker.h"
#include <iostream>

LapMarker::LapMarker(int value)
{
	if (value >= 0) {
		markerValue = value;
	}
		
	else {
		std::cout << "Invalid marker value given to lap marker! Defaulting to 1..." << std::endl;
		markerValue = 1;
	}
		
}
