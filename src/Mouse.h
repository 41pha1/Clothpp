#ifndef MOUSE_H_
#define MOUSE_H_

class Mouse {
public:
	int x = 0, y = 0, lx = 0, ly = 0, dx = 0, dy = 0;
	bool left = false, right = false;
	Mouse();
	virtual ~Mouse();
};

#endif /* MOUSE_H_ */
