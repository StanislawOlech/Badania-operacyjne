#include <iostream>
#include <list>
#include <cmath>
#include <limits>
#include <tuple>

int inf = std::numeric_limits<int>::max();
float float_inf = std::numeric_limits<float>::max();

template <size_t size, size_t amount>
float cal_cost(int(&costs)[amount][size], const int *ans){
    /*
    Funkcja kalkuluje czas skończenia każdego procesu.
     :param costs: macierz kosztów.
     :param ans: wskaźnik do tablicy, która zawiera kolejność wykonywania działań.
    */

    // Deklaracja tablicy czasu zakończenia każdego etapu
    int cal_cost[amount][size];


    cal_cost[0][0] = costs[0][ans[0]];
    for (size_t y = 1; y != amount; y++) {
        cal_cost[y][0] = cal_cost[y - 1][0] + costs[y][ans[0]];
    }


    for (size_t x = 1; x != size; x++) {
        cal_cost[0][x] = costs[0][ans[x]] + cal_cost[0][x - 1];

        for (size_t y = 1; y != amount; y++) {
            cal_cost[y][x] = (cal_cost[y - 1][x] > cal_cost[y][x - 1]) ? cal_cost[y - 1][x] : cal_cost[y][x - 1];
            cal_cost[y][x] += costs[y][ans[x]];
        }
    }

    return cal_cost[amount - 1][size - 1];
}


template <size_t size>
float johnson(int(&costs)[2][size], int *ans){

    // Deklaracja zmiennych
    std::list<int> path = {};
    bool exist[size];
    for(size_t x = 0; x != size; x++) {exist[x] = false;}
    float cost = 0;
    int min;
    std::tuple<int, int> cord = {0, 0};
    int start = 0;
    int end = size - 1;

    // poszukiwanie kolejności
    while(end >= start) {
        min = inf;
        for (size_t x = 0; x != size; x++) {
            if (exist[x] == true) {
                continue;
            }
            if (min > costs[0][x]) {
                min = costs[0][x];
                cord = {0, x};
            }
            if (min > costs[1][x]) {
                min = costs[1][x];
                cord = {1, x};
            }
        }

        // Wstawianie na początek
        if (std::get<0>(cord) == 0) {
            ans[start] = std::get<1>(cord);
            exist[std::get<1>(cord)] = true;
            start++;
        }

        // Wstawianie na koniec
        if (std::get<0>(cord) == 1) {
            ans[end] = std::get<1>(cord);
            exist[std::get<1>(cord)] = true;
            end--;
        }
    }

    return cal_cost(costs, ans);
}

template <size_t size, size_t amount>
float CDS(int(&costs)[amount][size], int *ans){
    // Deklaracja zmiennych
    int temp_ans[size];
    int temp_costs[2][size];
    float min = float_inf;

    for(size_t r = 0; r != amount - 1; r++){
        // Tworzenie nowej macierzy kosztów
        for(size_t x = 0; x != size; x++){temp_costs[0][x] = 0; temp_costs[1][x] = 0;}

        for(size_t x = 0; x != size; x++){
            for(size_t y = 0; y != r + 1; y++){temp_costs[0][x] += costs[y][x];}
            for(size_t y = amount - r - 1; y != amount; y++){temp_costs[1][x] += costs[y][x];}
        }

        johnson(temp_costs, temp_ans);
        float time = cal_cost(costs, temp_ans);
        if (time < min){
            min = time;
            for(size_t x = 0; x != size; x++) {ans[x] = temp_ans[x];}
        }
    }

    return min;
}

int main() {
    // Pierwszy przykład
    int costs1[2][6] = {
            {9 ,6, 8,  7, 12, 3},
            {7, 3, 5, 10, 4, 7},
    };

    int ans1[6] = {0 ,0, 0, 0, 0, 0};

    float cost1 = johnson(costs1, ans1);
    std::cout << "minimalna dlugosc: "<< cost1 << std::endl;

    for(int an : ans1) {
        std::cout << an + 1 << " -> ";
    }
    std::cout << std::endl << std::endl;


    // Drugi przykład
    int costs2[4][5] = {
            {12 ,7, 10, 4, 16},
            {10 ,12, 6, 15, 8},
            {6 ,18, 8, 13, 6},
            {15 ,9, 12, 7, 10},
    };

    int ans2[5] = {0 ,0, 0, 0, 0};

    float cost2 = CDS(costs2, ans2);
    std::cout << "minimalna dlugosc: "<< cost2 << std::endl;

    for(int an : ans2) {
        std::cout << an + 1<< " -> ";
    }
    std::cout << std::endl << std::endl;

    // Trzeci przykład
    int costs[4][10] = {
            {4 ,9, 6, 15, 8, 3, 7, 7, 10, 10},
            {3, 8, 5,  3, 1, 3, 5, 2,  8,  3},
            {5 ,2, 4,  1, 5, 2, 7, 1,  5,  8},
            {1, 3, 8,  2, 3, 7, 2, 8,  3,  7},
    };

    int ans[10] = {0 ,0, 0, 0, 0, 0, 0, 0, 0, 0};

    float cost = CDS(costs, ans);
    std::cout << "minimalna dlugosc: "<< cost << std::endl;

    for(int an : ans) {
        std::cout << an + 1<< " -> ";
    }
}