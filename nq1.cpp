

    #include <iostream>
    #include <vector>
    #include <algorithm>
    void checkUserInput(int amountQueens) {
        if (amountQueens <= 1) {
            throw std::runtime_error("invalid input");
        }
    }
    std::vector<std::vector<bool>> createChessboard(std::vector<std::vector<bool>>& board, int columns, int rows) {
        board.resize(columns, std::vector<bool>(rows));
        for (int i = 0; i < columns; i++) {
            for (int j = 0; j < rows; j++)
                board.at(i).at(j) = false;
        }
        return board;
    }
    bool isQueenPlacementPossible(std::vector<std::vector<bool>>&board, int row, int column) {
        int j;
        for (int i = 0; i < column; i++) {
            if (board.at(row).at(i)) {
                return false;
            }
        }
        for (int i = row, j = column; i >= 0 && j >= 0;i--,j--) {
          if (board.at(i).at(j)) {
                return false;
            }
        }
        for (int i = row, j = column;i < board.size() && j >= 0; i++, j--)  {
             if (board.at(i).at(j)) {
                return false;
            }
        }
        return true;
    }
    bool placeQueens(int N, std::vector<std::vector<bool>>&board, int column) {
        if (column >= N) {
            return true;
        }
        for (int i = 0; i < N; i++) {
            if (isQueenPlacementPossible(board,i,column)) {
                board.at(i).at(column) = true;
                if (placeQueens(N, board,column+1)) {
                    return true;
                }
                board.at(i).at(column) = false;
            }
        }
        return false;
    }
    void printChessBoard(std::vector<std::vector<bool>>& board,char queenIcon, char chessIcon) {
      for (int i = 0; i < board.size(); i++) {
          for (int j = 0; j < board.at(i).size(); j++) {
              if (board.at(i).at(j)) {
                  std::cout << queenIcon;
              } else {
                  std::cout << chessIcon;
              }
          }
          std::cout << std::endl;
      }
    }
    void otherQueenSolution(std::vector<std::vector<bool>>& board) {
        int boardLastIndex = board.size() - 1;
        std::vector<int> Queenposition;
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board.at(i).size(); j++) {
                if (board.at(i).at(j)) {
                    Queenposition.push_back(boardLastIndex-j);
                }
                board.at(i).at(j) = false;
            }
            board.at(i).at(Queenposition.at(i)) = true;
        }
    }
    int main() {
        int amountOfQueens;
        std::vector<std::vector<bool>> chessBoard;
        std::cout << "How many queens to place on the board?";
        std::cin >> amountOfQueens;
        try {
            checkUserInput(amountOfQueens);
            createChessboard(chessBoard, amountOfQueens, amountOfQueens);
            bool solution = placeQueens(amountOfQueens, chessBoard, 0);
            if (solution) {
                otherQueenSolution(chessBoard);
                printChessBoard(chessBoard, 'Q', '.');
            } else {
                std::cout << "No solution found to place "<< amountOfQueens << " queens on a "<< amountOfQueens << " by "<< amountOfQueens << " chess board" << std::endl;
            }
        } catch(std::runtime_error e) {
            std::cout << "error: " << e.what() << std::endl;
        } catch (std::out_of_range e) {
            std::cout << "error: " << e.what() << std::endl;
        } catch (...) {
            std::cout << "Unknown error..." << std::endl;
        }
        return 0;
    }

