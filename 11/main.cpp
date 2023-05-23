#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
int inf = std::numeric_limits<int>::max();

template <typename type>
std::tuple<int, int> chose(std::vector<std::vector<type>>& tab, std::vector<type>& cost, std::vector<type>& storage_cost, std::vector<type>& demand, type process, type state, type min_storage){
    int min = inf;
    int min_ind;
    for(int i = 0; i != cost.size(); i++){
        type next = tab[state][0] - demand[process] + i - min_storage;
        if (cost.size() - min_storage - 1 < next or next < 0){continue;}
        int x = (demand.size() - 1 - process) * 2;
        type next_cost = tab[next][x];
        type new_cost = cost[i] + storage_cost[next] + next_cost;
        if (next_cost == inf or storage_cost[next] == inf){new_cost = inf;}

        if (new_cost < min){
            min = new_cost;
            min_ind = i;
        }
    }
    if (min == inf){
        return {-1, inf};
    }
    else{
        return {min_ind, min};
    }
}

template <typename type>
std::vector<type> decisionProcess(std::vector<type>& cost, std::vector<type>& storage_cost, std::vector<type>& demand, type end, type begin){
    // inicjacja oraz definicja potrzebnych tablic
    int min_storage = storage_cost.size();
    for(int i = 0; i != storage_cost.size(); i++){
        if (storage_cost[i] != inf){
            min_storage = i;
            break;
        }
    }

    int m = storage_cost.size() - min_storage, n = demand.size() * 2 + 1;
    std::vector<std::vector<type>> tab(m, std::vector<type> (n, 0));
    std::vector<type> ans;

    for(int i = 0; i != tab.size(); i++){
        tab[i][0] = min_storage + i;
    }

    // wpisanie do tablicy pierwszego obiektu
    for(int i = 0; i != tab.size(); i++){
        int num = end  - tab[i][0] + demand[demand.size()-1];
        if (num < 0 or num > cost.size() - 1){
            tab[i][1] = -1;
            tab[i][2] = inf;
        }
        else{
            tab[i][1] = num;
            tab[i][2] = cost[tab[i][1]];
        }

    }

    // dla każdego etapu od przedostatniego do drugiego
    for(int y = demand.size() - 2; y != -1; y--){
        int ind = (demand.size() - 1 - y) * 2 + 1;
        for(int i = 0; i != tab.size(); i++){
            std::tuple<int, int> temp = chose(tab, cost, storage_cost, demand, y, i, min_storage);
            tab[i][ind] = std::get<0>(temp);
            tab[i][ind + 1] = std::get<1>(temp);
        }
    }

    // odzyskanie
    int state = begin;
    for(int y = 0; y != demand.size(); y++){
        int ind = (demand.size() - 1 - y) * 2 + 1;
        ans.push_back(tab[state - min_storage][ind]);
        state = state + tab[state - min_storage][ind] - demand[y];
    }

    // wyświetlanie
    for(int i = 0; i != tab.size(); i++){
        std::cout <<  tab[i][0] << " |";
        for(int j = 1; j != tab[i].size(); j++){
            if (j % 2 == 1){
                if (tab[i][j] == -1){
                    std::cout << "#" << " ";
                }
                else{
                    std::cout << tab[i][j] << " ";
                }
            }
            else{
                if (tab[i][j] == inf){
                    std::cout << "inf" << "  ";
                }
                else{
                    std::cout <<   std::setfill('0') << std::setw(3) << tab[i][j] << "  ";
                }
            }

        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    return ans;
}



int main() {
    std::vector<int> cost = {2, 8, 12, 15, 17, 20};
    std::vector<int> storage_cost = {inf, 0, 0, 2, 2, 4}; // Tu mamy pojemność magazynu min i maks
    std::vector<int> demand = {4, 2, 6, 5, 3, 3, 2, 6, 0 ,5, 5, 1}; // Tu mamy ilość etapów w długości

    std::vector<int> ans = decisionProcess(cost, storage_cost, demand, 3, 4);
    for(int i = 0; i != ans.size(); i++){
        std::cout << ans[i] << " produkcja w " << i + 1 << " etapie"<< std::endl;
    }

    return 0;
}