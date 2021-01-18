#pragma once
#include <cstdint>
#include <iostream>
#include <SDL.h>

class Timer {
	uint64_t delay;
public:
	Timer(unsigned int time = 0) {
		SetDelay(time);
	};

	~Timer() {};

	void SetDelay(const uint64_t delay) {
		this->delay = SDL_GetTicks() + delay;
	}
	
	bool TimeElasped() {
		if (delay <= SDL_GetTicks()) {
			return true;
		}


		return false;
	}
};
