
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <Windows.h>

#include "Queue.h"

using namespace std;

// Field (Board) size
#define FIELD_SIZE		20

#define FIELD_EMPTY		-80
#define FIELD_SNAKE		-78

// Position structure for a coordinate on the game
struct Position {
	int x;		// row index
	int y;		// column index

	Position() : x(0), y(0) {}
	Position(int x, int y) : x(x), y(y) {}
};

// Snake class
class Snake {
public:
	// Contructure
	Snake();

	// recursive game loop function
	void gameLoop();

private:
	// Display game field (board)
	void display();

private:
	// Board defined 20 x 20
	char field[FIELD_SIZE][FIELD_SIZE];
	// Head of the snake position
	Position head;
	// Body queue which holds snake queue
	Queue<Position> bodyQueue;
	// Size of the snake
	int currSize;
	// Counter value
	int counter;
	// Next size value
	int nextSize;
};

// Contructor
Snake::Snake() : head(5, 5), currSize(1), counter(0)
{
	// Seed random number generator
	srand((unsigned int) time(NULL));

	// Assign a random value to nextSize a random number between 1-5
	nextSize = (rand() % 5) + 1;

	// Initialize the field: 0: empty, 1: there is snake part
	for (int i = 0; i < FIELD_SIZE; ++i) {
		for (int j = 0; j < FIELD_SIZE; ++j) {
			field[i][j] = FIELD_EMPTY;
		}
	}

	// head of the snake
	field[5][5] = FIELD_SNAKE;
}

// Recursive game loop function
void Snake::gameLoop()
{
	// Display the field
	display();

	// Get the character
	int ch = _getch();
	
	// It will hold next position of the snake head
	int nx = head.x;
	int ny = head.y;

	// Update next head position according to the input
	switch (ch) {
	case 'w':
	case 'W':
		--nx;
		break;
	case 's':
	case 'S':
		++nx;
		break;
	case 'a':
	case 'A':
		--ny;
		break;
	case 'd':
	case 'D':
		++ny;
		break;
	default:
		// Not a valid input
		gameLoop();
		return;
	}

	// Check if the position is valid (game is not over)
	if (nx < 0 || nx >= FIELD_SIZE || ny < 0 || ny >= FIELD_SIZE || field[nx][ny] == FIELD_SNAKE)
		return;

	// Add old head position to the queue
	bodyQueue.add(Position(head.x, head.y));
	
	// Check if the body queue size is bigger or equal to the snake size
	if (bodyQueue.size() >= currSize) {
		// Remove first element in the body queue
		Position pos = bodyQueue.remove();

		// Unset that position in the field (make empty)
		field[pos.x][pos.y] = FIELD_EMPTY;
	}

	// Update head position
	head.x = nx;
	head.y = ny;

	// Set new head position in the field
	field[head.x][head.y] = FIELD_SNAKE;
	// Increase counter value
	++counter;

	// Check counter value with next size value
	if (counter == nextSize) {
		// Set counter as 0
		counter = 0;
		// Increase snake size by one
		++currSize;
		// Assign a random value to nextSize a random number between 1-5
		nextSize = (rand() % 5) + 1;
	}

	// Call game loop again
	gameLoop();

	return;
}

// Display game field (board)
void Snake::display()
{
	// Clear screen
	system("cls");

	// Print field array
	for (int i = 0; i < FIELD_SIZE; ++i) {
		for (int j = 0; j < FIELD_SIZE; ++j) {
			std::cout << static_cast<char>(field[i][j]);
		}

		std::cout << std::endl;
	}
}

// Main function
int main()
{
	// Use US-ASCII coding
	SetConsoleCP(437);
	SetConsoleOutputCP(437);

	Snake snake;

	snake.gameLoop();

	std::cout << "Game Over!" << std::endl;

	return 0;
}

