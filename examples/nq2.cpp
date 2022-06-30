

#include <iostream>
#include <vector>
using namespace std;
void printBoard(int N, const vector < vector <bool> >& b){
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            cout << ( b.at(i).at(j) ? 'Q' : '.' );
        }
        cout << endl;
    }
}
bool isValid(int N, const vector < vector <bool> >& b, int row, int column){
    for ( int r=row-1; r>=0; r-- ){ // check all rows above row
        int c;
        // test diagonal towards up-left
        c = column - (row-r);
        if ( (c>=0) && b.at(r).at(c) )  return false; // queen found
        // test vertically
        if ( b.at(r).at(column) )       return false; // queen found
        // test diagonal towards up-right
        c = column + (row-r);
        if ( (c<N) && b.at(r).at(c) )   return false; // queen found
    }
    return true;
}
bool placeQueens(int N, vector < vector <bool> >& b, int row){
    for (int column=0; column<N; column++){
        if ( isValid(N, b, row, column) ){
            b.at(row).at(column) = true; // provisionally place queen
            if ( row+1 == N ){
                return true; // last row filled, success!
            }
            if ( placeQueens(N, b, row+1) ){
                return true; // done successfully!
            }else{
                b.at(row).at(column) = false; // retract queen
            }
        }
    }
    return false; // no solution found
}
int main(){
    int N;
    cout << "How many queens to place on the board? ";
    cin >> N;
    if (  cin.fail() || ( N<1 ) ){
        cout << "error: invalid input\n";
    }else{
        vector< vector<bool> > board(N, vector<bool>(N)); // init all to false
        if ( placeQueens(N, board, 0) ){
            printBoard(N, board);
        }else{
            cout << "No solution found to place " << N << " queens on a "
                    << N << " by " << N << " chess board\n";
        }
    }
    return 0;
}

