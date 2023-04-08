#include <iostream>
#include <limits>
#include <map>
#include <list>
#include <algorithm>

int inf = std::numeric_limits<int>::max();

struct path{
    int origin;
    int destination;
};

template <size_t size>
std::tuple<std::list<path>, int> FARIN(int(&graph)[size][size], int s){

    // Deklaracja zmiennych
    std::list<path> A = {};
    std::list<path> newA = {};
    int short_n = -1;
    int short_e = -1;
    std::list<int> visited;
    int length = 0;
    int shortest = -1;

    visited.push_back(s);

    // szukanie następnego wierzchołka
    for (auto y : visited){
        for (size_t x = 0; x < size; x++){
            if (std::find(std::begin(visited), std::end(visited), x) ==  std::end(visited) and graph[y][x] != inf and graph[y][x] > short_e){
                short_e = graph[y][x];
                short_n = static_cast<int>(x);
            }
        }
    }

    // dodwawanie wierzchołka
    visited.push_back(short_n);
    A.push_back({s + 1, short_n + 1});
    A.push_back({ short_n + 1, s + 1,});



    while (A.size() != size ){
        short_e = -1;
        // szukanie następnego wierzchołka
        for (auto y : visited){
            for (size_t x = 0; x < size; x++){
                if (std::find(std::begin(visited), std::end(visited), x) ==  std::end(visited) and graph[y][x] != inf and graph[y][x] > short_e){
                    short_e = graph[y][x];
                    short_n = static_cast<int>(x);
                }
            }
        }
        visited.push_back(short_n);

        // szukanie miejsca gdzie wpisać wierzchołek
        short_e = inf;
        for(auto p = A.begin(); p != A.end(); p++){
            length = 0;
            for(auto a = A.begin(); a != p; a++){
                if (length == inf or graph[a->origin - 1][a->destination - 1] == inf){
                    length = inf;
                }
                else{
                    length += graph[a->origin - 1][a->destination - 1];
                }
            }

            auto x = p;
            x ++;
            for(auto b = x; b != A.end(); b++){
                if (length == inf or graph[b->origin - 1][b->destination - 1] == inf){
                    length = inf;
                }
                else{
                    length += graph[b->origin - 1][b->destination - 1];
                }
            }

            int sum = graph[p->origin - 1][short_n] + graph[short_n][p->destination - 1] + length;

            if (graph[p->origin - 1][short_n] == inf){
                sum = inf;
            }

            if (graph[short_n][p->destination - 1] == inf){
                sum = inf;
            }

            if (length == inf){
                sum = inf;
            }

            // elminacja inf-a
            if (graph[p->origin - 1][p->destination - 1] == inf and sum != inf){
                short_e = sum;
                shortest = p->origin - 1;
                continue;
            }

            // normalny przypadek wybieramy najkrótszy
            if (sum < short_e){
                short_e = sum;
                shortest = p->origin - 1;
                continue;
            }

            // jak jakikolwiek zadziałał to nie szukamy w infach
            if (short_e != inf){
                continue;
            }

            // dodawanie wierzchołka mimo nieskończonej ścieżki
            if (graph[p->origin - 1][short_n] != inf and graph[short_n][p->destination - 1] != inf){
                short_e = sum;
                shortest = p->origin - 1;
                continue;
            }

            // dodawanie wierzchołka z jednym infem
            if ((graph[p->origin - 1][short_n] != inf or graph[short_n][p->destination - 1] != inf) and sum == inf){
                shortest = p->origin - 1;
            }

        }
        length = 0;

        // dodawanie wierzchołka do ścieżki
        for(auto p : A){
            if (p.origin - 1 == shortest){
                path next = {short_n + 1,  p.destination};
                path prev = {p.origin, short_n + 1};
                //A.erase(i);
                newA.push_back(prev);
                newA.push_back(next);
            }
            else{
                newA.push_back(p);
            }
        }

        A = newA;
        newA.clear();

    }

    // liczenie długośći
    for(auto p : A){

        if (length == inf or graph[p.origin - 1][p.destination - 1] == inf){
            length = inf;
        } else{
            length += graph[p.origin - 1][p.destination - 1];
        }
    }

    return {A, length};

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
    auto ans = FARIN(graph, s);
    std::cout << "suma kormiwojazera z "<< s + 1 << " wynosi: "<< std::get<1>(ans) << std::endl;

    for(auto ele : std::get<0>(ans)){
        std::cout << ele.origin << " -> " << ele.destination << std::endl;
    }
}
