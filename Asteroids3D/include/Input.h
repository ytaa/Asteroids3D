#pragma once
#define INPUT_FIRST_SPECIAL_KEY 255
#define INPUT_KEY_F1 256
#define INPUT_KEY_F2 257
#define INPUT_KEY_F3 258
#define INPUT_KEY_F4 259
#define INPUT_KEY_F5 260
#define INPUT_KEY_F6 261
#define INPUT_KEY_F7 262
#define INPUT_KEY_F8 263
#define INPUT_KEY_F9 264
#define INPUT_KEY_F10 265
#define INPUT_KEY_F11 266
#define INPUT_KEY_F12 267
#define INPUT_KEY_LEFT 268
#define INPUT_KEY_UP 269
#define INPUT_KEY_RIGHT 270
#define INPUT_KEY_DOWN 271
#define INPUT_KEY_PAGE_UP 272
#define INPUT_KEY_PAGE_DOWN 273
#define INPUT_KEY_HOME 274
#define INPUT_KEY_END 275
#define INPUT_KEY_INSERT 276
#define INPUT_KEY_LSHIFT 280
#define INPUT_KEY_RSHIFT 281
#define INPUT_KEY_LCTRL 282
#define INPUT_KEY_RCTRL 283
#define INPUT_KEY_LALT 284
#define INPUT_KEY_RALT 285
#define INPUT_KEYSNUMBER 286
class Input
{
public:
	Input();
	virtual ~Input();
	virtual void keyDown(unsigned char key, int xx, int yy) = 0;
	virtual void specialKeyDown(int key, int xx, int yy) = 0;
	virtual void keyUp(unsigned char key, int xx, int yy) = 0;
	virtual void specialKeyUp(int key, int xx, int yy) = 0;
	virtual void mouseMove(int x, int y) = 0;
	virtual void mouseAction(int button, int state, int x, int y) = 0;

};

