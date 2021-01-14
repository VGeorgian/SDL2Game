#pragma once
#include <cstdint>
#include <iostream>
#include <chrono>
using namespace std::chrono;

class Timer {
	uint64_t delay;
public:
	Timer(unsigned int time = 0) {
		SetDelay(time);
	};

	~Timer() {};

	void SetDelay(const uint64_t delay) {
		milliseconds ms = duration_cast<milliseconds>(
			system_clock::now().time_since_epoch()
			);

		this->delay = delay + ms.count();
	}
	
	bool TimeElasped() {
		if (delay == 0) {
			delay = duration_cast<milliseconds>
				(system_clock::now().time_since_epoch()).count();
		}

		if (delay <= duration_cast<milliseconds>
			(system_clock::now().time_since_epoch()).count()) {
			return true;
		}


		return false;
	}
};
