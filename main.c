#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    
    srand(time(NULL));  // ensures that different random numbers are generated every time a program is run;
    setvbuf(stdout, NULL, _IONBF, 0);
    
    char map[12][30];
    int minelist[2][10];
    int i, j, count = 0, c;
    
    // stores '.' signs in an array "map":
    for (i = 0; i<12; i++) {
        for (j = 0; j<30; j++) {
            map[i][j] = '.';
        }
    }
    
    // generates coordinates of mines and stores these values to an array "minelist":
    for (c = 0; c<10; c++) {
        minelist[0][c] = (rand() % 12);
        minelist[1][c] = (rand() % 30);
    }
    
    // replaces '.' signs in array "map" by '*' signs according to the coordinates stores in "minelist":
    for (c = 0; c < 10; c++) {
        i = minelist[0][c];
        j = minelist[1][c];
        map[i][j] = '*';
    }
    
    // changes value of each cell according to the number of "*" signs in neighbouring cells:
    for (i = 0; i < 12; i++) {
        for (j = 0; j < 30; j++) {
            if (map[i][j] == '.') {
                if (!(i-1<0) && !(j-1<0)) {
                    if (map[i-1][j-1] == '*') {
                       count++;
                    }
                }
                
                if (!(i-1<0) && !(j>29)) {
                    if (map[i-1][j] == '*') {
                       count++;
                    }
                }
                
                if (!(i-1<0) && !(j+1>29)) {
                    if (map[i-1][j+1] == '*') {
                       count++;
                    }
                }
            
                if (!(i<0) && !(j-1<0)) {
                    if (map[i][j-1] == '*') {
                       count++;
                    }
                }
            
                if (!(i<0) && !(j+1>29)) {
                    if (map[i][j+1] == '*') {
                       count++;
                    }
                }
            
                if (!(i+1>11) && !(j-1<0)) {
                    if(map[i+1][j-1] == '*') {
                       count++;
                    }
                }
        
                if (!(i+1>11) && !(j>29)) {
                    if (map[i+1][j] == '*') {
                       count++;
                    }
                }
                
                if (!(i+1>11) && !(j+1>29)) {
                    if (map[i+1][j+1] == '*') {
                       count++;
                    }
                }
                
                if (count > 0) {
                    map[i][j] = count + '0';  // if at least 1 '*' sign was found, replaces the value of a cell by a count;
                    count = 0;
                } else {
                    map[i][j] = '.'; // if no such sign was found, the initial value remains;
                }
            }
        }
    }
    
    _Bool view[12][30];  // an array that stores the values of uncovered cells;
    int x, y;
    int guess_count = 0;  // is used to count the number of trials made by the user;
    
    for (i = 0; i<12; i++) {
        for (j = 0; j<30; j++) {
            view[i][j] = 0;  // in the beginning sets all values false;
        }
    }
    
    do {
        // gets corresponding coordinates from the user:
       printf("Type in a number of row: ");
       scanf("%i", &x);
       printf("Type in a number of column: ");
       scanf("%i", &y);

        // checks if given numbers are in a range, if not the program keeps asking for new numbers unless they are valid:
       if (x<=0 || x>12 || y<=0 || y>30) {
          do {
              printf("Invalid value \n");
              printf("Type in a number of row: ");
              scanf("%i", &x);
              printf("Type in a number of column: ");
              scanf("%i", &y);
          } while (!((x>0) && (x<13) && (y>0) && (y<31)));
       }
    
       i = x-1;
       j = y-1;
      
       view[i][j] = 1; // changes the value of according coordinates in an array to true;
       char ch = '?';

        if (map[i][j] == '*') {
            for (i = 0; i<12; i++) {
                for (j = 0; j<30; j++) {
                    printf("%2c", map[i][j]);
                }
                printf("\n");
            }
            printf("BOOOOM! Game is over!\n");  // if a mine was uncovered, ends the program;
            break;
        } else {
               for (i = 0; i<12; i++) {
                   for (j = 0; j<30; j++) {
                       if (view[i][j] == 1) {
                          printf("%2c", map[i][j]);
                       } else if (view[i][j] == 0) {
                          printf("%2c", ch);
                       }
                   }
                   printf("\n");
               }
            guess_count++; // if a mine was not uncovered, shows the values of "map" which are true in "view", while others are replaced by a "?" sign;
        }
    } while (guess_count < 350);
    
    if (guess_count >= 350) {
       printf("CONGRATULATIONS!\n"); // the maximum possible number of guesses is 350, so if the count exceeds, then the player must be the winner;
    }
    
    return 0;
}
