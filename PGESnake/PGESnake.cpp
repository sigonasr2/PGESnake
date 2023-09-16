#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

//THIS IS WRITTEN USING OLC GPE, CHECK OUT onelonecoder.com
//Or else
class Snake : public olc::PixelGameEngine {
public:
	Snake() {
		sAppName = "Snake";
	}

	enum direction { STOP, LEFT, RIGHT, DOWN, UP };
	direction dir;
	//Game variables
	int score;
	//Snake variables
	int SnakeXPos = 50, SnakeYPos = 50, speed = 1;
	int tailX[100], tailY[100], tailLength;
	//Tail coordinates
	int fposX, fposY, sposX, sposY;
	//Target variables
	int targetX, targetY;



private:

public:
	bool OnUserUpdate(float fElapsedTime) override {
		Clear(olc::BLACK);
		//Draw top border
		DrawLine(5, 5, ScreenWidth() - 5, 5, olc::WHITE);
		//Draw left border
		DrawLine(5, 5, 5, ScreenHeight() - 5, olc::WHITE);
		//Draw right border
		DrawLine(ScreenWidth() - 5, 5, ScreenWidth() - 5, ScreenHeight() - 5, olc::WHITE);
		//Draw bottom border
		DrawLine(5, ScreenHeight() - 5, ScreenWidth() - 5, ScreenHeight() - 5, olc::WHITE);

		//Draw Snake
		DrawRect(SnakeXPos, SnakeYPos, 1, 1, olc::GREEN);

		//Directions changes
		if (GetKey(olc::Key::UP).bPressed && dir != DOWN) {
			dir = UP;
		}
		if (GetKey(olc::Key::DOWN).bPressed && dir != UP) {
			dir = DOWN;
		}
		if (GetKey(olc::Key::LEFT).bPressed && dir != RIGHT) {
			dir = LEFT;
		}
		if (GetKey(olc::Key::RIGHT).bPressed && dir != LEFT) {
			dir = RIGHT;
		}

		//Move Snake
		switch (dir) {
		case LEFT:
			SnakeXPos -= speed;
			break;
		case RIGHT:
			SnakeXPos += speed;
			break;
		case DOWN:
			SnakeYPos += speed;
			break;
		case UP:
			SnakeYPos -= speed;
			break;
		}
		return true;
	}

	bool OnUserCreate() override {
		dir = STOP;

		return true;
	}
};

int main() {
	Snake demo;
	if (demo.Construct(200, 200, 5, 5))
		demo.Start();
	return 0;
}