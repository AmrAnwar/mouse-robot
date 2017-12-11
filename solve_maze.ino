#define x(p) p - ((p/8) * 8)
#define y(p) p/8


#define MAXPATH 20

void slv_maze(char, char);
char flt_path(void);

static char maze[64][5] = {

	{0, 0, 1, 1, 12}, {1, 0, 1, 0, 11}, {1, 0, 1, 0, 10}, {1, 0, 1, 1, 9 },
	{1, 0, 1, 0, 10}, {1, 0, 1, 0, 11}, {1, 0, 1, 0, 12}, {1, 0, 0, 0, 13},

	{0, 1, 0, 1, 13}, {0, 0, 1, 1, 10}, {1, 0, 0, 1, 9 }, {0, 1, 0, 1, 8 },
	{0, 0, 1, 1, 3 }, {1, 0, 1, 1, 2 }, {1, 0, 1, 0, 1 }, {1, 0, 1, 1, 0} ,

	{0, 1, 0, 1, 12}, {0, 1, 1, 0, 9 }, {1, 1, 1, 0, 8 }, {1, 1, 0, 1, 7 },
	{0, 1, 0, 0, 4 }, {0, 1, 1, 1, 3 }, {1, 0, 0, 0, 4 }, {0, 1, 0, 1, 1 },

	{0, 1, 1, 0, 11}, {1, 0, 0, 1, 10}, {0, 0, 1, 0, 7 }, {1, 1, 1, 0, 6 },
	{1, 0, 1, 0, 5 }, {1, 1, 0, 1, 4 }, {0, 0, 1, 1, 3 }, {1, 1, 0, 0, 2 },

	{0, 0, 0, 1, 12}, {0, 1, 1, 1, 9 }, {1, 0, 1, 0, 8 }, {1, 0, 1, 0, 7 },
	{1, 0, 1, 1, 6 }, {1, 1, 0, 0, 5 }, {0, 1, 1, 1, 4 }, {1, 0, 0, 1, 5 },

	{0, 1, 1, 1, 11}, {1, 1, 0, 1, 10}, {0, 0, 1, 1, 11}, {1, 0, 0, 1, 10},
	{0, 1, 0, 1, 7 }, {0, 0, 1, 0, 6 }, {1, 1, 0, 0, 5 }, {0, 1, 0, 1, 6 },

	{0, 1, 0, 1, 12}, {0, 1, 0, 1, 11}, {0, 1, 1, 0, 10}, {1, 1, 1, 0, 9 },
	{1, 1, 1, 1, 8 }, {1, 0, 1, 0, 9 }, {1, 0, 1, 0, 8 }, {1, 1, 0, 0, 7 },

	{0, 1, 0, 0, 13}, {0, 1, 1, 0, 12}, {1, 0, 1, 0, 13}, {1, 0, 0, 0, 14},
	{0, 1, 1, 0, 9 }, {1, 0, 1, 0, 10}, {1, 0, 1, 0, 11}, {1, 0, 0, 0, 12}

};


static int path[MAXPATH][2];
static int sh_path[MAXPATH][2];


void setup()
{
  Serial.begin(9600);
}

void loop()
{
  
  char s, i;
  char *str;
  
  slv_maze(56, 15);
  s = flt_path();
  edit_path(s);
  for (i = 0; i < s; ++i){
    Serial.print(sh_path[i][0]);
    Serial.print(" ");
    Serial.print(sh_path[i][1]);
    Serial.println("------------------------");
  }
}


char stpcount;
char pathcount;

void slv_maze(char curr_pnt, char end_pnt)
{
	stpcount  = 1;
	pathcount = 0;

	path[pathcount][0]   = x(curr_pnt);
	path[pathcount++][1] = y(curr_pnt);

	while (curr_pnt != end_pnt) {
		char adj_pnts[4];
		char clst_dis, clst_pnt;
		char i, j;

		for (i = 0, j = 0; i < 4; ++i) {
			if (maze[curr_pnt][i] == 1) {
				switch (i) {
				case 0:
					*(adj_pnts + j++) = curr_pnt - 1;
					maze[curr_pnt-1][2] = -1;
					break;
				case 1:
					*(adj_pnts + j++) = curr_pnt - 8;
					maze[curr_pnt-8][3] = -1;
					break;
				case 2:
					*(adj_pnts + j++) = curr_pnt + 1;
					maze[curr_pnt+1][0] = -1;
					break;
				case 3:
					*(adj_pnts + j++) = curr_pnt + 8;
					maze[curr_pnt+8][1] = -1;
					break;
				}
			}
		}

		clst_dis = 20;
		for (i = 0; i < j; ++i) {
			if (maze[adj_pnts[i]][4] < clst_dis) {
				clst_dis = maze[adj_pnts[i]][4];
				clst_pnt = adj_pnts[i];
			}
		}
   
		curr_pnt = clst_pnt;
		path[pathcount][0]   = x(curr_pnt);
		path[pathcount++][1] = y(curr_pnt);
		++stpcount;
	}
}

char flt_path()
{
	char i, j, k;
	char c, r;
	
	for (i = 0, j = 0; i < pathcount; ++j) {

		sh_path[j][0] = path[i][0];
		sh_path[j][1] = path[i][1];

		k = 0;
		c = path[i][0];
		r = path[i][1];
		
		++i;

		while (path[i][0] == c && path[i + 1][0] == c)
			++i, ++k;

		while (!k && path[i][1] == r && path[i + 1][1] == r)
			++i;
	}
	return j;
}

void edit_path(char s)
{
	char i;

	for (i = 0; i < s; ++i)
		sh_path[i][1] = 7 - sh_path[i][1];
}