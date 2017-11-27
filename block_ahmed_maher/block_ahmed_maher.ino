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
//	- I don't use any complicated structure because we work on a fuckin arduino.
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

#define x(p) p / 8
#define y(p) p - ((p / 8) * 8)

void dead_lrn(char(*)[4], char, char);

// entering the maze manually for just testing
// one for nothing, zero for wall

static char maze[64][4] = {

	"\0\0\0\1", "\0\0\1\1", "\1\0\1\0", "\1\0\0\1", "\0\0\1\1", "\1\0\0\1", "\0\0\1\0", "\1\0\0\1",

	"\0\1\0\1", "\0\1\0\1", "\0\0\1\1", "\1\1\0\0", "\0\1\0\1", "\0\1\1\0", "\1\0\0\0", "\0\1\0\1",

	"\0\1\1\0", "\1\1\0\0", "\0\1\0\1", "\0\1\0\0", "\0\1\0\1", "\0\0\1\1", "\1\0\0\1", "\0\1\0\1",

	"\0\0\1\1", "\1\0\1\0", "\1\1\0\1", "\0\0\1\1", "\1\1\0\0", "\0\1\0\0", "\0\1\0\1", "\0\1\0\1",

	"\0\1\0\1", "\0\0\1\1", "\1\1\0\0", "\0\1\0\1", "\0\0\1\1", "\1\0\1\0", "\1\1\0\1", "\0\1\0\1",

	"\0\1\0\1", "\0\1\0\1", "\0\0\1\1", "\1\1\0\0", "\0\1\0\1", "\0\0\1\0", "\1\1\0\1", "\0\1\0\1",

	"\0\1\0\1", "\0\1\0\0", "\0\1\0\0", "\0\0\0\1", "\0\1\1\1", "\1\0\0\1", "\0\1\0\0", "\0\1\0\1",

	"\0\1\1\0", "\1\0\1\0", "\1\0\1\0", "\1\1\1\0", "\1\1\0\1", "\0\1\1\0", "\1\0\1\0", "\1\1\0\0"

	   };

int main()
{
	printf(":: MAZE 8x8 ::\n\nStart Point (0, 2) || End Point (7, 4)\n\n");
	dead_lrn(maze, 2, 60);

	return 0;
}

int stpcount = 1;

void dead_lrn(char(*maze)[4], char currpnt, char endpnt)
{
	void printmove(char, char);

	while (currpnt != endpnt) {
		char i, j, k;						// loop counters
		char valid, notvalid, back;			// wall counters
		char dirc[4];						// to save possible directions
		char skip = 0;						//skip a loop if there is a deadend
		char rndindx, rnddir;

		// loop for fetching possible directions
		// -1 indicate a back route
		for (i = 0, j = 0, notvalid = 0, valid = 0, back = 0; i < 4; ++i) {
			if (maze[currpnt][i] == 1) {
				++valid;
				*(dirc + j++) = i;
			}
			else if (maze[currpnt][i] == -1)
				++back;
			else
				++notvalid;
		}

		// loop for creating virutal wall in dead ends
		for (k = 0; k < 4; ++k) {
			if (notvalid == 3 && back == 1 && maze[currpnt][k] == -1) {
				// make the virtual wall for the current block
				maze[currpnt][k] = 0;

				// make the virtual wall for the contiguous block
				switch (k)
				{
				case 0:
					maze[currpnt-1][k+2] = 0;
					printmove(currpnt, currpnt - 1);
					//overirde the 1 & 0 rule, and moving the location
					--currpnt;
					break;
				case 1:
					maze[currpnt-8][k+2] = 0;
					printmove(currpnt, currpnt - 8);
					currpnt -= 8;
					break;
				case 2:
					maze[currpnt+1][k-2] = 0;
					printmove(currpnt, currpnt + 1);
					++currpnt;
					break;
				case 3:
					maze[currpnt+8][k-2] = 0;
					printmove(currpnt, currpnt + 8);
					currpnt += 8;
					break;
				}
				skip = 1;
				break;
			}
		}

		// skip happen in deadend cases
		// no need to execute the second switch,
		// as the moving happened already
		if (skip) {
			++stpcount;
			skip = 0;
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
			--currpnt;
			// Preventing from going back the same node
			maze[currpnt][rnddir + 2] = -1;
			break;
		case 1:
			printmove(currpnt, currpnt - 8);
			currpnt -= 8;
			maze[currpnt][rnddir + 2] = -1;
			break;
		case 2:
			printmove(currpnt, currpnt + 1);
			++currpnt;
			maze[currpnt][rnddir - 2] = -1;
			break;
		case 3:
			printmove(currpnt, currpnt + 8);
			currpnt += 8;
			maze[currpnt][rnddir - 2] = -1;
			break;
		default:
			printf("fn : dead_lrn <- switch <- error : out of index\n");
			return;
		}
		// for step counting
		++stpcount;
	}
}

// printf wrapper
void printmove(char from, char to)
{

	serial.print("step %2d :  (%d, %d) --> (%d, %d)\n\n", stpcount, x(from), y(from), x(to), y(to));
}
