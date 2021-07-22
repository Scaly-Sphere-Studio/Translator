#include "data.hpp"


Evaluation::Evaluation()
{
	fill(0);
}

Evaluation::Evaluation(const std::array<uint16_t, 5> init_array)
{
	*this = init_array;
}

float Evaluation::average() const
{
	float count = 0, mean = 0;
	for (float i = 0; i < 5; i++) {
		count += this->at(i);
		mean += (i+1) * this->at(i);
	}

	return mean / count;
}

uint32_t  Evaluation::count() const
{
	uint32_t count = 0;
	for (float i = 0; i < 5; i++) {
		count += this->at(i);
	}

	return count;
}
