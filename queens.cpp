#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdio>
#include <cstdlib>

using namespace std;

int Val(char (*arr), int M, int N) // finds value at current state
{
    char newArr[M][N]; //creates local array so it doesnt manipulate pointer passed through
    for(int i=0; i<M; i++)
    {
        for (int j=0; j<N; j++)
        {
            newArr[i][j] = arr[i*N + j]; //copies pointer (state) to array
        }
    }
    
    int score = 0; // number  of violations
    for(int i = 0; i < M; i++)
    {
        for(int j = 0; j < N; j++)
        {
            //check B
            if (newArr[i][j] == 'B')
            {
                //same row
                for (int k = 0; k < N; k++)
                {
                    if (newArr[i][k] == 'W')
                        score++;
                }
                
                //same column
                for (int k = 0; k < M; k++)
                {
                    if (newArr[k][j] == 'W')
                        score++;
                }
                
                //------diagonals------
                
                // up left
                int x = i - 1;
                int y = j - 1;
                while (x >= 0 && y >= 0)
                {
                    if (newArr[x][y] == 'W')
                        score++;
                    x--;
                    y--;
                }
                
                //up right
                x = i - 1;
                y = j + 1;
                while (x >= 0 && y < N)
                {
                    if (newArr[x][y] == 'W')
                        score++;
                    x--;
                    y++;
                }
                
                // down left
                x = i + 1;
                y = j - 1;
                while (x < M && y >= 0)
                {
                    if (newArr[x][y] == 'W')
                        score++;
                    x++;
                    y--;
                }
                
                //down right
                x = i + 1;
                y = j + 1;
                while (x < M && y < N)
                {
                    if (newArr[x][y] == 'W')
                        score++;
                    x++;
                    y++;
                }
                
            }
        }
    }
    return score;
}

int Val(char (*arr), int M, int N, char rep, int oldPos, int newPos) // same value function but gives parameters for a potential swap
{
    char newArr[M][N]; //creates local array so pointer is not manipulated
    for(int i=0; i<M; i++)
    {
        for (int j=0; j<N; j++)
        {
            newArr[i][j] = arr[i*N + j]; //turns pointer into 2d array
        }
    }
    newArr[(int)(newPos / N)][newPos % N] = rep;
    newArr[(int)(oldPos / N)][oldPos % N] = ' ';
    
    int score = 0;
    for(int i = 0; i < M; i++)
    {
        for(int j = 0; j < N; j++)
        {
            //check B
            if (newArr[i][j] == 'B')
            {
                //same row
                for (int k = 0; k < N; k++)
                {
                    if (newArr[i][k] == 'W')
                        score++;
                    
                }
                
                //same column
                for (int k = 0; k < M; k++)
                {
                    if (newArr[k][j] == 'W')
                        score++;
                }
                
                //------diagonals------
                
                // up left
                int x = i - 1;
                int y = j - 1;
                while (x >= 0 && y >= 0)
                {
                    if (newArr[x][y] == 'W')
                        score++;
                    x--;
                    y--;
                }
                
                //up right
                x = i - 1;
                y = j + 1;
                while (x >= 0 && y < N)
                {
                    if (newArr[x][y] == 'W')
                        score++;
                    x--;
                    y++;
                }
                
                // down left
                x = i + 1;
                y = j - 1;
                while (x < M && y >= 0)
                {
                    if (newArr[x][y] == 'W')
                        score++;
                    x++;
                    y--;
                }
                
                //down right
                x = i + 1;
                y = j + 1;
                while (x < M && y < N)
                {
                    if (newArr[x][y] == 'W')
                        score++;
                    x++;
                    y++;
                }
                
            }
        }
    }
    return score;
}

void findBestNeigh(char (*s), char (*arr), int M, int N) //finds best neighbor
{
    int bestScore, curScore, bestPosFrom, bestPosTo;
    bestScore = 100000; //initializes as very high number
    int posFrom, posTo;
    
    char curRep, bestRep; // rep is whatever color queen the iteration finds
    for(int i=0; i<M; i++)
    {
        for (int j=0; j<N; j++)
        {
            arr[i*N+j] = s[i*N + j]; //copies current state to neighbor state bc neigh is constantly manipulated
        }
    }
    
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++) //iterates through the entire board
        {
            if ( arr[i*N + j] != ' ') // when it finds a queen
            {
                posFrom = i*N + j; //sets current position
                curRep = arr[i*N + j]; // sets color as current queen's
                for (int x = 0; x < M; x++)
                {
                    for (int y = 0; y < N; y++) //iterates to find the best possible position for that queen
                    {
                        posTo = x*N + y;
                        if ( arr[x*N+y] == ' ') //only looking for empty spaces to put queen
                        {
                            curScore = Val(arr, M, N, curRep, posFrom, posTo); // finds potential score if that queen was swapped with this empty space
                            if (curScore < bestScore) // if this score is less than the best, then mark it as the best
                            {
                                bestScore = curScore;
                                bestRep = curRep;
                                bestPosFrom = i*N + j;
                                bestPosTo = x*N+y;
                            }
                        }
                    }
                }
            }
        }
    }
    arr[bestPosTo] = bestRep; // make the best move
    arr[bestPosFrom] = ' ';
}

void InitBoard(char *s, int M, int N, int B, int W) //initiallizes board
{
    for(int i = 0; i < M; i++)
    {
        for(int j = 0; j < N; j++)
        {
            s[i*N+j] = ' '; //creates empty board
        }
    }
    int m, n;
    for (int i = 0; i < B; i++) //places black queens
    {
        do
        {
            m = rand() % M;
            n = rand() % N;
        } while ( s[m*N+n] != ' ');
        s[m*N+n] = 'B';
    }
    
    for (int i = 0; i < W; i++) //places white queens
    {
        do
        {
            m = rand() % M;
            n = rand() % N;
        } while ( s[m*N+n] != ' ');
        s[m*N+n] = 'W';
    }
    
}

int main (int argc, char** argv)
{
    int N, M, W, B;
    double tmax;
    string fileName;
    bool extra;
    
    M=strtol(argv[1], nullptr, 0);
    N=strtol(argv[2], nullptr, 0);
    W=strtol(argv[3], nullptr, 0);
    B=strtol(argv[4], nullptr, 0);
    tmax = strtol(argv[5], nullptr, 0) * CLOCKS_PER_SEC;
    fileName = argv[6];
    
    if ( strcmp(argv[7], "extra") == 0 )
        extra = true;
    else
        extra = false;
    
    srand(time(NULL));
    
    if ( B + W > M * N -1) // error prevention if there are more queens than board spaces
    {
        cout << "Cannot have that many queens for this board" << endl;
        return -1;
    }
    
    //initialize
    char s[M][N];
    cout << "Creating board..." << endl;
    InitBoard(*s,M,N,B,W);
    
    // write to initial state file
    ofstream initFile;
    initFile.open("InitialState.txt");
    if(initFile.is_open())
    {
        initFile << "Initial number of violations: " << Val(*s, M, N) << endl;//show initial score
        for(int i=0; i<M; i++)
        {
            for (int j=0; j<N; j++)
            {
                initFile << " | ";
                initFile << s[i][j];
            }
            initFile << " |" << endl;
        }
    }
    initFile.close();
    
    // start finding neighbors
    clock_t start = clock();  // Start Clock
    char sNeigh[M][N]; // creates state for neighbor
    int bestVal = Val(*s,M,N);
    char bestState[M][N]; // creates state to store best state
    
    int counter = 0; // counter for number of random restarts
    int valState, valNeigh;
    
    const int GOAL = 0;
    cout << "Starting loop..." << endl;
    while (Val(*s,M,N) > GOAL && (clock() - start) < tmax)
    {
        findBestNeigh(*s, *sNeigh, M, N);
        valState = Val(*s,M,N);
        valNeigh = Val(*sNeigh,M,N);
        
        /*
         if (valNeigh < bestVal) // CANT PUT THIS HERE FOR SOME REASON
         bestVal = valNeigh;
         */
        
        if (valNeigh < valState) // if value of neigh is less than current state's value
        {
            for(int i =0; i < M; i++)
            {
                for(int j = 0; j < N; j++)
                {
                    s[i][j] = sNeigh[i][j]; // make the neigh state the current state
                    if (valNeigh < bestVal)
                    {
                        bestState[i][j] = sNeigh[i][j]; // if the neigh state is better than the best state, copy it too
                    }
                }
            }
        }
        if (valNeigh == GOAL) // had to create this bc of weird error above
        {
            bestVal = GOAL;
            cout << "Found a solution!" << endl;
        }
        else if ( extra && valNeigh >= valState) // if neigh state isn't better, then random restart
        {
            if (valState < bestVal)
                bestVal = valState;
            counter++;
            cout << "Restarting... Score at this state was " << valState << endl;
            InitBoard(*s, M, N, B, W); // random restart. re initializes state
        }
        if (clock() - start > tmax) // if the time has expired and the current state is better than the best state
            if (valState < bestVal)
                bestVal = valState;
    }
    
    if ( bestVal != GOAL )
        cout << "Time expired. No perfect solution found." << endl;
    
    clock_t timeC = (clock() - start);
    int timeS = timeC / CLOCKS_PER_SEC;
    double timeM = timeC / (CLOCKS_PER_SEC/1000);
    
    ofstream outputFile;
    outputFile.open(fileName);
    if(outputFile.is_open())
    {
        outputFile << "Final number of violations: " << bestVal << endl;
        outputFile << "Total number of restarts: " << counter << endl;
        outputFile << "Time taken: " << timeS << " seconds or " << timeM << " milliseconds" << endl;
        for(int i=0; i<M; i++)
        {
            for (int j=0; j<N; j++)
            {
                outputFile << " | ";
                outputFile << bestState[i][j];
            }
            outputFile << " |" << endl;
        }
        if (bestVal == GOAL)
            outputFile << "YES" << endl;
        else
            outputFile << "NO" << endl;
    }
    outputFile.close();
    
    return 0;
}


