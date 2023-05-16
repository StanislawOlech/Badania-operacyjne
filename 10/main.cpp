#include <iostream>
#include <vector>
#include <iomanip>

template <typename type>
type chose_size(std::vector<type> cost, type free_weight, type weight, bool maximalize){
    // Funkcja wybiera liczbę przedmiotów do wpisania, znając ich: wagi, funkcje celu i liczbę wolnych miejsc.

    int ans = 0;
    for (int i = 1; i != cost.size(); i++){
        if (maximalize and i * weight <= free_weight and cost[i] > cost[ans]){
            ans = i;
        }
        if (not maximalize and i * weight <= free_weight and cost[i] < cost[ans]){
            ans = i;
        }
    }
    return ans;
}

template <typename type>
std::vector<int> backpack_problem(std::vector<std::vector<type>> costs, std::vector<type> weights, type max_weight, bool maximalize){
    // inicjacja oraz definicja potrzebnych tablic
    int m = max_weight + 1, n = weights.size() * 2;
    std::vector<std::vector<type>> tab(m, std::vector<type> (n, 0));
    std::vector<type> ans;


    // wpisanie do tablicy pierwszego obiektu
    for (int free_weigh = 0; free_weigh != max_weight + 1; free_weigh++) {
        type i = chose_size(costs[0], free_weigh, weights[0], maximalize);
        tab[free_weigh][0] = i;
        tab[free_weigh][1] += costs[0][i];
    }

    // wpisanie pozostałych obiektów
    for(int object_num = 1; object_num != weights.size(); object_num++) {
        for (int free_weigh = 0; free_weigh != max_weight + 1; free_weigh++) {

            // liczenie nowych wag, które biorą pod uwagę poprzednie elementy
            std::vector<type> new_cost = costs[object_num];
            for (int i = 0; i != new_cost.size(); i++){
                if (free_weigh - i * weights[object_num] < 0){break;}
                new_cost[i] += tab[free_weigh - i * weights[object_num]][2 * object_num - 1];
            }

            // wpisanie reszty elementów
            type i = chose_size(new_cost, free_weigh, weights[object_num], maximalize);
            tab[free_weigh][2 * object_num] = i;
            tab[free_weigh][2 * object_num + 1] += new_cost[i];
        }
    }

    // odzyskiwanie liczby obiektów
    int sum = max_weight;
    for(int object_num = weights.size() - 1; object_num != -1; object_num--) {
        ans.insert(ans.begin(), tab[sum][2 * object_num]);
        sum -= tab[sum][2 * object_num] * weights[object_num];

    }

    for(int i = 0; i != tab.size(); i++){
        std::cout << std::setfill('0') << std::setw(2) <<  i << " |";
        for(int j = 0; j != tab[i].size(); j++){
            if (j % 2 == 1){
                std::cout <<   std::setfill('0') << std::setw(2) << tab[i][j] << " ";
            }
            else{
                std::cout << tab[i][j] << " ";
            }

        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    return ans;
}



int main() {
    std::vector<int> cost1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> cost2 = {2, 2, 2, 2 ,2, 2};
    std::vector<int> cost3 = {0, 3, 6, 12};
    std::vector<int> cost4 = {1, 5, 25};
    std::vector<int> cost5 = {2, 2, 2, 2, 2};
    std::vector<int> cost6 = {0, 5, 10};
    std::vector<int> cost7 = {10, 20, 30, 40};
    std::vector<int> cost8 = {0, 10, 20, 30};
    std::vector<int> cost9 = {0, 50};
    std::vector<int> cost10 = {0, 30, 60};
    std::vector<int> weights = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    std::vector<std::vector<int>> costs = {cost10, cost9, cost8, cost7, cost6, cost5, cost4, cost3, cost2, cost1};
    int max_weight = 200;


    std::vector<int> ans = backpack_problem(costs, weights, max_weight, true);
    for(int i = 0; i != ans.size(); i++){
        std::cout << ans[i] << " elementow o rozmiarze " << weights[i] << std::endl;
    }

    return 0;
}
