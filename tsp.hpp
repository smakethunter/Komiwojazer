//
// Wojciech Pełka 302895
//

#ifndef UNTITLED_TSP_H
#define UNTITLED_TSP_H

#include <utility>
#include <vector>
#include <map>
#include <iostream>
#include <functional>
#include <cmath>
#include <limits>
#include <iostream>
#include <vector>
#include <climits>
double get_forbidden_cost();
const double INF=get_forbidden_cost();

class TSP_cost_matrix{
private:
    int num_summits;
    int max_boud;
    std::vector<std::vector<double>> cost_matrix;
    std::vector<std::pair<int,int>> spath;
public:
    TSP_cost_matrix(std::vector<std::vector<double>> &m){
        cost_matrix=m;
        num_summits=std::size(cost_matrix);

    }
    double sum_row(int,int);
    double sum_col(int,int);
    std::vector<std::vector<double>> get_cmatrix(){ return  cost_matrix;}
    std::vector<std::pair<int,int>> get_spath(){return spath;}
    std::vector<double> find_min_row();
    std::vector<double> find_min_col();
    void reduce_row();
    void reduce_col();
    void show_matrix();
    void show_spath();
    std::pair<int,int>find_zero();
    bool if_zero_ew();
    void remove_ix_row_col(std::pair<int,int>);
    void set_as_forbidden(std::pair<int,int>);
    void sort_spath();
    std::vector<int> format_spath();

};

std::vector<int> tsp(std::vector<std::vector<double>> cost_matrix);










#endif //UNTITLED_TSP_H
