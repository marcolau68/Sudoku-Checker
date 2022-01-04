#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <vector>


// find the index of a number in a 2D sudoku
int twod_to_oned(int row, int col, int rowlen){
    return row*rowlen+col;
}


// find n in vector v and return index i, otherwise, return -1
int mfind(int n, const std::vector<int>& v){
        
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == n) {
            return i;
        }
    }
    
    return -1;
}


// check whether 1 to n exists in v
bool check_sequence(const std::vector<int>& v){
    
    for (int i = 1; i <= v.size();i++) {
        if (mfind(i, v) == -1) {
            return false;
        }
    }
    
    return true;
}


// returns the chosen row in a vector
void get_row(int r, const std::vector<int>& in, std::vector<int>& out){
    int num, rowlen = sqrt(in.size());
    
    for (int i = 0; i < rowlen; i++) {
        num = in[twod_to_oned(r, i, rowlen)];
        out.push_back(num);
    }
}


// returns the chosen column in a vector
void get_col(int c, const std::vector<int>& in, std::vector<int>& out){
    int num, rowlen = sqrt(in.size());
    
    for (int i = 0; i < rowlen; i++) {
        num = in[twod_to_oned(i, c, rowlen)];
        out.push_back(num);
    }
}


// returns the chosen subsquare in a vector
void get_subsq(int subs, const std::vector<int>& in, std::vector<int>& out){

    int side = sqrt(in.size()), num;
    int subside = sqrt(side), x = subs % subside, y = subs / subside;


    for (int i = y * subside; i < subside * (y + 1); i++) {
        for (int j = x * subside; j < subside * (x + 1); j++) {
            num = in[twod_to_oned(i, j, side)];
            out.push_back(num);
        }
    }
}


// function that determines wether the sudoku is valid or not
bool valid_sudoku(const std::vector<int>& g){
    int side = std::sqrt(g.size());
    std::vector<int> seq;

    // for each row...
    for(int i = 0; i < side; i++){
        seq.clear();
        get_row(i, g, seq);
        
        if(!check_sequence(seq)){
            return false;
        }
    }
    
    // for each column...
    for(int i = 0; i < side; i++){
        seq.clear();
        get_col(i, g, seq);
        
        if(!check_sequence(seq)){
            return false;
        }
    }
    
    // for each subsquare...
   for(int i = 0; i < side; i++){
       seq.clear();
       get_subsq(i, g, seq);
       
       if(!check_sequence(seq)) {
           return false;
       }
    }
    
    return true;
}


// Main loop
int main(){
    
    std::vector<int> s;
        
    std::string filename;
    
    std::cout << "please enter name of file containing the sudoku" << std::endl;
    std::cin >> filename;
    
    // Open and store the content in filename into vector s
    std::ifstream infile;
    infile.open(filename);
    
    if(!infile.is_open()){
        std::cout << "error, can't open input file" << std::endl;
        return EXIT_FAILURE;
    }
    
    int tmp;
    
    while(infile >> tmp){
        s.push_back(tmp);
    }
        
    int side = std::sqrt(s.size());
    
    // print out the 2D representation of vector s
    for(int i = 0; i < side; i++){
        for(int j = 0; j < side; j++){
            std::cout << s[twod_to_oned(i,j,side)] << " ";
        }
        std::cout << std::endl;
    }
        
    // check whether vector s is a valid sudoku
    bool valid = valid_sudoku(s);
    
    if(valid){
        std::cout << "valid" << std::endl;
    }
    else{
        std::cout << "not valid" << std::endl;
    }
    
}





