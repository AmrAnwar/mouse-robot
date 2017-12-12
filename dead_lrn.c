// ==============================================================================
//							$$ dead_lrn.c $$
//
// Date :
//	11/21/2017
// 
// Description :
//  dead and learning algorithm implementation for NxM Maze solving
//
//
// Notes:
//	- I used one number for each block to make calculations easier.
//	- The solving function is dimensions-independent.
//	- I don't use any complicated structure because we work with arduino.
//	- I use char not int, as the function only deals with small numbers.
//
// TODO:
//	** maze generator
//	*  maze illustration
//
// ==============================================================================


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define x(p) p - ((p / 8) * 8)
#define y(p) p / 8
#define DEADEND (!valid && notvalid == 3 && back == 1)

int dead_lrn(char(*)[4], char, char);
void draw_maze(char(*)[4], char, char);
void clear(char(*)[4]);

// entering the maze manually for just testing 
// one for nothing, zero for wall

static char maze[64][4] = {

	"\0\0\1\1", "\1\0\1\0", "\1\0\1\0", "\1\0\1\1", "\1\0\1\0", "\1\0\1\0", "\1\0\1\0", "\1\0\0\0",

	"\0\1\0\1", "\0\0\1\1", "\1\0\0\1", "\0\1\0\1", "\0\0\1\1", "\1\0\1\1", "\1\0\1\0", "\1\0\1\1",

	"\0\1\0\1", "\0\1\1\0", "\1\1\1\0", "\1\1\0\1", "\0\1\0\0", "\0\1\1\1", "\1\0\0\0", "\0\1\0\1",

	"\0\1\1\0", "\1\0\0\1", "\0\0\1\0", "\1\1\1\0", "\1\0\1\0", "\1\1\0\1", "\0\0\1\1", "\1\1\0\0",

	"\0\0\0\1", "\0\1\1\1", "\1\0\1\0", "\1\0\1\0", "\1\0\1\1", "\1\1\0\0", "\0\1\1\1", "\1\0\0\1",

	"\0\1\1\1", "\1\1\0\1", "\0\0\1\1", "\1\0\0\1", "\0\1\0\1", "\0\0\1\0", "\1\1\0\0", "\0\1\0\1",

	"\0\1\0\1", "\0\1\0\1", "\0\1\1\0", "\1\1\1\0", "\1\1\1\1", "\1\0\1\0", "\1\0\1\0", "\1\1\0\0",

	"\0\1\0\0", "\0\1\1\0", "\1\0\1\0", "\1\0\0\0", "\0\1\1\0", "\1\0\1\0", "\1\0\1\0", "\1\0\0\0"

};

int main()
{
	int count;

	printf("\n");
	for (count = 0; count < 10; ++count) {
		clear(maze);
		draw_maze(maze, 56, 15);
		printf("\n\n");
		dead_lrn(maze, 56, 15);
	}
	return 0;
}

void draw_maze(char(*maze)[4], char s, char e)
{
	int i, j;

	putchar('=');
	for (i = 0; i < 8; ++i) {
		for (j = 0; j < 8; ++j) {
			if (!maze[i * 8 + j][1])
				printf("======");
			else
				printf("      ");
		}
		printf("\n");
		for (j = 0; j < 8; ++j) {
			if (!maze[i * 8 + j][0])
				printf(((i * 8 + j) == e) ? "|  X  " : ((i * 8 + j) == s) ? "|  S  " : "| %02d  ", i * 8 + j);
			else
				printf(((i * 8 + j) == e) ? "   X  " : ((i * 8 + j) == s) ? "   S  " : "  %02d  ", i * 8 + j);
		}
		printf("|\n");
	}
	printf("=================================================");
}

int stpcount;

int dead_lrn(char(*maze)[4], char currpnt, char endpnt)
{
	int bckdg = -1;
	void printmove(char, char);

	stpcount = 1;
	while (currpnt != endpnt) {
		char i, j, k;						// loop counters
		char valid, notvalid, back;			// wall counters
		char dirc[4];						// to save possible directions
		char skip = 0;						// skip a loop if there is a deadend
		char rndindx, rnddir;

		// loop for fetching possible directions
		// -num indicate a back route
		for (i = 0, j = 0, notvalid = 0, valid = 0, back = 0; i < 4; ++i) {
			if (maze[currpnt][i] == 1) {
				++valid;
				*(dirc + j++) = i;
			}
			else if (maze[currpnt][i] < 0)
				++back;
			else
				++notvalid;
		}

		// loop for creating virutal wall in dead ends
		if (!valid && notvalid && back) {
			int oldpt = -100;
			int olddr;
			for (k = 0; k < 4; ++k) {
				if (maze[currpnt][k] > oldpt && maze[currpnt][k] < 0) {
					oldpt = maze[currpnt][k];
					olddr = k;
				}
			}
			// make the virtual wall for the current block
			if (DEADEND)
				maze[currpnt][olddr] = 0;

			// make the virtual wall for the contiguous block
			switch (olddr)
			{
			case 0:
				if (DEADEND)
					maze[currpnt - 1][olddr + 2] = 0;
				printmove(currpnt, currpnt - 1);
				//overirde the 1 & 0 rule, and moving the location
				--currpnt;
				break;
			case 1:
				if (DEADEND)
					maze[currpnt - 8][olddr + 2] = 0;
				printmove(currpnt, currpnt - 8);
				currpnt -= 8;
				break;
			case 2:
				if (DEADEND)
					maze[currpnt + 1][olddr - 2] = 0;
				printmove(currpnt, currpnt + 1);
				++currpnt;
				break;
			case 3:
				if (DEADEND)
					maze[currpnt + 8][olddr - 2] = 0;
				printmove(currpnt, currpnt + 8);
				currpnt += 8;
				break;
			}
			skip = 1;
		}

		// skip happen in deadend cases
		// no need to execute the second switch,
		// as the moving happened already
		if (skip) {
			skip = 0;
			++stpcount;
			continue;
		}

		// random index generator
		srand(time(NULL));
		rndindx = rand() % valid;
		rnddir = *(dirc + rndindx);

		// moving code
		switch (rnddir) {
		case 0:
			printmove(currpnt, currpnt - 1);
			maze[currpnt][rnddir] = bckdg;
			--currpnt;
			// Preventing from going back the same node
			maze[currpnt][rnddir + 2] = bckdg--;
			break;
		case 1:
			printmove(currpnt, currpnt - 8);
			maze[currpnt][rnddir] = bckdg;
			currpnt -= 8;
			maze[currpnt][rnddir + 2] = bckdg--;
			break;
		case 2:
			printmove(currpnt, currpnt + 1);
			maze[currpnt][rnddir] = bckdg;
			++currpnt;
			maze[currpnt][rnddir - 2] = bckdg--;
			break;
		case 3:
			printmove(currpnt, currpnt + 8);
			maze[currpnt][rnddir] = bckdg;
			currpnt += 8;
			maze[currpnt][rnddir - 2] = bckdg--;
			break;
		default:
			printf("fn : dead_lrn <- switch <- error : out of index\n");
			return -1;
		}
		// for step counting
		++stpcount;
	}
	printf("\n\n");
	return stpcount;
}

// printf wrapper
void printmove(char from, char to)
{
	printf("step %02d :  (%d, %d) --> (%d, %d)", stpcount, x(from), y(from), x(to), y(to));
	printf(" | %02d --> %02d\n\n", from, to);
}

//clear maze from minus numbers for next try
void clear(char(*maze)[4])
{
	int i, j;

	for (i = 0; i < 64; ++i) {
		for (j = 0; j < 4; ++j) 
			maze[i][j] = (maze[i][j] < 0) ? 1 : maze[i][j];
	}
}
