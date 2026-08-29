#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

struct Cell {
    int value = 0;                     // wartosc dla zwyklej komorki (formula pusta)
    std::vector<std::string> formula;  // pusta = zwykla wartosc
    int cached = 0;                    // ostatnio policzony wynik formuly (memoizacja)
    bool dirty = false;                // czy cached trzeba przeliczyc
};

class Excel {
    public:
        Excel(int height, char width);

        void set(int row, char column, int val);

        int get(int row, char column);

        int sum(int row, char column, std::vector<std::string> numbers);

    private:
        int height_;
        char width_;
        std::vector<std::vector<Cell>> sheet_;

        // graf zaleznosci: dependents_[X] = komorki, ktorych formula czyta X
        std::map<std::pair<int, char>, std::set<std::pair<int, char>>> dependents_;

        Cell& at(int row, char col);

        static std::pair<int, char> parseCell(const std::string& address);
        static std::vector<std::pair<int, char>> cellsInToken(const std::string& token);

        int evalToken(const std::string& token);

        void registerDeps(std::pair<int, char> key, const std::vector<std::string>& formula);
        void unregisterDeps(std::pair<int, char> key, const std::vector<std::string>& formula);
        void markDirty(std::pair<int, char> key);
    };
