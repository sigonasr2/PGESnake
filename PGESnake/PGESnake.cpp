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
	float SnakeXPos, SnakeYPos, OldSnakeXPos, OldSnakeYPos;
	int tailX[100], tailY[100], tailLength = 0;
	//Tail Coordinates
	float fposX, fposY, sposX, sposY;
	float x, y;
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
			OldSnakeXPos = SnakeXPos + speed;
			OldSnakeYPos = SnakeYPos;
			SnakeXPos -= speed;
			break;
		case RIGHT:
			OldSnakeXPos = SnakeXPos - speed;
			OldSnakeYPos = SnakeYPos;
			SnakeXPos += speed;
			break;
		case DOWN:
			OldSnakeYPos = SnakeYPos - speed;
			OldSnakeXPos = SnakeXPos;
			SnakeYPos += speed;
			break;
		case UP:
			OldSnakeYPos = SnakeYPos + speed;
			OldSnakeXPos = SnakeXPos;
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
		Clear(olc::BLACK);
		//Draw top border
		DrawLine(2, 2, ScreenWidth() - 2, 2, olc::WHITE);
		//Draw left border
		DrawLine(2, 2, 2, ScreenHeight() - 2, olc::WHITE);
		//Draw right border
		DrawLine(ScreenWidth() - 2, 2, ScreenWidth() - 2, ScreenHeight() - 2, olc::WHITE);
		//Draw bottom border
		DrawLine(2, ScreenHeight() - 2, ScreenWidth() - 2, ScreenHeight() - 2, olc::WHITE);

		olc::vi2d SnakeHead(SnakeXPos, SnakeYPos);
		olc::vi2d SnakeHeadSize(2, 2);

		olc::vi2d Fruit(fruit1X, fruit1Y);
		olc::vu2d FruitSize(2, 2);

		//Directions changes
		userInput(speed);

		//Snake and fruit collision
		if (SnakeHead.x < Fruit.x + FruitSize.x &&
			SnakeHead.x + SnakeHeadSize.x > Fruit.x &&
			SnakeHead.y < Fruit.y + FruitSize.y &&
			SnakeHead.y + SnakeHeadSize.y > Fruit.y) {
			fruit1 = false;
			score++;
			tailLength++;
		}

		//Draw fruit
		DrawRect(fruit1X, fruit1Y, 1, 1, olc::RED);

		//Fruit coord gen
		FruitCoordGen();

		//Border collision
		BorderCollisionCheck();

		//Tail
		for (int i = 1; i <= tailLength; i++) {
			tailX[1] = OldSnakeXPos;
			tailY[1] = OldSnakeYPos;
		}

		//Draw Snake tail
		if (tailLength >= 1) {
			for (int i = 1; i <= tailLength; i++) {
				DrawRect(tailX[i], tailY[i], 1, 1, olc::GREEN);
			}
		}

		//Draw Snake
		DrawRect(SnakeXPos, SnakeYPos, 1, 1, olc::DARK_GREEN);

		return true;
	}

	bool OnUserCreate() override {
		srand(time(NULL));
		dir = STOP;
		//Snake X coord gen
		SnakeXPos = rand() & ScreenWidth();
		if (SnakeXPos <= 3 || SnakeXPos >= ScreenWidth() - 3) {
			SnakeXPos = rand() & ScreenWidth();
		}
		if (SnakeXPos <= 3 || SnakeXPos >= ScreenHeight() - 3) {
			SnakeXPos = rand() & ScreenHeight();
		}
		//Snake Y coord gen
		SnakeYPos = rand() & ScreenWidth();
		if (SnakeYPos <= 3 || SnakeYPos >= ScreenWidth() - 3) {
			SnakeYPos = rand() & ScreenWidth();
		}
		if (SnakeYPos <= 3 || SnakeYPos >= ScreenHeight() - 3) {
			SnakeYPos = rand() & ScreenHeight();
		}
		return true;
	}
};

int main() {
	Snake demo;
	if (demo.Construct(100, 100, 10, 10))
		demo.Start();
	return 0;
}