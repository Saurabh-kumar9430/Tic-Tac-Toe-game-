#include <iostream>
#include <string>
using namespace std;

class Game
{
public:
    enum class Player { PLAYER_X, PLAYER_O, NONE };

    Game(Player p1, Player p2) : winner(Player::NONE)
    {
        if (p1 == p2) {
            cout << "Invalid game, both players are same\n";
            exit(1);
        }
        now = (p1 == Player::PLAYER_X) ? p1 : p2;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                board[i][j] = Player::NONE;
            }
        }
    }

    void displayBoard()
    {
        cout << "Current board:\n";
        cout << "   - 1 - 2 - 3 -\n";
        for (int i = 0; i < 3; ++i) {
            cout << " " << (i + 1) << " | ";
            for (int j = 0; j < 3; ++j) {
                char symbol = (board[i][j] == Player::PLAYER_X) ? 'X' : 
                              (board[i][j] == Player::PLAYER_O) ? 'O' : ' ';
                cout << symbol << " | ";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    pair<int, int> inputCell()
    {
        int row, col;
        while (true) {
            cout << "Enter row (1-3) and column (1-3) for Player " << 
                    (now == Player::PLAYER_X ? 'X' : 'O') << ": ";
            cin >> row >> col;
            if ((row < 1 || row > 3) || (col < 1 || col > 3)) {
                cout << "Invalid row or column value\n";
                continue;
            } 
            else if (board[row - 1][col - 1] != Player::NONE) {
                cout << "Cell (" << row << ", " << col << ") is already occupied\n";
                continue;
            } 
            else break;
        }
        board[row - 1][col - 1] = now;
        return { row - 1, col - 1 };
    }

    void calcWinner(pair<int, int> p)
    {
        int i = p.first, j = p.second;
        if (checkRow(i, j, now) || checkColumn(i, j, now)) {
            winner = now;
            now = Player::NONE;
            return;
        }
        if (checkDiagonals(now)) {
            winner = now;
            now = Player::NONE;
            return;
        }
        int cnt = 0;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cnt += (board[i][j] != Player::NONE);
            }
        }
        if (cnt == 9) winner = now = Player::NONE;
    }

    bool hasEnded()
    {
        return now == Player::NONE;
    }

    void switchPlayer()
    {
        now = (now == Player::PLAYER_X) ? Player::PLAYER_O : Player::PLAYER_X;
    }

    void displayWinner()
    {
        cout << "GAME OVER!\n";
        if (winner == now && now == Player::NONE) {
            cout << "It's a draw\n";
            return;
        }
        cout << "The winner is Player " << (winner == Player::PLAYER_X ? 'X' : 'O') << endl;
    }

 private:
    Player board[3][3];
    Player now;
    Player winner;
    bool checkRow(int row, int col, Player player)
    {
        for (int j = 0; j < 3; ++j) {
            if (board[row][j] != player) {
                return false;
            }
        }
        return true;
    }

    bool checkColumn(int row, int col, Player player)
    {
        for (int i = 0; i < 3; ++i) {
            if (board[i][col] != player) {
                return false;
            }
        }
        return true;
    }

    bool checkDiagonals(Player player)
    {
        if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
            (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
                return true;
        }
        return false;
    }
};

int main()
{
    while (true) {
        Game game(
            Game::Player::PLAYER_X,
            Game::Player::PLAYER_O);
        game.displayBoard();
        while (true) {
            auto p = game.inputCell();
            game.displayBoard();
            game.calcWinner(p);
            if (game.hasEnded()) break;
            game.switchPlayer();
        }
        game.displayWinner();
        cout << "\nEnter Y to replay, quit otherwise: ";
        char ch; 
        cin >> ch;
        switch (ch) {
            case 'y': case 'Y': continue;
            default: exit(0);
        }
    }
    return 0;
}
