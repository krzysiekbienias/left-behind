#include <cstddef>
#include <excel_sum.hpp>
#include <string>
#include <utility>

Excel::Excel(int height, char width)
    : height_(height),
      width_(width),
      sheet_(height, std::vector<Cell>(width - 'A' + 1)) {}

Cell& Excel::at(int row, char col) {
    return sheet_[row - 1][col - 'A'];
}

void Excel::set(int row, char col, int val) {
    std::pair<int, char> key = {row, col};
    Cell& cell = at(row, col);

    unregisterDeps(key, cell.formula);  // komorka przestaje zalezec od czegokolwiek
    cell.value = val;
    cell.formula.clear();
    cell.dirty = false;                 // zwykla wartosc, nic do liczenia

    markDirty(key);                     // ci, co zaleza od tej komorki, sa nieaktualni
}

int Excel::get(int row, char col) {
    Cell& cell = at(row, col);

    if (cell.formula.empty()) {
        return cell.value;
    }
    if (cell.dirty) {                   // cache nieaktualny -> policz raz i zapamietaj
        int total = 0;
        for (const std::string& token : cell.formula) {
            total += evalToken(token);
        }
        cell.cached = total;
        cell.dirty = false;
    }
    return cell.cached;                 // memoizacja: kolejne get zwroca to samo w O(1)
}

int Excel::sum(int row, char col, std::vector<std::string> numbers) {
    std::pair<int, char> key = {row, col};
    Cell& cell = at(row, col);

    unregisterDeps(key, cell.formula);  // zerwij stare zaleznosci
    cell.formula = std::move(numbers);
    registerDeps(key, cell.formula);    // zarejestruj nowe krawedzie grafu
    cell.dirty = true;                  // formula wymaga przeliczenia

    markDirty(key);                     // zalezni tez sa nieaktualni
    return get(row, col);
}

std::pair<int, char> Excel::parseCell(const std::string& address) {
    return {std::stoi(address.substr(1)), address[0]};
}

std::vector<std::pair<int, char>> Excel::cellsInToken(const std::string& token) {
    std::vector<std::pair<int, char>> cells;
    size_t colon = token.find(':');
    if (colon == std::string::npos) {
        cells.push_back(parseCell(token));  // pojedyncza komorka, np. "K55"
        return cells;
    }
    std::pair<int, char> start_edge = parseCell(token.substr(0, colon));
    std::pair<int, char> end_edge = parseCell(token.substr(colon + 1));
    for (int r = start_edge.first; r <= end_edge.first; r++) {
        for (char c = start_edge.second; c <= end_edge.second; c++) {
            cells.push_back({r, c});
        }
    }
    return cells;
}

int Excel::evalToken(const std::string& token) {
    int total = 0;
    for (const std::pair<int, char>& rc : cellsInToken(token)) {
        total += get(rc.first, rc.second);  // rekurencja z memoizacja w get
    }
    return total;
}

void Excel::registerDeps(std::pair<int, char> key, const std::vector<std::string>& formula) {
    for (const std::string& token : formula) {
        for (const std::pair<int, char>& rc : cellsInToken(token)) {
            dependents_[rc].insert(key);
        }
    }
}

void Excel::unregisterDeps(std::pair<int, char> key, const std::vector<std::string>& formula) {
    for (const std::string& token : formula) {
        for (const std::pair<int, char>& rc : cellsInToken(token)) {
            dependents_[rc].erase(key);
        }
    }
}

void Excel::markDirty(std::pair<int, char> key) {
    auto it = dependents_.find(key);
    if (it == dependents_.end()) {
        return;
    }
    for (const std::pair<int, char>& dep : it->second) {
        Cell& dc = at(dep.first, dep.second);
        if (!dc.dirty) {                // guard: nie schodz drugi raz w to samo poddrzewo
            dc.dirty = true;
            markDirty(dep);             // propaguj unieważnienie w gore grafu
        }
    }
}
