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
	int fruit1X, fruit1Y, fruit2X, fruit2Y;
	bool fruit1 = false, fruit2 = false;
	bool GameOver;

	void SnakeDead() {
		if (GameOver == true) {
			Clear(olc::BLACK);
			DrawString(ScreenWidth() - ((ScreenWidth() / 2) + (ScreenWidth() / 2.8)), ScreenHeight() / 2 - 5, "Game Over", olc::RED, 1);
		}
}
	void BorderCollisionCheck() {
		if (SnakeXPos <= 3) {
			GameOver = true;
			SnakeDead();
		}
		if (SnakeXPos >= ScreenWidth() - 3) {
			GameOver = true;
			SnakeDead();
		}
		if (SnakeYPos <= 3) {
			GameOver = true;
			SnakeDead();
		}
		if (SnakeYPos >= ScreenHeight() - 3) {
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
	void FruitCoordGen() {
		//Fruit1
		if (fruit1 == false) {
			fruit1X = rand() & ScreenWidth();
			fruit1Y = rand() & ScreenHeight();
			fruit1 = true;
		}
		if (fruit1X <= 2 || fruit1X >= ScreenWidth() - 2) {
			fruit1X = rand() & ScreenWidth();
		}
		if (fruit1Y <= 2 || fruit1Y >= ScreenHeight() - 2) {
			fruit1Y = rand() & ScreenHeight();
		}
		//Fruit2
		//if (fruit2 == false) {
			//fruit2X = rand() & ScreenWidth();
			//fruit2Y = rand() & ScreenHeight();
			//fruit2 = true;
		//}
		//if (fruit2X <= 2 || fruit2X >= ScreenWidth() - 2) {
			//fruit1X = rand() & ScreenWidth();
		//}
		//if (fruit2Y <= 2 || fruit2Y >= ScreenHeight() - 2) {
			//fruit1Y = rand() & ScreenHeight();
		//}
		//if (fruit1X == fruit2X) {
			//fruit1X = rand() & ScreenWidth();
		//}
		//if (fruit1Y == fruit2Y) {
			//fruit1Y = rand() & ScreenWidth();
		//}
	}

private:

public:
	bool OnUserUpdate(float fElapsedTime) override {
		float speed = 20 * fElapsedTime;
		//Fruit coord gen
		FruitCoordGen();

		Clear(olc::BLACK);
		//Draw top border
		DrawLine(2, 2, ScreenWidth() - 2, 2, olc::WHITE);
		//Draw left border
		DrawLine(2, 2, 2, ScreenHeight() - 2, olc::WHITE);
		//Draw right border
		DrawLine(ScreenWidth() - 2, 2, ScreenWidth() - 2, ScreenHeight() - 2, olc::WHITE);
		//Draw bottom border
		DrawLine(2, ScreenHeight() - 2, ScreenWidth() - 2, ScreenHeight() - 2, olc::WHITE);

		//Draw Snake
		DrawRect(SnakeXPos, SnakeYPos, 1, 1, olc::DARK_GREEN);

		//Draw fruit
		DrawRect(fruit1X, fruit1Y, 1, 1, olc::RED);
		//DrawRect(fruit2X, fruit2Y, 1, 1, olc::RED);

		//Fruit collision
		if (floor(SnakeXPos) == fruit1X && floor(SnakeYPos) == fruit1Y) {
			score++;
			fruit1 = false;
		}

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