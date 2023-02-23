#include <iostream>
#include <array>
#include <vector>
#include <math.h>


/*

    Firstly thanks for viewing my code. I hope I could've explained the code clearly enough and it all makes sense for you.

    The comments in this file will only explain steps of the algorithm and usage of methods. 
    In order to understand the base algorithm, read the explanation from the github page of this code.

    Github username: kerem-kirici
    for any advice to improve the algorithm please email me: kerem.kirici36@gmail.com
    
    ITU <3
*/


// Number of blocks on a side of the square board of the game.
const int SIZE = 4;

// A constant which will be used as highest number (infinity) for doubles
const double DOUBLE_MAX = std::numeric_limits<double>::max();

// classes will be used
class Game;
class Player;

/*

        There are some similar functions in these classes. 
        The explanation of those functions will only appear in Game class.

*/


// This class has methods to run the game properly which can be played either by a user(via console inputs) or a Player class bot.
class Game {
private:

    // main board of the game
    int board[SIZE][SIZE];
    // secondary board of the game. This board will only be used as a copy for the main board in order to paste it later in some situations.
    int con_board[SIZE][SIZE];
    // main board of the game
    int score = 0;
    // secondary board of the game. This board will only be used as a copy for the main board in order to paste it later in some situations.
    int con_score = 0;

    // a boolean which indicates if the game will end if the player reaches target number (which is usually 2048)
    bool target_number_active;
    // a boolean indicating whether the console is showing the current state of the game during playtime or not.
    bool log_data;


    // the following sliding functions have one base method. 
    //  * (1) first for each column/row start checking the blocks from the ending side of the swipe.
    //  * (2) if the block contains a non 0 value, then:
    //      * (3) start checking from that block to the starting side of the swipe with another loop 
    //      * (4) check if there is the same valued block in the column until there is a non-empty block with another value, in that case break the loop.
    //      * (5) if there is a same value block then delete that block's value and multiply the starting block with 2, then break the loop.
    //  * (6) lastly slide all the non empty blocks in the direction of swipe to fill empty blocks with valued blocks (to have no gaps between valued blocks).

    bool slide_up(){
        // pasting the main board to the secondary board in order to check if it has changed at the end of this function. 
        paste_board_to(&con_board[0][0], &con_score);

        // starting a loop for columns
        for (int col = 0; col < SIZE; col++){
            // (1)
            for (int row = 0; row < SIZE; row++){
                int cell = board[row][col];
                // (2)
                if (cell != 0)
                    // (3)
                    for (int srow = row+1; srow < SIZE; srow++){
                        // (5)
                        if (board[srow][col] == cell){
                            board[row][col] *= 2;
                            board[srow][col] = 0;
                            score += cell*2;
                            break;
                        }
                        else if (board[srow][col] != 0) break;   // (4) (breaks the loop if there is a different valued block.)
                    }                 
                
            }
            // (6)
            for (int row = 0; row < SIZE; row++)
                if (board[row][col] == 0){
                    for (int srow = row+1; srow < SIZE; srow++){
                        int scell = board[srow][col];
                        if (scell != 0){
                            board[row][col] = scell;
                            board[srow][col] = 0;
                            break;
                        }
                    }                   
                }   
        }

        // check if the board has changed. return true if it has changed otherwise return false.
        return !boards_same();
    }

    // to understand the function, read slide_up() function's explanation 
    bool slide_down(){
        paste_board_to(&con_board[0][0], &con_score);

        for (int col = 0; col < SIZE; col++){
            for (int row = SIZE-1; row >= 0; row--){
                int cell = board[row][col];
                if (cell != 0)
                    for (int srow = row-1; srow >= 0; srow--){
                        if (board[srow][col] == cell){
                            board[row][col] *= 2;
                            board[srow][col] = 0;
                            score += cell*2;
                            break;
                        }
                        else if (board[srow][col] != 0) break;   
                    }                 
                
            }
            for (int row = SIZE-1; row >= 0; row--)
                if (board[row][col] == 0){
                    for (int srow = row-1; srow >= 0; srow--){
                        int scell = board[srow][col];
                        if (scell != 0){
                            board[row][col] = scell;
                            board[srow][col] = 0;
                            break;
                        }
                    }                   
                }   
        }

        return !boards_same();
    }

    // to understand the function, read slide_up() function's explanation 
    bool slide_left(){
        paste_board_to(&con_board[0][0], &con_score);

        for (int row = 0; row < SIZE; row++){
            for (int col = 0; col < SIZE; col++){
                int cell = board[row][col];
                if (cell != 0)
                    for (int scol = col+1; scol < SIZE; scol++){
                        if (board[row][scol] == cell){
                            board[row][col] *= 2;
                            board[row][scol] = 0;
                            score += cell*2;
                            break;
                        }
                        else if (board[row][scol] != 0) break;   
                    }                 
                
            }
            for (int col = 0; col < SIZE; col++)
                if (board[row][col] == 0){
                    for (int scol = col+1; scol < SIZE; scol++){
                        int scell = board[row][scol];
                        if (scell != 0){
                            board[row][col] = scell;
                            board[row][scol] = 0;
                            break;
                        }
                    }                   
                }   
        }

        return !boards_same();
    }

    // to understand the function, read slide_up() function's explanation 
    bool slide_right(){
        paste_board_to(&con_board[0][0], &con_score);

        for (int row = 0; row < SIZE; row++){
            for (int col = SIZE-1; col >= 0; col--){
                int cell = board[row][col];
                if (cell != 0)
                    for (int scol = col-1; scol >= 0; scol--){
                        if (board[row][scol] == cell){
                            board[row][col] *= 2;
                            board[row][scol] = 0;
                            score += cell*2;
                            break;
                        }
                        else if (board[row][scol] != 0) break;   
                    }                 
                
            }
            for (int col = SIZE-1; col >= 0; col--)
                if (board[row][col] == 0){
                    for (int scol = col-1; scol >= 0; scol--){
                        int scell = board[row][scol];
                        if (scell != 0){
                            board[row][col] = scell;
                            board[row][scol] = 0;
                            break;
                        }
                    }                   
                }   
        }

        return !boards_same();
    }

    // pastes main board into the given board type and score
    void paste_board_to(int *board_ptr, int *score_ptr){
        std::copy(&board[0][0], &board[0][0]+SIZE*SIZE, board_ptr);
        *score_ptr = score;
    }

    // copies main board from the given board type and score
    void copy_board_from(int *board_ptr, int *score_ptr){
        std::copy(board_ptr, board_ptr+SIZE*SIZE, &board[0][0]);
        score = *score_ptr;
    }

    // checks whether the game is finished or not.
    bool finished(){
        // copying board in order to check later if it has changed.
        paste_board_to(&con_board[0][0], &con_score);

        // if the target number has been activated then check if it has been reached.
        if (target_number_active){
            for (int i = 0; i < SIZE; i++)
                for (int j = 0; j < SIZE; j++)
                    if (board[i][j] == Game::FINISHING_NUMBER) return true;
        }

        // following section has similarities. all of 4 checks has same base idea which is:
        //  * try to slide in all directions, if board has changed, then game is not finished so paste original board back and return false
        if (slide_up()){
            copy_board_from(&con_board[0][0], &con_score);
            return false;
        }

        if (slide_down()){
            copy_board_from(&con_board[0][0], &con_score);
            return false;
        }

        if (slide_left()){
            copy_board_from(&con_board[0][0], &con_score);
            return false;
        }

        if (slide_right()){
            copy_board_from(&con_board[0][0], &con_score);
            return false;
        }

        // if the target score is not reached and no possible move can change the board, then the game is finished.
        return true;
    }

    // this method finds all empty blocks and randomly selects one. then with a chance of 90% fills that block with 2 otherwise with 4.
    void seed_board(){
        // get a floating number between 0 and 1.
        float possible4 = (float) rand() / RAND_MAX;

        // vector storing all empty positions in the board.
        std::vector<std::array<int, 2>> positions;
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                if (board[i][j] == 0) // checking empty positions
                    positions.push_back({i, j});
        
        int position_index = rand() % positions.size(); // randomly selecting one empty position from the vector.

        std::array<int, 2> position= positions[position_index];

        // filling the empty block with 2 (90%) or 4 (10%), deciding the probability with the random floating number being lower or higher than 0.1.
        board[position[0]][position[1]] = ( possible4 > 0.1 ) ? 2 : 4;

    }

    // checks if the main board and secondary board are the same.
    bool boards_same(){
        //gets starting value's pointer of the boards and compares 1 by 1 through the board by increasing pointer method
        int *ptr1 = &board[0][0];
        int *ptr2 = &con_board[0][0];
        for (int i = 0; i < SIZE*SIZE; i++)
            if (*(ptr1+i) != *(ptr2+i))
                return false;
        return true;
    }

    // in case of a user played game, this method receives user input and returns it as char data.
    char user_input(){
        char move;
        std::cout << "Move (u d r l q): ";
        std::cin >> move;

        return move;
    }

    // this method receives a move as a parameter and plays that move.
    void step(char move){
        
        switch (move)
        {
        case 'u':
            if (slide_up())
                seed_board();
            break;
            
        case 'd':
            if (slide_down())
                seed_board();
            break;

        case 'l':
            if (slide_left())
                seed_board();
            break;
            
        case 'r':
            if (slide_right())
                seed_board();
            break;
        
        default:
            // in case of invalid input
            display_board();
            std::cout << "Invalid Input" << std::endl;
        }

    }


public:

    // a shared board and score which is a copy of the main board/score but by using this shared board, it is impossible for the player to affect the main board.
    int shared_board[SIZE][SIZE];
    int shared_score = 0;

    // Target Number
    static const int FINISHING_NUMBER = 2048;

    // while printing the board, just to prettify things, using this maximum padding length for numbers.
    const int PADDING_LENGTH = log10(FINISHING_NUMBER)+2;

    // constructor which will receive 2 booleans: target number activated and logging playing data such as current board, best move, chance of death...
    Game(bool target_number_actv=true, bool log_playing_data=true) {
        // seed random source for full randomness.
        srand(rand()+time(0));
        target_number_active = target_number_actv;
        log_data = log_playing_data;

        // creating total empty board
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                board[i][j] = 0;

        // seeding board twice to start the game.
        seed_board();
        seed_board();

        // pasting the original board to the shared one.
        paste_board_to(&shared_board[0][0], &shared_score);
    }
    
    // function for displaying the board and score pretty.
    void display_board(){
        std::cout << std::endl << "Score: " << score << std::endl;

        for (int i = 0; i < SIZE; i++){
            for (int j = 0; j < SIZE; j++){
                std::cout << board[i][j];
                for (int k = 0; k < PADDING_LENGTH-(int)log10(board[i][j]+1); k++) 
                    std::cout << " "; 
            }
            std::cout << std::endl;
        }
    }

    // main play function which initiates every other step.
    // receives 2 optional parameters, if there is no parameter passed, then it means the user will play.
    // otherwise if a pointer to a Player class object and a pointer to a get_move function of Player class passed, then Player class bot should play the game.
    void play(Player *player_ptr = nullptr, char (Player::*get_move)(bool) = nullptr){
        
        // while loop that will run until game is finished
        while (!finished()){
            char move;
            if (log_data) display_board();
            paste_board_to(&shared_board[0][0], &shared_score);

            // if it is played by user:
            if (player_ptr == nullptr){
                move = user_input();
                if (move == 'q') break;
            }
            // if it is played by bot
            else move = (player_ptr->*get_move)(log_data);
            
            // perform the move
            step(move);
        }
        
        if (log_data) display_board();
        if (log_data) std::cout << "End!" << std::endl;
    }

};

// This class has methods to play the game in the most proper way according to the algorithm.
class Player {
private:
    // main calculation board
    int board[SIZE][SIZE];
    // secondary copying board
    int con_board[SIZE][SIZE];
    // board will store the original board from Game class
    int parent_board[SIZE][SIZE];
    // main calculation score
    int score = 0;
    // secondary copying score
    int con_score = 0;
    // score will store the original score from Game class
    int parent_score = 0;

    // Maximum depth of steps the calculation functions will go through.
    int COMPUTE_DEPTH = 4;

    // pointer to the main game object 
    Game *game;


    // check for explanations in Game class slide functions.
    bool slide_up(){
        paste_board_to(&con_board[0][0], &con_score);

        for (int col = 0; col < SIZE; col++){
            for (int row = 0; row < SIZE; row++){
                int cell = board[row][col];
                if (cell != 0)
                    for (int srow = row+1; srow < SIZE; srow++){
                        if (board[srow][col] == cell){
                            board[row][col] *= 2;
                            board[srow][col] = 0;
                            score += cell*2;
                            break;
                        }
                        else if (board[srow][col] != 0) break;   
                    }                 
                
            }
            for (int row = 0; row < SIZE; row++)
                if (board[row][col] == 0){
                    for (int srow = row+1; srow < SIZE; srow++){
                        int scell = board[srow][col];
                        if (scell != 0){
                            board[row][col] = scell;
                            board[srow][col] = 0;
                            break;
                        }
                    }                   
                }   
        }

        return !boards_same();
    }

    bool slide_down(){
        paste_board_to(&con_board[0][0], &con_score);

        for (int col = 0; col < SIZE; col++){
            for (int row = SIZE-1; row >= 0; row--){
                int cell = board[row][col];
                if (cell != 0)
                    for (int srow = row-1; srow >= 0; srow--){
                        if (board[srow][col] == cell){
                            board[row][col] *= 2;
                            board[srow][col] = 0;
                            score += cell*2;
                            break;
                        }
                        else if (board[srow][col] != 0) break;   
                    }                 
                
            }
            for (int row = SIZE-1; row >= 0; row--)
                if (board[row][col] == 0){
                    for (int srow = row-1; srow >= 0; srow--){
                        int scell = board[srow][col];
                        if (scell != 0){
                            board[row][col] = scell;
                            board[srow][col] = 0;
                            break;
                        }
                    }                   
                }   
        }

        return !boards_same();
    }

    bool slide_left(){
        paste_board_to(&con_board[0][0], &con_score);

        for (int row = 0; row < SIZE; row++){
            for (int col = 0; col < SIZE; col++){
                int cell = board[row][col];
                if (cell != 0)
                    for (int scol = col+1; scol < SIZE; scol++){
                        if (board[row][scol] == cell){
                            board[row][col] *= 2;
                            board[row][scol] = 0;
                            score += cell*2;
                            break;
                        }
                        else if (board[row][scol] != 0) break;   
                    }                 
                
            }
            for (int col = 0; col < SIZE; col++)
                if (board[row][col] == 0){
                    for (int scol = col+1; scol < SIZE; scol++){
                        int scell = board[row][scol];
                        if (scell != 0){
                            board[row][col] = scell;
                            board[row][scol] = 0;
                            break;
                        }
                    }                   
                }   
        }

        return !boards_same();
    }

    bool slide_right(){
        paste_board_to(&con_board[0][0], &con_score);

        for (int row = 0; row < SIZE; row++){
            for (int col = SIZE-1; col >= 0; col--){
                int cell = board[row][col];
                if (cell != 0)
                    for (int scol = col-1; scol >= 0; scol--){
                        if (board[row][scol] == cell){
                            board[row][col] *= 2;
                            board[row][scol] = 0;
                            score += cell*2;
                            break;
                        }
                        else if (board[row][scol] != 0) break;   
                    }                 
                
            }
            for (int col = SIZE-1; col >= 0; col--)
                if (board[row][col] == 0){
                    for (int scol = col-1; scol >= 0; scol--){
                        int scell = board[row][scol];
                        if (scell != 0){
                            board[row][col] = scell;
                            board[row][scol] = 0;
                            break;
                        }
                    }                   
                }   
        }

        return !boards_same();
    }

    // check for explanations in Game class board copy/paste functions.
    void paste_board_to(int *board_ptr, int *score_ptr){
        std::copy(&board[0][0], &board[0][0]+SIZE*SIZE, board_ptr);
        *score_ptr = score;
    }

    void copy_board_from(int *board_ptr, int *score_ptr){
        std::copy(board_ptr, board_ptr+SIZE*SIZE, &board[0][0]);
        score = *score_ptr;
    }

    // copies parent board from the given board type and score
    void copy_parent_board_from(int *board_ptr, int *score_ptr){
        std::copy(board_ptr, board_ptr+SIZE*SIZE, &parent_board[0][0]);
        parent_score = *score_ptr;
    }

    // check for explanations in the Game class finished function. (only difference: this has no target value check)
    bool finished(){
        paste_board_to(&con_board[0][0], &con_score);

        // this finished function doesn't have a target value in order to have no limit thus it can reach higher numbers than target value.

        if (slide_up()){
            copy_board_from(&con_board[0][0], &con_score);
            return false;
        }

        if (slide_down()){
            copy_board_from(&con_board[0][0], &con_score);
            return false;
        }

        if (slide_left()){
            copy_board_from(&con_board[0][0], &con_score);
            return false;
        }

        if (slide_right()){
            copy_board_from(&con_board[0][0], &con_score);
            return false;
        }

        return true;
    }

    // check for explanations in Game class boards_same() function.
    bool boards_same(){
        int *ptr1 = &board[0][0];
        int *ptr2 = &con_board[0][0];
        for (int i = 0; i < SIZE*SIZE; i++)
            if (*(ptr1+i) != *(ptr2+i))
                return false;
        return true;
    }

    // returns number of blank blocks in the board
    int empty_cells_num(){
        int s = 0;
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                s += (board[i][j] == 0);
        return s;
    }


    // this function, one of the two key functions of deep calculation, does 1 thing: 
    //  * (1) It fills every empty block one by one with twos and fours then initiates the next level of computing (search_move).
    //        By this way further steps are calculated until depth reaches maximum depth or game finishes.
    //  * (2) While filling empty blocks with start values, the function updates this position's chance of occurrence for further levels.
    void search_fill(double *parent_point_of_gain, double *parent_chance_of_death, int parent_empty_cells,
                     int parent_score, int depth=0, double chance_of_occur=1){

        // will be used to calculate chance of occur
        int n_empty_cells = empty_cells_num();

        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++){
                // if the block is empty it fills
                if (board[i][j] == 0){      // (1)
                    board[i][j] = 2;

                    // further steps of calculation start with the last step's chance of death and point of gain as parent values and 
                    //   updated chance of occurrence.
                    // chance of occur is updated with multiplier of 0.9 or 0.1 (filling with either 2 or 4)  
                    //                                 and chance of that block has been picked which is 1/(number of empty cells)

                    search_move(parent_point_of_gain, parent_chance_of_death, parent_empty_cells-1, parent_score, depth,
                                chance_of_occur*0.9*1/n_empty_cells);    // (2)
                    
                    board[i][j] = 4;
                    search_move(parent_point_of_gain, parent_chance_of_death, parent_empty_cells-1, parent_score, depth,
                                chance_of_occur*0.1*1/n_empty_cells);    // (2)
                    
                    // lastly clears that cell
                    board[i][j] = 0;
                }
            }
    }
    
    // this function, one of the two key functions of deep calculation, does 2 main things: 
    //  * (1_1) Checks if the current board is finished.
    //  * (1_2) If it has finished, then it updates the parent chance of death by adding the chance of this position's occurrence.
    //  * (2_1) Checks if the current depth of the calculation has reached maximum depth.
    //  * (2_2) If it has reached, then the function calculates the current point of gain and adds it up to the parent decider level's point of gain.
    //  * (3) If it hasn't finished, first copy the current position of board, then for every each of 4 swipe option do:
    //      * (5) If it is possible to slide, slide
    //      * (6) Initiate next level of computing by search_fill method end updates this levels chance of death and point of gain
    //      * (7) Update the current minimum chance of death if this slide's chance of death is less.
    //      * (8) In case of these chances of deaths being equal, update the current maximum point of gain if this slide's point is higher.
    //      * (9) Lastly reset all chance of death and point of gain data for other slide options and reset the board to the position in this method's start
    //  * (4) At the end as the minimum possible chance of death and maximum point of gain which can be decided,
    //        add current values of this chance and point to the parent values

    void search_move(double *parent_point_of_gain, double *parent_chance_of_death, int parent_empty_cells, int parent_score,
                     int depth, double chance_of_occur){
        
        // first increase the depth of calculation. 
        depth += 1;

        // (1_1)
        if (finished()){
            *parent_chance_of_death += chance_of_occur; // (1_2)
            return;
        }
        
        if (depth == COMPUTE_DEPTH){    // (2_1)
            // incresement of number of empty cells motivates the code to select that option so in case of a increasement the change in number is a 
            //   multiplier of the gain point, in other cases the multplier is 1, so there is no lose of any points.
            int cell_change = empty_cells_num() - parent_empty_cells;
            int cell_chng_point = ( cell_change > 0 ? cell_change : 1 );
            
            // adjacent point motivates the code to choose the option with similar numbers like 2048 and 1024 rather than different numbers like 2048 and 2.
            // it sums up the 1/(ratio to the adjacent cell), unless it's a 0, and the logarithm of the result in base 2 is a multiplier of gain point.
            double adjacent_point = 0;
            for (int i = 0; i < SIZE; i++)
                for (int j = 0; j < SIZE; j++)
                    for (int k = -1; k <= 1; k++)
                        for (int t = -1; t <= 1; t++)
                            if ( k*t == 0 && k+t != 0 && 0 <= i+k && i+k < SIZE && 0 <= j+t && j+t < SIZE){
                                int cell1 = board[i][j];
                                int cell2 = board[i+k][j+t];
                                if (cell1 != 0 && cell2 != 0){
                                    if (cell1 < cell2) adjacent_point += (double)cell1/cell2;
                                    else adjacent_point += (double)cell2/cell1;
                                }
                            }
                        
            // (2_2)
            // logarithm of difference in scores in base 2 is another multiplier of gain point.
            *parent_point_of_gain += cell_chng_point*log2(score-parent_score+1)*log2(adjacent_point+1)*chance_of_occur;
            return;
        }
        
        // define current board and score to copy this method's starting position.
        int cur_board[SIZE][SIZE];
        int cur_score;

        paste_board_to(&cur_board[0][0], &cur_score);

        // declare this method's current and further levels' parent chance of death and point of gain values.
        double point_of_gain = 0, chance_of_death = 0;
        double *point_of_gain_ptr = &point_of_gain, *chance_of_death_ptr = &chance_of_death;
        double cur_point_of_gain = 0, cur_chance_of_death = DOUBLE_MAX;

        // sliding actions have the same base idea which will be explained only in the slide_up() method.
        if (slide_up()){    // (5)
            // (6)
            search_fill(point_of_gain_ptr, chance_of_death_ptr, parent_empty_cells, parent_score, depth, chance_of_occur);
            
            // (7)
            if (chance_of_death < cur_chance_of_death){
                cur_chance_of_death = chance_of_death;
                cur_point_of_gain = point_of_gain;
            }
            
            // (8)
            else if(chance_of_death == cur_chance_of_death && point_of_gain > cur_point_of_gain)
                cur_point_of_gain = point_of_gain;
            
            // (9)
            copy_board_from(&cur_board[0][0], &cur_score);

            point_of_gain = 0;
            chance_of_death = 0;
        }
        
        // to understand this part please read slide_up part of this sliding actions
        if (slide_down()){
            search_fill(point_of_gain_ptr, chance_of_death_ptr, parent_empty_cells, parent_score, depth, chance_of_occur);

            if (chance_of_death < cur_chance_of_death){
                cur_chance_of_death = chance_of_death;
                cur_point_of_gain = point_of_gain;
            }
            
            else if(chance_of_death == cur_chance_of_death && point_of_gain > cur_point_of_gain)
                cur_point_of_gain = point_of_gain;

            copy_board_from(&cur_board[0][0], &cur_score);

            point_of_gain = 0;
            chance_of_death = 0;
        }
        
        // to understand this part please read slide_up part of this sliding actions
        if (slide_right()){
            search_fill(point_of_gain_ptr, chance_of_death_ptr, parent_empty_cells, parent_score, depth, chance_of_occur);

            if (chance_of_death < cur_chance_of_death){
                cur_chance_of_death = chance_of_death;
                cur_point_of_gain = point_of_gain;
            }
            
            else if(chance_of_death == cur_chance_of_death && point_of_gain > cur_point_of_gain)
                cur_point_of_gain = point_of_gain;            

            copy_board_from(&cur_board[0][0], &cur_score);

            point_of_gain = 0;
            chance_of_death = 0;
        }
        
        // to understand this part please read slide_up part of this sliding actions
        if (slide_left()){
            search_fill(point_of_gain_ptr, chance_of_death_ptr, parent_empty_cells, parent_score, depth, chance_of_occur);

            if (chance_of_death < cur_chance_of_death){
                cur_chance_of_death = chance_of_death;
                cur_point_of_gain = point_of_gain;
            }
            
            else if(chance_of_death == cur_chance_of_death && point_of_gain > cur_point_of_gain)
                cur_point_of_gain = point_of_gain;

            copy_board_from(&cur_board[0][0], &cur_score);
        }

        // (4)
        *parent_chance_of_death += cur_chance_of_death;
        *parent_point_of_gain += cur_point_of_gain;        
    }

public:
    const int PADDING_LENGTH = log10(Game::FINISHING_NUMBER)+1;

    // constructor method which declares a game object to the game pointer data of class.
    Player(Game *game_ptr){
        game = game_ptr;
    }
    
    // function that starts the whole finding best move process and returns the best possible move.
    char best_move(bool log_data){
        //firstly get the current situation from the Game class shared board to the parent board and then the main board
        copy_parent_board_from(&(*game).shared_board[0][0], &(*game).shared_score);
        copy_board_from(&parent_board[0][0], &parent_score);
        
        // create decider point_of_gain and chance_of_death for lower steps/levels of calculation
        double point_of_gain = 0, chance_of_death = 0;
        double *point_of_gain_ptr = &point_of_gain, *chance_of_death_ptr = &chance_of_death;        
        // create current point_of_gain and current chance_of_death variables for tracking the lowest chance_of_death and highest point_of_gain possible
        double cur_point_of_gain = 0, cur_chance_of_death = DOUBLE_MAX;
        // best move variable that will be returned at the end of this function
        char best_move;

        // declaring starting values of number of empty cells and score to calculate point_of_gain in the lowest level of calculation.
        int cur_empty_cells = empty_cells_num();
        int cur_score = score;

        // following sliding actions all have same base method which is: 
        //  * (1) if it is possible to slide, slide
        //  * (2) start computing next levels of calculation by starting serach_fill method which will end with 
        //        updated values of this level's chance of death and point of gain.
        //  * (3) in case of chance_of_death being the lowest ever seen during this searching best move process update it and point of gain.
        //  * (4) if it is equal to the lowest ever seen chance of death then if this move has more points of gain, update it with the higher one.
        //  * (5) lastly reset all chance of death and point of gain data for other slide options and reset the board to the parent board.

        if (slide_up()){    // (1)
            // (2)
            search_fill(point_of_gain_ptr, chance_of_death_ptr, cur_empty_cells, cur_score);
            // (3)
            if (chance_of_death < cur_chance_of_death) {
                cur_chance_of_death = chance_of_death;
                cur_point_of_gain = point_of_gain;
                best_move = 'u';
            }
            // (4)
            else if(chance_of_death == cur_chance_of_death && point_of_gain > cur_point_of_gain){
                cur_point_of_gain = point_of_gain;
                best_move = 'u';
            }
            // (5)
            copy_board_from(&parent_board[0][0], &parent_score);
                
            point_of_gain = 0;
            chance_of_death = 0;
        }

        // to understand this part please read slide_up part of this sliding actions
        if (slide_down()){
            search_fill(point_of_gain_ptr, chance_of_death_ptr, cur_empty_cells, cur_score);
            if (chance_of_death < cur_chance_of_death) {
                cur_chance_of_death = chance_of_death;
                cur_point_of_gain = point_of_gain;
                best_move = 'd';
            }
            else if(chance_of_death == cur_chance_of_death && point_of_gain > cur_point_of_gain){
                cur_point_of_gain = point_of_gain;
                best_move = 'd';
            }
            copy_board_from(&parent_board[0][0], &parent_score);

            point_of_gain = 0;
            chance_of_death = 0;
        }
        
        // to understand this part please read slide_up part of this sliding actions
        if (slide_right()){
            search_fill(point_of_gain_ptr, chance_of_death_ptr, cur_empty_cells, cur_score);
            if (chance_of_death < cur_chance_of_death) {
                cur_chance_of_death = chance_of_death;
                cur_point_of_gain = point_of_gain;
                best_move = 'r';
            }
            else if(chance_of_death == cur_chance_of_death && point_of_gain > cur_point_of_gain){
                cur_point_of_gain = point_of_gain;
                best_move = 'r';
            }
            copy_board_from(&parent_board[0][0], &parent_score);
            
            point_of_gain = 0;
            chance_of_death = 0;
        }

        // to understand this part please read slide_up part of this sliding actions
        if (slide_left()){
            search_fill(point_of_gain_ptr, chance_of_death_ptr, cur_empty_cells, cur_score);
            if (chance_of_death < cur_chance_of_death) {
                cur_chance_of_death = chance_of_death;
                cur_point_of_gain = point_of_gain;
                best_move = 'l';
            }
            else if(chance_of_death == cur_chance_of_death && point_of_gain > cur_point_of_gain){
                cur_point_of_gain = point_of_gain;
                best_move = 'l';
            }
            copy_board_from(&parent_board[0][0], &parent_score);
        }

        // prints out best move, chance of death and point of gain if logging data is on.
        if (log_data) std::cout << "Best Move: " << best_move << " chance of death: " << cur_chance_of_death << " point of gain: " << cur_point_of_gain << std::endl;
        
        // returns best move
        return best_move;
    }

};

void user_play(bool target_number_actv=true, bool log_data=true){

    Game game(target_number_actv, log_data);
    game.play();

}

void auto_play(bool target_number_actv=false, bool log_data=true){

    Game game(target_number_actv, log_data);
    Player player(&game);
    game.play(&player, &Player::best_move);

}




int main() {
    
    std::cout << "Welcome to my app. I'm Kerem and I'm studying electronics and communication engineering at ITU." << std::endl <<
                "I have a few years of coding experience and just started to learn C++ and this is my first project in C++." << std::endl <<
                "You can either play 2048 game by yourself (which is not the exciting part :D ) or" << std::endl <<
                "you can watch my algorithm, which is explained in both the github page and in the file, play it in front of you." << std::endl;
                
    
    char input;

    do{
        std::cout << std::endl <<
                     "1- To play the game please enter [1]" << std::endl <<
                     "2- To watch my algorithm play it please enter [2]" << std::endl << 
                     "q- To Quit the app please enter [q]" << std::endl;

        std::cout << std::endl << "Input: ";
        std::cin >> input;
        switch (input)
        {
        case '1':
            user_play();
            break;

        case '2':
            auto_play();
            std::cout << std::endl << "After algorithm plays the game the app needs a refresh so this program will terminate itself. Press [Enter]";
            std::cin.get();
            std::cin.get();
            break;

        case 'q':
            break;

        default:
            std::cout << "Invalid input. Please enter either 1, 2 or q" << std::endl;
            break;
        }

    }while(input != 'q' && input != '2');
    
    return 0;
}


