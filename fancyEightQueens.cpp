//Nicole Haller 
#include <iostream>
using namespace std;

void nextRow(int q[], int &c);
void nextColumn(int q[], int &c);
void backTrack(int q[], int &c);
void print(int cross[], int c);

void nextColumn(int q[], int &c){
    c++;
    if (c==8) print(q, c); //if column is off the board, we have a solution to print
    nextRow(q,c); //else check next row for a solution
}

void nextRow(int q[], int &c){
    q[c]++;
    if (q[c]==8) {
        backTrack(q, c); //if row is off the board, no solutions so backtrack
    }
    for (int i=0; i<c; i++){
        if (q[c]==q[i] || (c-i)==abs(q[c]-q[i])) nextRow(q,c); //if fail row test and diagonal test try next row
    }
    nextColumn(q, c); //if passes both tests, places queen, and goes to next column
}

void backTrack(int q[], int &c){
    q[c] = -1; //re-set the value of current box to -1
    c--;
    if (c==-1) exit(1); //if column is -1 we found all solutions so exit code 
    nextRow(q,c); //check next row for a good place for queen
}

void print (int q[], int c){ 
    //print solution #
    static int solutions=0; 
    solutions++;
    cout << "solution #" << solutions << endl;

    //print 1d array
    for (int col=0; col<8; col++){
        cout << q[col] << " ";
    }
    cout << endl;

    //print fancy 2d array
    typedef char box[5][7]; //define box as 2d char array
    //define empty 5x7 white box, 5x7 empty black box, and 8x8 board array where every element is a pointer 
    box bb, wb, *board[8][8];

    //creates regular 5x7 black box and white box
    for (int r=0; r<5; r++){
        for (int c=0; c<7; c++){
            bb[r][c] = 'X'; //black box is filled with X's
            wb[r][c] = ' '; //white box is filled with blanks
        }
    } 
    
    //bq= 5x7 black queen box(black box with white queen)
    static box bq ={
        {'X','X','X','X','X','X','X'},   
        {'X',' ','X',' ','X',' ','X'},
        {'X',' ','X',' ','X',' ','X'},
        {'X',' ',' ',' ',' ',' ','X'},
        {'X','X','X','X','X','X','X'},
        };
    //wq= 5x7 white queen box(white box with black queen of Xs)
    static box wq= {
        {' ',' ',' ',' ',' ',' ',' '},   
        {' ', 'X',' ','X',' ','X',' '},
        {' ', 'X',' ','X',' ','X',' '},
        {' ', 'X','X','X','X','X',' '},
        {' ',' ',' ',' ',' ',' ',' '},
        };
    
    //filling board with address of white boxes and black boxes(empty chess board)
    for (int r=0; r<8; r++){
        for (int c=0; c<8; c++){
             if ((r+c)%2==0){ 
                board[r][c] = &bb;//if r+c is even, assign the address of black box to that box
             } else {
                board[r][c]= &wb; //if r+c is odd, assigns address of white box to that specific box
             }
        }
    }

    //assigning address of white queen(wq) and black queen(bq) to the appropriate boxes
    for (int r=0; r<8; r++){
        for (int c=0; c<8; c++){
            if (r==q[c]){ //if a queen belongs in that box... 
                if ((r+c)%2 ==0) board[r][c]= &bq; // if r+c is even, assign address of a black queen to the specific box 
                else board[r][c]= &wq;//if r+ c is odd, assign adress of a white queen to the specific box
            } 
        }
    }
    
    //print the actual board (by dereferencing the addresses already placed in the boxes) 
    for (int i=0; i<8; i++){ //the board rows
        for (int r=0; r<5; r++){ //the individual box rows(5x7 so 5)
            for (int j=0; j<8; j++){ //the board columns (7 columns across)
                for (int c=0; c<7; c++){ //the individual box columns
                    box *currentBox= board[i][j]; //points to current box we are in//refers to current box, pointer is stored in currentBox variable, //board[i][j] holds address of box we want to print, need whats inside(contents of 5x7) so dereference 
                    //dereference currentBox to access what is stored there, [r][c] to print that particular column of that 2d array
                    cout<< (*board[i][j])[r][c]; //(*board[i][j]) refers to bb or wb(dereference the address) and then find specific box row and column within those by doing [r][c]
                    //or *(currentBox)[r][c];
                }
            }
            cout << endl;
        }
    }
    //after find one solution, need to go back and check for more
    backTrack(q,c);
}

int main(){
    int q[8]= {0};
    int c=0;
    q[0]=0; //sets top left corner of 2d array to have a queen to start 
    nextColumn(q, c);
    return 0;
}