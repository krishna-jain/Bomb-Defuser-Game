#include <bits/stdc++.h>

using namespace std;

//***********  BOMB DEFUSER  **********

int R, C, BOMBS;
time_t start_time = time(NULL);  // Time starts

bool isValid(int row, int col) // Check for out of range cells
{
    if(row >= 0 && row < R && col >= 0 && col < C)
        return true;
    else
        return false;
}

bool isBomb(int row, int col, vector<vector<char>> &ansBoard) // Check to find if bomb is present in that cell
{
    if(ansBoard[row][col] == char(225))
        return true;
    else
        return false;
}

void takeInput(int &row, int &col) // Take input from user to play the game
{
    cout << "Enter the column character and the row number(eg:- a1): ";
    char c;
    cin >> c;
    cin >> row;
    row--;
    if(c >= 'A' && c <= 'Z')
    {
        {
            c = c - 'A' + 'a';    // coverts uppercase to lowercase
        }
    }
    col = c - 'a';
}

void showBoard(vector<vector<char>> &userBoard) // Display the current progress of the game
{
    int row = userBoard.size();
    int col = userBoard[0].size();

        // Using Ascii characters to draw a box, display bomb (is char(225)) and hide the contents (is char(219))
    int remark = rand()%7;

    switch(remark)
    {
        case 0: cout << "\n\t\t\t\t\t\t   AWESOME! \n\n";break;
        case 1: cout << "\n\t\t\t\t\t\t   GOOD MOVE! \n\n";break;
        case 2: cout << "\n\t\t\t\t\t\t   GREAT MOVE!! \n\n";break;
        case 3: cout << "\n\t\t\t\t\t\t   WONDERFUL! \n\n";break;                       // Random remarks throughout the game
        case 4: cout << "\n\t\t\t\t\t\t   AMAZING, KEEP GOING! \n\n";break;
        case 5: cout << "\n\t\t\t\t\t\t   DOING GREAT! \n\n";break;
        case 6: cout << "\n\t\t\t\t\t\t   BORN TO SAVE THE WORLD! \n\n";
    }

    cout << "\n\t\t\t\t\t\t     ";
    for(int i = 0; i < col; i++)
    {
        cout << char(i+'a') << "  ";
    }
    cout << "\n\t\t\t\t\t\t   ";
    cout << char(201);
    for(int i = 0; i < col; i++)
    {
        cout << char(205)<<char(205)<<char(205);
    }

    cout << "\n";

    for(int i = 0; i < row; i++)
    {
        cout << "\t\t\t\t\t\t";
        if(i<9) cout << " ";
        cout << i+1 << " "  << char(186) << " ";
        for(int j = 0; j < col; j++)
        {
            cout << userBoard[i][j] << "  ";
        }

        cout << "\n";
        cout << "\t\t\t\t\t\t   ";
        cout << char(186);
        cout << "\n";
    }

    cout << "\n\n\n\n";

}

int countBombs(int row, int col, vector<vector<char>> &bombs, vector<vector<char>> &ansBoard) // Counts total number of bombs in neighboring cells
{
    int count = 0;
    if(isValid(row-1, col-1))
    {
        if(isBomb(row-1, col-1, ansBoard))
            count++;
    }
    if(isValid(row-1, col))
    {
        if(isBomb(row-1, col, ansBoard))
            count++;
    }
    if(isValid(row-1, col+1))
    {
        if(isBomb(row-1, col+1, ansBoard))
            count++;
    }
    if(isValid(row, col-1))
    {
        if(isBomb(row, col-1, ansBoard))
            count++;
    }
    if(isValid(row, col+1))
    {
        if(isBomb(row, col+1, ansBoard))
            count++;
    }
    if(isValid(row+1, col-1))
    {
        if(isBomb(row+1, col-1, ansBoard))
            count++;
    }
    if(isValid(row+1, col))
    {
        if(isBomb(row+1, col, ansBoard))
            count++;
    }
    if(isValid(row+1, col+1))
    {
        if(isBomb(row+1, col+1, ansBoard))
            count++;
    }

    return count;
}

bool playGame(vector<vector<char>> &userBoard, vector<vector<char>> &ansBoard, vector<vector<char>> &bombs, int row, int col, int &movesLeft)
{
    if(userBoard[row][col] != char(219)) // INVALID MOVE
        return true;

    if(ansBoard[row][col] == char(225)) // Stepped on a BOMB
    {
        userBoard[row][col] = char(225);

        for(int i = 0; i < BOMBS; i++)
        {
            userBoard[bombs[i][0]][bombs[i][1]] = char(225);
        }
        showBoard(userBoard);
        cout << "\n\n\t\t\t\t\t YOU LOST, BETTER LUCK NEXT TIME :)\n\n";
        return false;
    }
    else // Stepped on a safe spot
    {
        int count = countBombs(row, col, bombs, ansBoard); // number of bombs surrounding the current block
   
        userBoard[row][col] = char(count+'0');

        if(count == 0) // recursively display all the blocks if no bomb nearby
        {
            if(isValid(row-1, col-1))
            {
                playGame(userBoard, ansBoard, bombs, row-1, col-1, movesLeft);
            }
            if(isValid(row-1, col))
            {
                playGame(userBoard, ansBoard, bombs, row-1, col, movesLeft);
            }
            if(isValid(row-1, col+1))
            {
                playGame(userBoard, ansBoard, bombs, row-1, col+1, movesLeft);
            }
            if(isValid(row, col-1))
            {
                playGame(userBoard, ansBoard, bombs, row, col-1, movesLeft);
            }
            if(isValid(row, col+1))
            {
                playGame(userBoard, ansBoard, bombs, row, col+1, movesLeft);
            }
            if(isValid(row+1, col-1))
            {
                playGame(userBoard, ansBoard, bombs, row+1, col-1, movesLeft);
            }
            if(isValid(row+1, col))
            {
                playGame(userBoard, ansBoard, bombs, row+1, col, movesLeft);
            }
            if(isValid(row+1, col+1))
            {
                playGame(userBoard, ansBoard, bombs, row+1, col+1, movesLeft);
            }
        }
        return true;
    }
}

void setBombs(int row, int col, vector<vector<char>> &bombs, vector<vector<char>> &ansBoard) // Randomly places bombs in the start of the game
{
    set<pair<int,int>> check;
    for(int i = 0; i < BOMBS;)
    {
        int x = rand() % row;
        int y = rand() % col;
        if(check.find({x,y}) == check.end())
        {
            bombs[i][0] = x;
            bombs[i][1] = y;
            ansBoard[bombs[i][0]][bombs[i][1]] = char(225);
            i++;
            check.insert({x,y});
        }
    }
}

void initialise(int row, int col, vector<vector<char>> &ansBoard, vector<vector<char>> &userBoard) // hides all the blocks before the start of game
{
    srand(time(NULL));
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            userBoard[i][j] = char(219);
            ansBoard[i][j] = char(219);
        }
    }
}


void replaceBomb(int row, int col, vector<vector<char>> &ansBoard) // bomb is replaced if stepped on the bomb in the very first move
{
    bool found = false;
    int x, y;
    while(found == false)
    {
        x = rand() % R;
        y = rand() % C;

        if(ansBoard[x][y] == char(219))
        {
            ansBoard[x][y] = char(225);
            found = true;
        }
    }
    ansBoard[row][col] = char(219);
}

void play(int row, int col)
{
    bool isPlaying = true;

    vector<vector<char>> ansBoard(row, vector<char> (col));
    vector<vector<char>> userBoard(row, vector<char> (col));

    int movesLeft = BOMBS;
    vector<vector<char>> bombs(BOMBS, vector<char> (2));
    initialise(row, col, ansBoard, userBoard);

    setBombs(row, col, bombs, ansBoard);
    bool firstMove = true;
    while(isPlaying)
    {
        time_t end_time = time(NULL);
        int diff = difftime(end_time, start_time);
        cout << "Current Progress in finding the bombs: \n";
        showBoard(userBoard);
        cout << "Playing time: ";
        if(diff/60 == 1)
        {
            cout << "1 minute ";
        }
        else if(diff/60>1)
        {
            cout << diff/60 << " minutes "; // Show Time Elapsed in the game so far
        }
        cout << diff%60  << " seconds"<< "\n";

        char chose;
        do{     // check for invalid input
             cout << "Press 'r' to reveal a box and 'd' to defuse a bomb \n";
             cin >> chose;

             if(chose != 'r' && chose && 'R' && chose != 'd' && chose != 'D')
                continue;
             takeInput(row,col);
        }
        while(row >= R || col >= C);

        if(chose == 'd' || chose == 'D')
        {
            if(ansBoard[row][col] == char(225))
            {
                cout << "\n\t\t\t\t\t\tA BOMB WAS SUCCESSFULLY DEFUSED!\n";
                movesLeft--;
                userBoard[row][col] = char(225);
                if(movesLeft != 0)
                continue;
            }
            else
            {
                for(int i = 0; i < BOMBS; i++)
                {
                    userBoard[bombs[i][0]][bombs[i][1]] = char(225);
                }
                showBoard(userBoard);
                cout << "THERE WAS NO BOMB TO DEFUSE THERE\n";
                cout << "\n\n\t\t\t\t\t YOU LOST, BETTER LUCK NEXT TIME :)\n\n";
                isPlaying = false;
                continue;
            }
        }

        if(firstMove)
        {
            if(isBomb(row, col, ansBoard))
              {
                  cout << row << " " << col << "\n";
                  replaceBomb(row, col, ansBoard);
              }
        }
        firstMove = false;

        if(movesLeft != 0)
        isPlaying = playGame(userBoard, ansBoard, bombs, row, col, movesLeft);

        if(isPlaying == true && movesLeft == 0)
        {
            showBoard(userBoard);
            cout << "\n\n CONGRATS, YOU DEFUSED ALL THE BOMBS! YOU WON! \n\n";
            isPlaying = false;
        }
    }
}
void selectDifficulty()
{
    cout << "Select the difficulty level\n\n";
    cout << "Enter 0 for EASY\n";
    cout << "Enter 1 for MEDIUM\n";
    cout << "Enter 2 for HARD\n";
    cout << "Enter 3 for Extreme\n";
    cout << "Enter 4 to chose your own board dimensions\n";
    int diff;
    cin >> diff;
    while(cin.fail())
    {
        cin.clear();
        cin.ignore();
        cout << "\nOops! Invalid Number, Please try again\n\n";
        cout << "Select the difficulty level\n\n";
        cout << "Enter 0 for EASY\n";
        cout << "Enter 1 for MEDIUM\n";
        cout << "Enter 2 for HARD\n";
        cout << "Enter 3 for Extreme\n";
        cout << "Enter 4 to chose your own board dimensions\n";
        cin >> diff;
    }
    if(diff == 0)
    {
        R = 7;
        C = 7;
        BOMBS = 7;
    }
    else if(diff == 1)
    {
        R = 11;
        C = 11;
        BOMBS = 18;
    }
    else if(diff == 2)
    {
        R = 18;
        C = 18;
        BOMBS = 48;
    }
    else if(diff == 3)
    {
        R = 26;
        C = 26;
        BOMBS = 97;
    }
    else if(diff == 4)
    {
        cout << "Chose the number of rows you would like to have: ";
        cin >> R;
        R = min(40, R);
        cout << "Chose the number of columns you would like to have: ";
        cin >> C;
        C = min(26, C);
        BOMBS = (double)(0.15*R*C);
    }
    else
    {
        cout << "\nOops! Invalid Number, Please try again\n\n";
        selectDifficulty();
    }
}

int main()
{
    start_time = time(NULL);

    cout << "\n\t\t\t\t\t\t   WELCOME TO BOMB DEFUSER \n\n\n";

    selectDifficulty();
    play(R,C);

    bool playAgain = true;
    string s;
    while(playAgain)
    {
        cout << "\nWould you like to play again?(y/n): ";
        cin >> s;
        cout << "\n";
        if(s == "y" || s == "Y" || s == "Yes" || s == "YES" || s == "yes")
        {
            selectDifficulty();
            play(R,C);
        }
        else playAgain = false;
    }

    return 0;
}
