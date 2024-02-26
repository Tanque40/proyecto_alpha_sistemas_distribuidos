#include <map>
#include <string>
#include <vector>

class WhackAMole {
   private:
    int boardSize;
    std::vector<std::vector<int>> board;
    std::map<int, int> userPuntuation;

   public:
    WhackAMole(int boardSize);
    void setBoardSize(int boardSize);
    int getBoardSideSize();
    std::string getBoard();
    bool setNewUserPuntuation(int userId);
    int getNewMolePosition();
    bool setUserPuntuation(int userId);
};