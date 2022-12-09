#include <iostream>
#include <stack>
#include <unordered_set>
#include <vector>
#include <utility>
using std::stack;
using namespace std;

bool ValidCheck(int a, int b, int c, int d, int e, int f, int g, int h, int i){
    vector<int> elementsToAdd {a, b, c, d, e, f, g, h, i};
    //string valid = "";
    int spook = 0;
    unordered_set<int> val;
    for (auto number: elementsToAdd){
        if (number !=0){
            //valid+=static_cast<char>(number);
            val.insert(number);
            spook++;
            if (val.size() != spook){
                return 0;
            }
        }
    }
    return 1;
}

bool rowCheck(vector<vector<int>> &sood, int i){
    if(ValidCheck(sood[i][0], sood[i][1], sood[i][2], sood[i][3], sood[i][4], sood[i][5], sood[i][6], sood[i][7], sood[i][8]) == 1){
        return 1;
    }
    else{
        return 0;
    }
}

bool colCheck(vector<vector<int>> &sood, int j){
    if(ValidCheck(sood[0][j], sood[1][j], sood[2][j], sood[3][j], sood[4][j], sood[5][j], sood[6][j], sood[7][j], sood[8][j]) == 1){
        return 1;
    }
    else{
        return 0;
    }
}

bool blockCheck(vector<vector<int>> &sood, int i, int j){
    if(ValidCheck(sood[(i/3)*3][(j/3)*3], sood[(i/3)*3][(j/3)*3 + 1], sood[(i/3)*3][(j/3)*3 + 2], sood[(i/3)*3 + 1][(j/3)*3], sood[(i/3)*3 + 1][(j/3)*3 + 1], sood[(i/3)*3 + 1][(j/3)*3 + 2], sood[(i/3)*3 + 2][(j/3)*3], sood[(i/3)*3 + 2][(j/3)*3 + 1], sood[(i/3)*3 + 2][(j/3)*3 + 2]) == 1){
        return 1;
    }
    else{
        return 0;
    }
}

string SudokuSolve(vector<vector<int>> &sood, int &zeroes){
    int i = 0, j = 0, o = 0, p = 0, k = 0, l = 0;
    bool foundFirst = 0;
    for (size_t a = 0; a < 9; a++){
        if (foundFirst == 1){
            break;
        }
        for (size_t b = 0; b < 9; b++){
            if (sood[a][b] == 0){
                k = a;
                l = b;
                foundFirst = 1;
                break;
            }
        }
    }
    bool endOfPuzzle = 0;
    vector<vector<int>> numToAdd(9, vector<int>(9, 2));
    stack<pair<int,int>> coordinates;
    string matrix = "";
    i = k;
    j = l;
    o = k;
    p = l;
    while (endOfPuzzle == 0){
        if (rowCheck(sood, o) == 0 || colCheck(sood, p) == 0 || blockCheck(sood, o, p) == 0){
            while(sood[o][p]){
                if (numToAdd[i][j] == 10){
                    coordinates.pop();
                    sood[i][j] = 0;
                    if ((i == k && j == l) == 0){
                        numToAdd[i][j] = 2;
                    }                                        
                    if(coordinates.size() == 0){
                        i = k;
                        j = l;
                        o = k;
                        p = l;
                    }
                    else{
                        i = coordinates.top().first;
                        j = coordinates.top().second;
                        o = i;
                        p = j; 
                    }
                    zeroes++;
                }
                else{
                    if(coordinates.size() == 0){
                        i = k;
                        j = l;
                    }
                    else{
                        i = coordinates.top().first;
                        j = coordinates.top().second;    
                    }
                    sood[i][j] = 0;
                }
            }
            if (coordinates.size() == 0 && numToAdd[k][l] == 10){
                cout << "No Solution" << endl;
                return "";
            }
            else{
                if (numToAdd[i][j] <= 9){
                    sood[i][j] = numToAdd[i][j];
                    numToAdd[i][j]++;     
                }
            }
        }
        else{
            if(i < 9 && j < 9){
                if (sood[i][j] == 0){
                sood[i][j]++;
                coordinates.push(make_pair(i,j));
                zeroes--; 
                }
                if (j==8){
                    j = 0;
                    i++;
                }
                else{
                    j++;
                } 
            }
        }
        if (i > 8){
            i = 8;
            j = 8;
        }
        if(coordinates.size() == 0){
            o = k;
            p = l;
        }
        else {
            o = coordinates.top().first;
            p = coordinates.top().second;
        }
        if (zeroes == 0){
            if(rowCheck(sood, o) == 1 && colCheck(sood, p) == 1 && blockCheck(sood, o, p) == 1){
            endOfPuzzle = 1; 
            }
        }
    }
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if (j == 8){
            cout << sood[i][j];
            }
            else{
            cout << sood[i][j] << " ";
            }
        }
        cout << endl;
    }
    return matrix;
}

int main(){
    int initial, numOfZeroes = 0;
    vector<vector<int>> puzzle(9, vector<int>(9, 0));
    for (int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            cin >> initial;
            puzzle[i][j] = initial;
            if(puzzle[i][j] == 0){
                numOfZeroes++;
            }
        }
    }
    cout <<'\n' << SudokuSolve(puzzle, numOfZeroes);
}