#include <iostream>
#include <string>
#include "geesespotter_lib.h"

using namespace std;

char* createBoard(std::size_t xdim, std::size_t ydim);
void hideBoard(char *board, std::size_t xdim, std::size_t ydim);
void cleanBoard(char *board);
int mark(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc,
		std::size_t yloc);
void printBoard(char *board, std::size_t xdim, std::size_t ydim);
int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc,
		std::size_t yloc);
void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim);
bool isGameWon(char *board, std::size_t xdim, std::size_t ydim);

char* createBoard(std::size_t xdim, std::size_t ydim) {
	size_t length = xdim * ydim;
	char *board { new char[length] { 0 } };
	return board;
}

void hideBoard(char *board, std::size_t xdim, std::size_t ydim) {
	size_t length = xdim * ydim;
	for (size_t i { 0 }; i < length; i++) {
		board[i] = board[i] | 0x20;
	}
}

void cleanBoard(char *board) {
	delete[] board;
	board = nullptr;
}

int mark(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc,
		std::size_t yloc) {

	size_t location = xloc + yloc * xdim;

	if ((board[location] & 0x20) == 0) {
		return 2;
	} else if ((board[location] & 0x10) == 0x10) {
		board[location] = board[location] & 0x2F;
	} else {
		board[location] = board[location] | 0x10;
	}
	return 0;
}

void printBoard(char *board, std::size_t xdim, std::size_t ydim) {
	size_t size = xdim * ydim;

	for (size_t i { 0 }; i <= size; i++) {
		if ((board[i] & 0x10) == 0x10) {
			std::cout << "M";
		} else if ((board[i] & 0x20) == 0x20) {
			std::cout << "*";
		} else {
			std::cout << int(board[i]);
		}
		if ((i + 1) % xdim == 0) {
			std::cout << std::endl;
		}
	}

}

void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim) {
	for (std::size_t y{ 0 }; y < ydim; y++) {
		for (std::size_t x { 0 }; x < xdim; x++) {
			if ((board[xdim * y + x] & 0x0f )== 0x09) {
				if (((int) x - 1) >= 0 && ((int) y - 1) >= 0) {
					board[xdim * (y - 1) + (x - 1)] += 1;
				}
				if (((int) y - 1) >= 0) {
					board[xdim * (y - 1) + x] += 1;
				}
				if ((x + 1) < xdim && ((int) y - 1) >= 0) {
					board[xdim * (y - 1) + (x + 1)] += 1;
				}
				if (((int) x - 1) >= 0) {
					board[xdim * (y) + (x - 1)] += 1;
				}

				if ((x + 1) < xdim) {
					board[xdim * (y) + (x + 1)] += 1;
				}

				if (((int) x - 1) >= 0 && (y + 1) < ydim) {
					board[xdim * (y + 1) + (x - 1)] += 1;
				}
				if ((y + 1) < ydim) {
					board[xdim * (y + 1) + (x)] += 1;
				}
				if ((x + 1) < xdim && (y + 1) < ydim) {
					board[xdim * (y + 1) + (x + 1)] += 1;
				}

			}
		}
	}

}

int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc,
		std::size_t yloc) {
	//marked
	if ((board[xdim * yloc + xloc] & 0x10) == 0x10) {
		return 1;
		//hidden & unmarked
	} else if ((board[xdim * yloc + xloc] & 0x20) == 0x20) {
		board[xdim * yloc + xloc] = board[xdim * yloc + xloc] & 0x0f;
		if (board[xdim * yloc + xloc] == 0x09) {
			return 9;
		} else {
			if (board[xdim * yloc + xloc] == 0) {
				if (((int) xloc - 1) >= 0 && ((int) yloc - 1) >= 0
						&& ((board[xdim * (yloc - 1) + (xloc - 1)] & 0x30) == 0x20)) {
					board[xdim * (yloc - 1) + (xloc - 1)] = board[xdim
							* (yloc - 1) + (xloc - 1)] & 0x0f;
				}
				if (((int) yloc - 1) >= 0
						&& ((board[xdim * (yloc - 1) + xloc] & 0x30) == 0x20)) {
					board[xdim * (yloc - 1) + xloc] = board[xdim * (yloc - 1)
							+ xloc] & 0x0f;
				}
				if ((xloc + 1) < xdim && ((int) yloc - 1) >= 0
						&& ((board[xdim * (yloc - 1) + (xloc + 1)] & 0x30) == 0x20)) {
					board[xdim * (yloc - 1) + (xloc + 1)] = board[xdim
							* (yloc - 1) + (xloc + 1)] & 0x0f;
				}
				if (((int) xloc - 1) >= 0
						&& ((board[xdim * (yloc) + (xloc - 1)] & 0x30) == 0x20)) {
					board[xdim * (yloc) + (xloc - 1)] = board[xdim * (yloc)
							+ (xloc - 1)] & 0x0f;
				}

				if ((xloc + 1) < xdim
						&& ((board[xdim * (yloc) + (xloc + 1)] & 0x30) == 0x20)) {
					board[xdim * (yloc) + (xloc + 1)] = board[xdim * (yloc)
							+ (xloc + 1)] & 0x0f;
				}

				if (((int) xloc - 1) >= 0 && (yloc + 1) < ydim
						&& ((board[xdim * (yloc + 1) + (xloc - 1)] & 0x30) == 0x20)) {
					board[xdim * (yloc + 1) + (xloc - 1)] = board[xdim
							* (yloc + 1) + (xloc - 1)] & 0x0f;
				}
				if ((yloc + 1) < ydim
						&& ((board[xdim * (yloc + 1) + (xloc)] & 0x30) == 0x20)) {
					board[xdim * (yloc + 1) + (xloc)] = board[xdim * (yloc + 1)
							+ (xloc)] & 0x0f;
				}
				if ((xloc + 1) < xdim && (yloc + 1) < ydim
						&& ((board[xdim * (yloc + 1) + (xloc + 1)] & 0x30) == 0x20)) {
					board[xdim * (yloc + 1) + (xloc + 1)] = board[xdim
							* (yloc + 1) + (xloc + 1)] & 0x0f;
				}

			}
			return 0;
		}

		//revealed
	} else {
		return 2;
	}

}


bool isGameWon(char *board, std::size_t xdim, std::size_t ydim){
	for(std::size_t i {0}; i < xdim * ydim; i++ ){
		if(((board[i] & 0x20) == 0x20) && (board[i] & 0x0f )!= 0x09){
			return false;
		}
		if(((board[i] & 0x0f) == 0x09) && ((board[i] & 0x20) != 0x20))	{
			return false;
		}
	}
	return true;
}

















