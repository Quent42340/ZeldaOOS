/*---------------------------------------------------------------------------------

	Eleandra
	Copyright (C) 2012 Quentin BAZIN quent42340@gmail.com
	
	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

---------------------------------------------------------------------------------*/
#include <nds.h>
#include "timer.h"

int Timer::osTime;

Timer::Timer() {
	s_t = osTime;
	s_isStarted = false;
	s_tick = 0;
}

Timer::~Timer() {
	reset();
	stop();
}

void Timer::stop() {
	if(s_isStarted) {
		s_isStarted = false;
		s_tick = osTime - s_t;
	}
}

void Timer::start() {
	if(!s_isStarted) {
		s_isStarted = true;
		s_t = osTime - s_tick;
	}
}

void Timer::reset() {
	s_t = osTime;
	s_isStarted = false;
	s_tick = 0;
}

void OnTimer(){
	Timer::osTime++;
}

void Timer::initTimers() {
	TIMER1_CR = 0;
	TIMER1_DATA = TIMER_FREQ_1024(1000);
	TIMER1_CR = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
	irqSet(IRQ_TIMER1, OnTimer);
	irqEnable(IRQ_TIMER1);
	osTime = 0;
}

