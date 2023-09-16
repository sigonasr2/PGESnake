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
	float SnakeXPos = 50, SnakeYPos = 50;
	int tailX[100], tailY[100], tailLength;
	//Tail coordinates
	int fposX, fposY, sposX, sposY;
	//Target variables
	int targetX, targetY;

	bool GameOver;

	void SnakeDead() {
		if (GameOver == true) {
			Clear(olc::BLACK);
			DrawString(ScreenWidth() - ((ScreenWidth() / 2) + (ScreenWidth() / 2.8)), ScreenHeight() / 2 - 5, "Game Over", olc::RED, 1);
		}
}
	void BorderCollisionCheck() {
		if (SnakeXPos <= 5) {
			GameOver = true;
			SnakeDead();
		}
		if (SnakeXPos >= ScreenWidth() - 5) {
			GameOver = true;
			SnakeDead();
		}
		if (SnakeYPos <= 5) {
			GameOver = true;
			SnakeDead();
		}
		if (SnakeYPos >= ScreenHeight() - 5) {
			GameOver = true;
			SnakeDead();
		}
	}
	void userInput(float speed) {
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
	}

private:

public:
	bool OnUserUpdate(float fElapsedTime) override {
		float speed = 20 * fElapsedTime;
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
		DrawRect(SnakeXPos, SnakeYPos, 1, 1, olc::DARK_GREEN);

		//Border collision
		BorderCollisionCheck();

		//Directions changes
		userInput(speed);

		return true;
	}

	bool OnUserCreate() override {
		dir = STOP;

		return true;
	}
};

int main() {
	Snake demo;
	if (demo.Construct(100, 100, 10, 10))
		demo.Start();
	return 0;
}