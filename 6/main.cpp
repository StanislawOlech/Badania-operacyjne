#include <iostream>
#include <limits>
#include <map>
#include <list>
#include <algorithm>
#include <cmath>

int inf = std::numeric_limits<int>::max();
float float_inf = std::numeric_limits<float>::max();

struct path{
    int origin;
    int destination;
};

struct re_num{
    int org_num;
    int new_num;
};


template <size_t size>
std::tuple<std::list<path>, float> PERT(int(&tc)[size][size], int(&tm)[size][size], int(&tp)[size][size]){

    // Deklaracja zmiennych
    std::list<path> path = {};
    std::list<re_num> new_name = {};
    std::list<size_t> nodes = {};
    float tx[size][size];
    float tw_x[size];
    float tp_x[size];
    float ans;

    for (size_t x = 0; x < size; x++) {
        for (size_t y = 0; y < size; y++) {
            if (tc[x][y] != inf){
                tx[x][y] = 1.29 * pow(pow(tp[x][y] - tc[x][y], 2) / 36, 0.5) + (float(tc[x][y]) / 6 + 4.0 / 6 * float(tm[x][y]) + float(tp[x][y]) / 6);
            } else{
                tx[x][y] = float_inf;
            }
        }
    }



    // Przenumerowanie
    int i = 0;
    while (nodes.size() != size) {
        for (size_t x = 0; x < size; x++) {
            if(std::find(nodes.begin(), nodes.end(), x) != nodes.end()){
                continue;
            }

            bool flag = true;


            for (size_t y = 0; y < size; y++) {
                if(std::find(nodes.begin(), nodes.end(), y) != nodes.end()){
                    continue;
                }
                if (tc[y][x] != inf and y != x) {
                    flag = false;
                }
            }

            if (flag) {
                new_name.push_back({static_cast<int>(x), i});
                nodes.push_back(x);
                i++;
            }
        }
    }

    for(auto& x :new_name){
        float sum = 0;
        for (size_t y = 0; y < size; y++) {
            if (tx[y][x.org_num] != float_inf and tx[y][x.org_num] + tw_x[y] > sum){
                sum = tx[y][x.org_num] + tw_x[y];
            }
        }
        tw_x[x.org_num] = sum;
        tp_x[x.org_num] = sum;
    }

    for(auto x = new_name.rbegin(); x != new_name.rend(); x++){
        re_num ele = x.operator*();
        if (ele.new_num == size -1){continue;}

        float sum = float_inf;
        for (size_t y = 0; y < size; y++) {
            if (tx[ele.org_num][y] != float_inf and tp_x[y] - tx[ele.org_num][y] < sum){
                sum = tp_x[y] - tx[ele.org_num][y];
            }
        }
        tp_x[ele.org_num] = sum;
    }

    int last = 0;
    bool flag = false;
    for(auto& x :new_name){
        if (!flag){
            last = x.org_num;
            flag = true;
            continue;
        }
        if(abs(tw_x[x.org_num] - tp_x[x.org_num]) < 0.0001){
            path.push_back({last, x.org_num});
            last = x.org_num;
        }
        ans = tw_x[x.org_num];
    }




    return {path, ans};

}

template <size_t size>
std::tuple<std::list<path>, float> PERT(int(&tc)[size][size]){

    // Deklaracja zmiennych
    std::list<path> path = {};
    std::list<re_num> new_name = {};
    std::list<size_t> nodes = {};
    float tx[size][size];
    float tw_x[size];
    float tp_x[size];
    float ans;

    for (size_t x = 0; x < size; x++) {
        for (size_t y = 0; y < size; y++) {
            if (tc[x][y] != inf){
                tx[x][y] = float(tc[x][y]);
            } else{
                tx[x][y] = float_inf;
            }
        }
    }

    // Przenumerowanie
    int i = 0;
    while (nodes.size() != size) {
        for (size_t x = 0; x < size; x++) {
            if(std::find(nodes.begin(), nodes.end(), x) != nodes.end()){
                continue;
            }

            bool flag = true;


            for (size_t y = 0; y < size; y++) {
                if(std::find(nodes.begin(), nodes.end(), y) != nodes.end()){
                    continue;
                }
                if (tc[y][x] != inf and y != x) {
                    flag = false;
                }
            }

            if (flag) {
                new_name.push_back({static_cast<int>(x), i});
                nodes.push_back(x);
                i++;
            }
        }
    }

    for(auto& x :new_name){
        float sum = 0;
        for (size_t y = 0; y < size; y++) {
            if (tx[y][x.org_num] != float_inf and tx[y][x.org_num] + tw_x[y] > sum){
                sum = tx[y][x.org_num] + tw_x[y];
            }
        }
        tw_x[x.org_num] = sum;
        tp_x[x.org_num] = sum;
    }

    for(auto x = new_name.rbegin(); x != new_name.rend(); x++){
        re_num ele = x.operator*();
        if (ele.new_num == size -1){continue;}

        float sum = float_inf;
        for (size_t y = 0; y < size; y++) {
            if (tx[ele.org_num][y] != float_inf and tp_x[y] - tx[ele.org_num][y] < sum){
                sum = tp_x[y] - tx[ele.org_num][y];
            }
        }
        tp_x[ele.org_num] = sum;
    }

    int last = 0;
    bool flag = false;
    for(auto& x :new_name){
        if (!flag){
            last = x.org_num;
            flag = true;
            continue;
        }
        if(abs(tw_x[x.org_num] - tp_x[x.org_num]) < 0.0001){
            path.push_back({last, x.org_num});
            last = x.org_num;
        }
        ans = tw_x[x.org_num];
    }




    return {path, ans};

}

int main() {
    int tc[10][10] = {
            {inf,2,  4,  1,   3,   inf, inf, 3,   7,   3  },
            {inf,inf,3,  1,   inf, inf, 5,   inf, inf, 2  },
            {inf,inf,inf,inf, 1,   2,   inf, inf, inf, inf},
            {inf,inf,1,  inf, inf, 4,   4,   inf, inf, inf},
            {inf,inf,inf,inf, inf, 3,   inf, 5,   inf, inf},
            {inf,inf,inf,inf, inf, inf, 3,   3,   4,   inf},
            {inf,inf,inf,inf, inf, inf, inf, inf, 2,   1  },
            {inf,inf,inf,inf, inf, inf, inf, inf, 1,   inf},
            {inf,inf,inf,inf, inf, inf, inf, inf, inf, 3  },
            {inf,inf,inf,inf, inf, inf, inf, inf, inf, inf},
    };

    int tm[10][10] = {
            {inf,3,  6,  1,   8,   inf, inf, 3,   8,   8  },
            {inf,inf,3,  2,   inf, inf, 5,   inf, inf, 2  },
            {inf,inf,inf,inf, 3,   2,   inf, inf, inf, inf},
            {inf,inf,1,  inf, inf, 4,   4,   inf, inf, inf},
            {inf,inf,inf,inf, inf, 7,   inf, 5,   inf, inf},
            {inf,inf,inf,inf, inf, inf, 4,   4,   4,   inf},
            {inf,inf,inf,inf, inf, inf, inf, inf, 2,   3  },
            {inf,inf,inf,inf, inf, inf, inf, inf, 3,   inf},
            {inf,inf,inf,inf, inf, inf, inf, inf, inf, 3  },
            {inf,inf,inf,inf, inf, inf, inf, inf, inf, inf},
    };

    int tp[10][10] = {
            {inf,9,  6,  15,  8,   inf, inf, 8,   10,  10 },
            {inf,inf,5,  3,   inf, inf, 5,   inf, inf, 3  },
            {inf,inf,inf,inf, 5,   2,   inf, inf, inf, inf},
            {inf,inf,2,  inf, inf, 7,   4,   inf, inf, inf},
            {inf,inf,inf,inf, inf, 7,   inf, 5,   inf, inf},
            {inf,inf,inf,inf, inf, inf, 4,   5,   5,   inf},
            {inf,inf,inf,inf, inf, inf, inf, inf, 7,   4  },
            {inf,inf,inf,inf, inf, inf, inf, inf, 3,   inf},
            {inf,inf,inf,inf, inf, inf, inf, inf, inf, 7  },
            {inf,inf,inf,inf, inf, inf, inf, inf, inf, inf},
    };
    auto ans1 = PERT(tc);
    std::cout << "minimalna dlugosc: "<< std::get<1>(ans1) << std::endl;

    for(auto ele : std::get<0>(ans1)){
        std::cout << ele.origin + 1 << " -> " << ele.destination + 1 << std::endl;
    }
    std::cout << std::endl;


    auto ans2 = PERT(tm);
    std::cout << "przewidywana dlugosc: "<< std::get<1>(ans2) << std::endl;

    for(auto ele : std::get<0>(ans2)){
        std::cout << ele.origin + 1 << " -> " << ele.destination + 1 << std::endl;
    }
    std::cout << std::endl;


    auto ans3 = PERT(tc, tm, tp);
    std::cout << "z prawdopodobienstwem 90% nie przekroczy: "<< std::get<1>(ans3) << std::endl;

    for(auto ele : std::get<0>(ans3)){
        std::cout << ele.origin + 1 << " -> " << ele.destination + 1 << std::endl;
    }
    std::cout << std::endl;


    auto ans4 = PERT(tp);
    std::cout << "maksymalna dlugosc: "<< std::get<1>(ans4) << std::endl;

    for(auto ele : std::get<0>(ans4)){
        std::cout << ele.origin + 1 << " -> " << ele.destination + 1 << std::endl;
    }
}