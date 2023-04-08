#include <iostream>
#include <limits>
#include <map>
#include <list>

int inf = std::numeric_limits<int>::max();

struct path{
    int origin;
    int destination;
};

template <size_t size>
std::tuple<std::list<path>, int> FW (int(&graph)[size][size], int s, int k){

    // Deklaracja zmiennych
    int d[size][size];
    int r[size][size];
    std::list<path> A = {};

    // przepisywanie ścieżek z grafu, by nie robić zmian grafu
    // plus wypełnianie tablicy r "-1" no "0" to u mnie wierzchołek
    for (size_t y = 0; y < size; y++){
        for (size_t x = 0; x < size; x++){
            r[x][y] = -1;
            d[x][y] = graph[x][y];
            if(x == y){
                d[x][y] = 0;
            }
        }
    }

    for (size_t i = 0; i < size; i++){ // wybieramy wierzchołek, przez który będziemy przechodzić
        for (size_t y = 0; y < size; y++){ // sprawdzamy dla każdej pary wierzchołków czy przejście przez "i" skróci
            for (size_t x = 0; x < size; x++){
                if(d[x][i] != inf and  d[i][y] != inf and d[x][y] > d[x][i] + d[i][y]){
                    d[x][y] = d[x][i] + d[i][y];
                    r[x][y] = static_cast<int>(i);
                }
            }
        }
    }

    // odzyskuje ścieżkę z tablicy R
    // wrzucam ścieżkę do listy, po czym dla każdego połączenia sprawdzam, czy przechodzi przez inny
    A.push_back({s + 1, k + 1});

    for(auto i = A.begin(); i != A.end(); i ++){
        path p_old = *i;
        if (r[p_old.origin - 1][p_old.destination - 1] != -1){
            A.erase(i);
            path next = {r[p_old.origin - 1][p_old.destination - 1] + 1, p_old.destination};
            path prev = {p_old.origin, r[p_old.origin - 1][p_old.destination - 1] + 1};
            //A.erase(i);
            A.push_back(prev);
            A.push_back(next);
            i = A.begin();
        }
    }

    return {A, d[s][k]};

}

int main() {
    int graph[10][10] = {
            {inf,2,  1,  4,   3,   inf, inf, inf, inf, inf},
            {2,  inf,inf,3,   inf, inf, 5,   inf, inf, 2  },
            {1,  inf,inf,7,   1,   2,   inf, inf, inf, inf},
            {4,  3,  7,  inf, inf, 4,   4,   inf, inf, inf},
            {3,  inf,1,  inf, inf, 3,   inf, 5,   inf, inf},
            {inf,inf,2,  4,   3,   inf, 3,   3,   4,   inf},
            {inf,5,  inf,4,   inf, 3,   inf, inf, 2,   1  },
            {inf,inf,inf,inf, 5,   3,   inf, inf, 1,   inf},
            {inf,inf,inf,inf, inf, 4,   2,   1  , inf, 3  },
            {inf,2,  inf,inf, inf, inf, 1,   inf, 3,   inf},
    };

    int s = 0;
    int k = 5;
    auto ans = FW(graph, s, k);
    std::cout << "suma krawedzi dotarcia z "<< s + 1 << " do "<< k + 1 << " wynosi: "<< std::get<1>(ans) << std::endl;

    for(auto ele : std::get<0>(ans)){
        std::cout << ele.origin << " -> " << ele.destination << std::endl;
    }
}

