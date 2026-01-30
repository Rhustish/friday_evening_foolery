#include <vector>

enum class PlayerSide{
    WHITE = 0,
    BLACK
};

class Player {
    PlayerSide side;
    int ownMaterial, opponentMaterial;
public:
    explicit Player(const PlayerSide side) : side(side), ownMaterial(0), opponentMaterial(0) {}
};

class Piece {
protected:
    PlayerSide player;
public:
    virtual ~Piece() = default;
    explicit Piece(const PlayerSide player) : player(player) {}
    PlayerSide getPlayer() const {
        return player;
    }
    virtual std::vector<std::pair<int,int>>getMoves(int x , int y) = 0;
};

class Pawn final : public Piece {
private:
    bool isOnHomeRow(const int y) const {
        if (player == PlayerSide::WHITE && y == 1) return true;
        if (player == PlayerSide::BLACK && y == 6) return true;
        return false;
    }
public:
    explicit Pawn(const PlayerSide player) : Piece(player) {}
    std::vector<std::pair<int,int>> getMoves(const int x , const int y) override {
        std::vector<std::pair<int,int>> moves;
        if (isOnHomeRow(y)) {
           moves.emplace_back(x, y + (player == PlayerSide::WHITE ? 2 : -2));
        }
        moves.emplace_back(x, y + (player == PlayerSide::WHITE ? 1 : -1));
        if (x > 0) {
            moves.emplace_back(x - 1, y + (player == PlayerSide::WHITE ? 1 : -1));
        }
        if (x < 7) {
            moves.emplace_back(x + 1, y + (player == PlayerSide::WHITE ? 1 : -1));
        }
        return moves;
    }
};

class Knight final : public Piece {
public:
    explicit Knight(const PlayerSide player) : Piece(player) {}
    std::vector<std::pair<int,int>> getMoves(const int x ,const  int y) override {
  static const int offsets[8][2] = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
    };
    std::vector<std::pair<int, int>> moves;
    for (const auto& offset : offsets) {
        int nx = x + offset[0];
        int ny = y + offset[1];
        if (nx >= 0 && nx <= 7 && ny >= 0 && ny <= 7) {
            moves.emplace_back(nx, ny);
        }
    }
        return moves;
    }
};

class Bishop final : public Piece {
public:
    explicit Bishop(const PlayerSide player) : Piece(player) {}
    std::vector<std::pair<int,int>> getMoves(int x , int y) override {
        std::vector<std::pair<int,int>> moves;
        for (int dx = -1; dx <= 1; dx += 2) {
            for (int dy = -1; dy <= 1; dy += 2) {
                for (int step = 1; step < 8; ++step) {
                    int nx = x + step * dx;
                    int ny = y + step * dy;
                    if (nx < 0 || nx > 7 || ny < 0 || ny > 7) break;
                    moves.emplace_back(nx, ny);
                }
            }
        }
        return moves;
    }
};

class Rook final : public Piece {
public:
    explicit Rook(const PlayerSide player): Piece(player) {}
    std::vector<std::pair<int,int>> getMoves(const int x ,const int y) override {
        std::vector<std::pair<int,int>> moves;
        for (int dir = -1; dir <= 1; dir += 2) {
            for (int step = 1; step < 8; ++step) {
                int nx = x + step * dir;
                if (nx < 0 || nx > 7) break;
                moves.emplace_back(nx, y);
            }
            for (int step = 1; step < 8; ++step) {
                int ny = y + step * dir;
                if (ny < 0 || ny > 7) break;
                moves.emplace_back(x, ny);
            }
        }
        return moves;
    }
};

class Queen final : public Piece {
public:
    explicit Queen(const PlayerSide player) : Piece(player) {}
    std::vector<std::pair<int,int>> getMoves(const int x ,const int y) override {
        std::vector<std::pair<int,int>> moves;
        auto rookMoves = Rook(player).getMoves(x,y);
        moves.insert(moves.end(), rookMoves.begin(), rookMoves.end());
        auto bishopMoves = Bishop(player).getMoves(x,y);
        moves.insert(moves.end(), bishopMoves.begin(), bishopMoves.end());
        return moves;
    }
};

class King final : public Piece {
public:
    explicit King(const PlayerSide player) : Piece(player) {}
    std::vector<std::pair<int,int>> getMoves(const int x ,const int y) override {
        std::vector<std::pair<int,int>> moves;
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx == 0 && dy == 0) continue;
                int nx = x + dx;
                int ny = y + dy;
                if (nx >= 0 && ny <= 7 && ny >= 0 && ny <= 7) {
                    moves.emplace_back(nx, ny);
                }
            }
        }
        return moves;
    }
};

struct Square {
    Piece *piece;
};

class Board {
private:
    std::vector<std::vector<Square*>> grid;
public:
    Board() {
        grid.resize(8, std::vector<Square*>(8));
    }
};


class Game {
    Board *board = new Board();

    std::unique_ptr<Player> white = std::make_unique<Player>(PlayerSide::WHITE);
    std::unique_ptr<Player> black=  std::make_unique<Player>(PlayerSide::BLACK);

    bool turn = static_cast<bool>(PlayerSide::WHITE);
};

int main() {

    return 0;
}