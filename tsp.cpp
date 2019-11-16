//
// Wojciech Pełka 302895
//
#include "tsp.hpp"
#include <sstream>

std::vector<double> TSP_cost_matrix::find_min_row() {
    std::vector<double> min_row;

    for (const auto& i: cost_matrix){
        double temp_cost=200;
        for(const auto& val: i){
            if(val<temp_cost){
                temp_cost=val;
            }
        }
        min_row.push_back(temp_cost);
    }
    return min_row;
}

std::vector<double> TSP_cost_matrix::find_min_col() {
    std::vector<double> min_col;
    for(int i=0;i< int(std::size(cost_matrix));i++) {
        double temp_cost=200;
        for(int j=0;j< int(std::size(cost_matrix));j++){
            if(cost_matrix[j][i]<temp_cost)
                temp_cost=cost_matrix[j][i];

        }
        min_col.push_back(temp_cost);
    }
   return min_col;
}

void TSP_cost_matrix::reduce_row() {
    std::vector<double> v_del=find_min_row();
    for(int i=0;i< int(std::size(cost_matrix));i++) {
        for(int j=0;j< int(std::size(cost_matrix));j++){
            cost_matrix[i][j]=cost_matrix[i][j]-v_del[i];
        }
    }

}
void TSP_cost_matrix::reduce_col() {
    std::vector<double> v_del=find_min_col();
    for(int i=0;i< int(std::size(cost_matrix));i++) {
        for(int j=0;j< int(std::size(cost_matrix));j++){
            cost_matrix[i][j]=cost_matrix[i][j]-v_del[j];
        }
    }


}

void TSP_cost_matrix::show_matrix() {
    for(int i=0;i< int(std::size(cost_matrix));i++) {
        for(int j=0;j< int(std::size(cost_matrix));j++){

            printf("%3.lf ,", cost_matrix[i][j] );
        }
        std::cout<<std::endl;
    }
std::cout<<std::endl;
}

std::pair<int,int>TSP_cost_matrix::find_zero() {
    std::vector<std::pair<int, int>> pairs;
    for (int i = 0; i < int(std::size(cost_matrix)); i++) {
        for (int j = 0; j < int(std::size(cost_matrix)); j++) {
            if (cost_matrix[i][j]==0){
                pairs.emplace_back(std::make_pair(i,j));

            }
        }
    }
    int a;

    if(int(std::size(pairs))==3) {
        std::pair<int, int> p1 = pairs[0];
        std::pair<int, int> p2 = pairs[1];
        std::pair<int, int> p3 = pairs[2];
        if ((std::get<0>(p1) == std::get<0>(p2) && std::get<1>(p1) == std::get<1>(p3)) ||
            (std::get<0>(p1) == std::get<0>(p3) && std::get<1>(p1) == std::get<1>(p2)))
        {
            a=1;
        }
        else if((std::get<0>(p2) == std::get<0>(p1) && std::get<1>(p2) == std::get<1>(p3)) ||
                (std::get<0>(p2) == std::get<0>(p3) && std::get<1>(p2) == std::get<1>(p1))){
            a=0;
        }
        else if((std::get<0>(p3) == std::get<0>(p2) && std::get<1>(p3) == std::get<1>(p1)) ||
                (std::get<0>(p3) == std::get<0>(p1) && std::get<1>(p3) == std::get<1>(p2))){
            a=0;
        }
        else{
            a=0;
        }
    }

    else{

            a = 0;
        }

    std::pair<std::pair<int,int>,double> low_cost=std::make_pair(pairs[a],sum_row(std::get<0>(pairs[a]),std::get<1>(pairs[a]))+sum_col(std::get<0>(pairs[a]),std::get<1>(pairs[a])));
    for (int pid=0;pid<int(std::size(pairs));pid++) {

        if(sum_row(std::get<0>(pairs[pid]),std::get<1>(pairs[pid])) + sum_col(std::get<0>(pairs[pid]),std::get<1>(pairs[pid])) > std::get<1>(low_cost)){

            low_cost=std::make_pair(pairs[pid],sum_row(std::get<0>(pairs[pid]),std::get<1>(pairs[pid]))+sum_col(std::get<0>(pairs[pid]),std::get<1>(pairs[pid])));

        }



    }
    return std::get<0>(low_cost);
}

bool TSP_cost_matrix::if_zero_ew() {
    bool in_row;
    for (int i = 0; i < int(std::size(cost_matrix)); i++) {
        for (int j = 0; j < int(std::size(cost_matrix)); j++) {
            if (cost_matrix[i][j]==0){
                in_row=true;
            }
           if (!in_row){
               return false;
           }
        }
    }
    bool in_col;
    for (int i = 0; i < int(std::size(cost_matrix)); i++) {
        for (int j = 0; j < int(std::size(cost_matrix)); j++) {
            if (cost_matrix[j][1] == 0) {
                in_col = true;
            }
        }
    }
    if(!in_col){return false;}
    return true;
}

void TSP_cost_matrix::remove_ix_row_col(std::pair<int,int>idx) {
    std::vector<std::vector<double>> new_matrix;
    //cost_matrix[std::get<1>(idx)][std::get<0>(idx)]=INF;
    set_as_forbidden(idx);
    for(int i=0;i<int(std::size(cost_matrix));i++){
        std::vector<double> n_row;
        if (i!=std::get<0>(idx)){
            for(int j=0;j<int(std::size(cost_matrix));j++){
                if(j!=std::get<1>(idx)){
                    n_row.push_back(cost_matrix[i][j]);
                }
                else{

                    n_row.push_back(INF);
                }
            }

        }
        else{
            for(int j=0;j<int(std::size(cost_matrix));j++){
                n_row.push_back(INF);
            }

        }

    new_matrix.push_back(n_row);
    }

    spath.push_back(idx);
    cost_matrix=new_matrix;

}

void TSP_cost_matrix::show_spath() {
    for (const auto& i: spath){

        std::cout<<std::get<0>(i)<<","<<std::get<1>(i)<<" -> ";


    }
std::cout<<std::endl;
}

void TSP_cost_matrix::set_as_forbidden(std::pair<int, int> p) {
    cost_matrix[std::get<1>(p)][std::get<0>(p)]=INF;

}

void TSP_cost_matrix::sort_spath() {

    for (int j=0;j<int(std::size(spath));j++) {

        for (int i = j+1; i < int(std::size(spath)); i++) {

            if (std::get<1>(spath[j]) == std::get<0>(spath[i])) {
                std::pair<int,int> temp_pair=spath[i];
                spath[i]=spath[j+1];
                spath[j+1]=temp_pair;

            }
        }
    }

}

std::vector<int> TSP_cost_matrix::format_spath() {
    std::vector<int> ans ;
    int last=std::get<0>(spath[0])+1;
    for(const auto& i: spath){
        ans.push_back(std::get<0>(i)+1);
    }
    ans.push_back(last);


    return ans;
}

double TSP_cost_matrix::sum_row(int r ,int c) {
    double temp=200;
    for(int i = 0; i<int(std::size(cost_matrix));i++){
        if(i!=c) {
            if (cost_matrix[r][i] < temp) {
                temp = cost_matrix[r][i];
            }
        }
    }

    return temp;
}

double TSP_cost_matrix::sum_col(int r ,int c) {
    double temp=200;
    for(int i = 0; i<int(std::size(cost_matrix));i++) {
        if (i != r) {
            if (cost_matrix[i][c] < temp) {
                temp = cost_matrix[i][c];
            }
        }
    }

    return temp;
}

double get_forbidden_cost(){

    return std::nan("NAN");
}

std::vector<int> tsp( std::vector<std::vector<double>> cost_matrix){
    TSP_cost_matrix M (cost_matrix);
    for (int i=0;i<int(std::size(M.get_cmatrix()));i++) {


     if(!M.if_zero_ew()) {
         M.reduce_row();

         M.reduce_col();

     }

        M.remove_ix_row_col(M.find_zero());

    }
    M.sort_spath();
    return M.format_spath();


}
