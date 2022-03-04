#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define ROWS 6
#define COLS 9
uint32_t m_w = 50000;
uint32_t m_z = 60000;

uint32_t get_random(){
  m_z = 36969 * (m_z & 65535) + (m_z >> 16);
  m_w = 18000 * (m_w & 65535) + (m_w >> 16);
  return (m_z << 16) + m_w; /* 32-bit result */
}

int user_input(){ // input validation.
    char u_input[256];
    int valid_input;
    do{
        printf("What column would you like to drop token into? Enter 1-7: ");
        scanf("%s",u_input);
        valid_input = u_input[0] - '0';
    }while((strlen(u_input) > 1) || (valid_input < 1) || (valid_input > 7));

    return valid_input;
}

bool check_board(char matrix[ROWS][COLS],int *row,int *col,char player_id){ //checks if enough space and updates the board.
    bool keep_going = true;
    int r = 0;
    int c = *col;

    while (r < ROWS && keep_going){
        if(matrix[r][c] == '.'){
            r += 1;
        }
        else{
            keep_going = false;
        }
    }

    if (r - 1 < 0){
        return false;
    }
    else{
        matrix[r-1][c] = player_id;
        *row = r-1;
        *col = c;
    }

    return true;
}

void print_board(char matrix[ROWS][COLS]){ // prints the board.
    printf(" ");
    for (int j = 0;j < COLS;j++){

        if (j > 0 && j < 8){
            printf(" ");
            printf("%d",j);
        }
    }
    printf("\n");
    printf("-----------------\n");
    for(int i = 0;i < ROWS;i++){
        for(int j = 0;j < COLS;j++){
            printf("%c", matrix[i][j]);
            printf(" ");

        }
        printf("\n");
    }
    printf("-----------------\n");
    printf("\n");
}

bool check_winning(char matrix[ROWS][COLS],int row, int col,char player_id){
    int old_row = row;
    int old_col = col;
    int count = 1;
    bool keep_going = true;

    void reset(){
        row = old_row;
        col = old_col;
        keep_going = true;
    }

    while ((col < COLS - 1) && keep_going){ // checking right side of the newly inserted token.
        col += 1;
        if(matrix[row][col] == player_id){
            count += 1;
            if (count == 5){
                return true;
            }

        }
        else{
            keep_going = false;
        }
    }

    reset();
    while ((col > 0) && keep_going){ // checking left side of the newly inserted token.
        col -= 1;
        if(matrix[row][col] == player_id){
            count += 1;
            if (count == 5){
                return true;
            }

        }
        else{
            keep_going = false;
        }
    }

    reset();
    count = 1;
    while((row < ROWS - 1) && keep_going){ //checking downwards of the newly inserted token.
        row += 1;
        if(matrix[row][col] == player_id){
            count += 1;
            if (count == 5){
                return true;
            }

        }
        else{
            keep_going = false;
        }
    }

    reset();
    count = 1;

    while((row < (ROWS-1) && col < (COLS-1)) && keep_going){ //Checking down and to the right.
        row += 1;
        col += 1;
        if(matrix[row][col] == player_id){
            count += 1;
            if (count == 5){
                return true;
            }

        }
        else{
            keep_going = false;
        }

    }

    reset();
    while((row > 0 && col > 0) && keep_going){ //Checking up and to the left.
        row -= 1;
        col -= 1;
        if(matrix[row][col] == player_id){
            count += 1;
            if (count == 5){
                return true;
            }

        }
        else{
            keep_going = false;
        }

    }

    reset();
    count = 1;
    while((row < (ROWS-1) && col > 0) && keep_going){ // checking down and to the left.
        row += 1;
        col -= 1;
        if(matrix[row][col] == player_id){
            count += 1;
            if (count == 5){
                return true;
            }

        }
        else{
            keep_going = false;
        }

    }

    reset();
    while((row > 0 && col < (COLS-1)) && keep_going){ // checking up and to the right.
        row -= 1;
        col += 1;
        if(matrix[row][col] == player_id){
            count += 1;
            if (count == 5){
                return true;
            }

        }
        else{
            keep_going = false;
        }

    }

    return false;

}


int main(){
    char first_move[3] = "HC";
    char matrix[ROWS][COLS];
    uint32_t n1;
    uint32_t n2;
    int col;
    int row;
    bool human_first = false;
    bool game_ended = false;
    int rand_num;
    char player_id;

    //Preparation of matrix.
    for(int i = 0;i < ROWS;i++){
        for(int j = 0;j < COLS;j++){
            if ((j == 0) || (j == 8)){
                if (i % 2 == 0){
                    matrix[i][j] = 'C';
                }else{
                    matrix[i][j] = 'H';
                }
            }
            else{
                matrix[i][j] = '.';
            }
        }
    }

    // The game begins from here.
    printf("Welcome to Connect Four, Five-in-a-Row variant!\n");
    printf("\n");
    printf("Enter two positive numbers to initialize the random number generator.\n");
    printf("Number 1: ");
    scanf("%d", &n1);
    printf("Number 2: ");
    scanf("%d", &n2);
    printf("Human player (H)\n");
    printf("Computer player (C)\n");
    m_w = n1;
    m_z = n2;
    rand_num = (get_random() % 2) + 0;
    if(first_move[rand_num] == 'H'){
        human_first = true;
    }

    if(human_first == true){
        printf("Coin toss... Human goes first.\n");
    }
    else{
        printf("Coin toss... Computer goes first.\n");
    }

    while (game_ended != true){
        if (human_first == true){
            player_id = 'H';
            col = user_input();
            //printf("valid input: %d\n",col);
            while (check_board(matrix,&row, &col, player_id) != true){ // checks if column empty, and then updates the board accordingly.
                printf("Sorry! it is already full. Enter a valid input.\n");
                printf("\n");
                col = user_input();
            }

            if(check_winning(matrix,row, col, player_id) == true){ //sending newly inserted (token's row and col) / position.
                game_ended = true;
            }

            if (game_ended != true){
                player_id = 'C';

                do{
                    col = (get_random() % 7) + 1;
                }while(check_board(matrix,&row, &col, player_id) != true);

                printf("Computer player selected column %d\n", col);

                if(check_winning(matrix,row, col, player_id) == true){
                    game_ended = true;
                }
            }

            printf("\n");
            print_board(matrix);

            if (player_id == 'H' && game_ended){
                printf("Congratulations, Human Winner!\n");
            }else if(player_id == 'C' && game_ended){
                printf("You Lose, Computer Winner!\n");
            }

        }

        else{
        
        	player_id = 'C';

                do{
                    col = (get_random() % 7) + 1;
                }while(check_board(matrix,&row, &col, player_id) != true);

                printf("Computer player selected column %d\n", col);

                if(check_winning(matrix,row, col, player_id) == true){
                    game_ended = true;
                }

		
		if (game_ended != true){
		    player_id = 'H';
            	    col = user_input();
            
            	   while (check_board(matrix,&row, &col, player_id) != true){ // checks if column empty, and then updates the board accordingly.
                	printf("Sorry! it is already full. Enter a valid input.\n");
                	printf("\n");
                	col = user_input();
		   }
		
		   if(check_winning(matrix,row, col, player_id) == true){ //sending newly inserted (token's row and col) / position.
                	game_ended = true;
            	}
	}
		
		printf("\n");
		print_board(matrix);

            	if (player_id == 'H' && game_ended){
                	printf("Congratulations, Human Winner!\n");
            	}else if(player_id == 'C' && game_ended){
                	printf("You Lose, Computer Winner!\n");
            	}
		
}
}
}
