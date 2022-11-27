#ifndef INPUT_H_
#define INPUT_H_

#include <map>

#include "Mouse.h"
#include "Simulation.h"
#include "Camera.h"

class Input {
public:
	std::map<int, bool> keyboard;
	Mouse * mouse;

	Input();
	void pollInputs();
	void update(Camera * cam);
	virtual ~Input();
};

#endif /* INPUT_H_ */
