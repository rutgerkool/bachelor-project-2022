

#include <iostream>
#include <stdlib.h>
#include <vector>
int N;
int* queens;
int* colCount;
int* upperDiagCount;
int* lowerDiagCount;
int queenQueen() {
	int conflict=0;
	for(int i=0; i<2*N-1; i++) {
		if(i<N) {
			colCount[i]=0;
		}
		upperDiagCount[i]=lowerDiagCount[i]=0;
	}
	for(int i=0; i<N; i++) {
			if(queens[i] > -1) {
				colCount[queens[i]] += 1;
				upperDiagCount[queens[i]+i] += 1;
				lowerDiagCount[(N-queens[i])+i-1] += 1;
			}
	}
	for(int i=0; i<2*N-1; i++) {
		if(i<N) {
			conflict += ((colCount[i]-1)*colCount[i])/2;
		}
		conflict += ((upperDiagCount[i]-1)*upperDiagCount[i])/2;
		conflict += ((lowerDiagCount[i]-1)*lowerDiagCount[i])/2;
	}
	return conflict;
}
void loadGame() {
	queens = new int[N];
	queens[0] = 0;
	colCount = new int[N];
	upperDiagCount = new int[(2*N)-1];
	lowerDiagCount = new int[(2*N)-1];
	for(int i=1; i<N; i++) {
		queens[i] = -1;
	}
}
void printBoard() {
	for(int i=0; i<N; i++){
		if(queens[i] < 0){
			for(int j=0; j<N; j++) {
				std::cout << "";
			}
		}
		else{
			for(int j=0; j<queens[i]; j++){
				std::cout << ".";
			}
			std::cout << "Q";
			for(int j=0; j<N-queens[i]-1; j++){
				std::cout << ".";
			}
		}
		std::cout << "\n";
	}
}
int backPath() {
	int steps = 0;
	int columnIndex = 0;
	int conflict = queenQueen();
	while(queens[N-1] < 0 || conflict > 0)	{
		while(conflict != 0) {
			//Print();
			queens[columnIndex]++;
			while(queens[columnIndex] >= N) {
				queens[columnIndex] = -1;
				columnIndex--;
				queens[columnIndex]++;
			}
			steps++;
			conflict = queenQueen();
		}
		columnIndex++;
		queens[columnIndex]=0;
		conflict = queenQueen();
	}
	return steps;
}
int main(int argc, const char *argv[]) {
	int n;
	std::cout << "How many queens to place on the board?";
	std::cin >> n;
	N = n;
	if (std::cin.fail()){
		std::cout << "\nerror: invalid input";
		return 0;
	}
	if (n == 0){
		std::cout << "\nerror: invalid input";
		return 0;
	}
	if(argc > 2){
		std::cerr << "Usage:\n\t" << argv[0] << std::endl;
		std::cerr << "\t" << argv[0] << " [Number of Queens]" << std::endl;
		return 0;
	}
	else if(argc == 2){
		n = atoi(argv[1]);
	}
	else if(n < 4){
		std::cout << "\nNo solution found to place " << n << " queens on a " << n <<  " by "<<n<<" chess board" << std::endl;
		return 0;
	}
	loadGame();
	int steps = backPath();
	if(n <= 20){
		printBoard();
	}
	return 0;
}

