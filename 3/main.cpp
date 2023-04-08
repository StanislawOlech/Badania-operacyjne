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
std::tuple<std::list<path>, int> DPA (int(&graph)[size][size], int s){

    // Deklaracja zmiennych
    int suma = 0;
    std::list<path> A = {};
    int alfa[size];
    int beta[size];
    std::list<int> Q;

    // Wpisanie wszystkich wierzchołków do listy do odwiedzenia
    for(size_t i = 0; i < size; i++){
        Q.push_back(i);
        alfa[i] = 0;
        beta[i] = inf;
    }

    // uaktualnienie kosztu przejścia do wierzchołka 1 oraz usunięcie go z listy
    beta[s - 1] = 0;
    Q.remove(s - 1);
    int u_last = s - 1;

    while (!Q.empty()){

        // Pętla uaktualniająca koszt przejścia do każdego wierzchołka z nowo przyłączonego
        for(auto u_it = Q.begin();u_it != Q.end(); u_it++){
            int u = *u_it;
            if (graph[u_last][u] != inf and graph[u_last][u] < beta[u]){
                alfa[u] = u_last;
                beta[u] = graph[u_last][u];
            }
        }

        // Poszukiwanie najtańszego do przyłączenia wierzchołka
        int min = inf;
        for(auto u_it = Q.begin();u_it != Q.end(); u_it++){
            int u = *u_it;
            if (beta[u] < min){
                min = beta[u];
                u_last = u;
            }
        }


        // Przyłączenie nowego wierzchołka
        Q.remove(u_last);
        path temp = {alfa[u_last] + 1, u_last + 1};
        A.push_back(temp);
        suma += graph[alfa[u_last]][u_last];
    }
    return {A, suma};

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


    auto ans = DPA(graph, 1);
    std::cout << "suma krawedzi MST: "<< std::get<1>(ans) << std::endl << std::endl;

    for(auto ele : std::get<0>(ans)){
        std::cout << ele.origin << " -> " << ele.destination << std::endl;
    }
}

