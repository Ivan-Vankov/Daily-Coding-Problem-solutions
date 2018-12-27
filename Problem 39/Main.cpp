#include <windows.h>
#include <stdio.h>

const int colls = 15;
const int rows = 50;

char table[colls][rows] = {
	"                                                 ",
	"                                                 ",
	"                                #                ",
	"                              # #                ",
	"                    ##      ##            ##     ",
	"                   #   #    ##            ##     ",
	"        ##        #     #   ##                   ",
	"        ##        #   # ##    # #                ",
	"                  #     #       #                ",
	"                   #   #                         ",
	"                    ##                           ",
	"                                                 ",
	"                                                 ",
	"                                                 ",
	"                                                 ",
/*	"                #                                ",
	"        #        ##                              ",
	"      # #       ##                               ",
	"       ##                                        ",
	"                                                 ",
	"#                                                ",
	" ##                                              ",
	"##                                               ",
	"                                                 ",
	"            ##                                   ",
	"           ##                                    ",
	"        #                                        ",
	"      # #                                        ",
	"       ##                                        ",
	"                                                 " */};

enum status{
	death,
	survival,
	birth,
	unknown
};

bool validXandY(int x, int y){
	if (x < 0 || x >= colls){
		return false;
	}
	if (y < 0 || y >= rows-1){
		return false;
	}
	return true;
}

int aliveNeighbours(const char newTable[colls][rows], int x, int y){
	int aliveCount = 0;
	for (int i = -1; i <= 1; i+=2){
		for (int j = -1; j <= 1; ++j){
			if (validXandY(x + i, y + j) && newTable[x + i][y + j] == '#'){
				++aliveCount;
			}
		}
	}
	// This way we skip i==0 && j==0
	if (validXandY(x, y - 1) && newTable[x][y - 1] == '#'){
		++aliveCount;
	}
	if (validXandY(x, y + 1) && newTable[x][y + 1] == '#'){
		++aliveCount;
	}
	return aliveCount;
}

status getStatus(const char newTable[colls][rows], int x, int y){
	if (!validXandY(x, y)){
		return unknown;
	}
	int neighbourCount = aliveNeighbours(newTable, x, y);
	// Birth: if the current cell is off and the neighbourCount is exactly 3, the current cell is switched on.
	if (newTable[x][y] == ' '){
		if (neighbourCount == 3){
			return birth;
		}
		else{
			return death;
		}
	}
	// Death: if the neighbourCount is less than 2 or greater than 3, the current cell is switched off.
	// Survival : if (a) the neighbourCount is 2 or 3 and the current cell is on, the current cell is left unchanged.
	if (newTable[x][y] == '#'){
		if (neighbourCount < 2 || neighbourCount > 3){
			return death;
		}
		else{
			return survival;
		}
	}
	return unknown;
}

void copyTable(char dest[][rows], const char src[][rows]){
	for (int i = 0; i < colls; ++i){
		for (int j = 0; j < rows; ++j){
			dest[i][j] = src[i][j];
		}
	}
}

void printTable(const char table[colls][rows]){
	for (int i = 0; i < colls; ++i){
		for (int j = 0; j < rows; ++j){
			printf("%c", table[i][j]);
		}
		printf("\n");
	}
}

void GameOfLife(){
	int i, j;
	status cellStatus = unknown;
	char tables[2][colls][rows];
	copyTable(tables[0], table);
	copyTable(tables[1], table);
	for (int currTable = 1;; (++currTable) %= 2){
		int otherTable = (currTable + 1) % 2;
		for (i = 0; i < colls-1; ++i){
			for (j = 0; j < rows; ++j){
				cellStatus = getStatus(tables[currTable], i, j);
				switch (cellStatus){
					// stay the same
				case(survival) : tables[otherTable][i][j] = '#'; break;
					// turn cell off 
					case(death) : tables[otherTable][i][j] = ' '; break;
					// turn cell on 
					case(birth) : tables[otherTable][i][j] = '#'; break;
					default: break;
				}
				//printf("%c", tables[otherTable][i][j]);
			}
			//printf("\n");
		}
		for (j = 0; j < rows; ++j){
			cellStatus = getStatus(tables[currTable], i, j);
			switch (cellStatus){
				case(survival) : tables[otherTable][i][j] = '#'; break;
				case(death) : tables[otherTable][i][j] = ' '; break;
				case(birth) : tables[otherTable][i][j] = '#'; break;
				default: break;
			}
			//printf("%c", tables[otherTable][i][j]);
		}
		printTable(tables[otherTable]);
		// Wait some time
		//Sleep(100);
		// Clear the screen
		system("cls");
	}
}

int main(){
	GameOfLife();
}