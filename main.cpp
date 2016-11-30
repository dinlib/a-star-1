#include <iostream>
#include <set>
#include <array>
#include <queue>
#include <sstream>
#include <unordered_set>

#define matrix_dimension 4

#define board_size 16

int solution[matrix_dimension][matrix_dimension];


typedef struct state {
    state *parent;
    int steps;
    int heuristic;
    int board[matrix_dimension][matrix_dimension];

     bool operator<(const state& s) const {
        int x = steps + heuristic;
        int y = s.steps + s.heuristic;
        {return  y < x;}
    }

    bool operator==(const state& s) const {
        bool equal = true;
        for (int i = 0; i < matrix_dimension; ++i) {
            for (int j = 0; j < matrix_dimension; ++j) {
                if(board[i][j] != s.board[i][j])
                    equal = false;
            }
        }
        return equal && (steps <= s.steps);
    }

} state;


struct Hash {
    int operator() (const state &st) const {
        int result = 0;
        for (int i = 0; i < matrix_dimension; i++)
            for (int j = 0; j < matrix_dimension; j++)
                result = 31 * result + st.board[i][j];
        result = 31 * result + st.steps;
        result = 31 * result + st.heuristic;
        return result;
    }
};


std::priority_queue<state> open;
std::unordered_set<state, Hash> open_hash;
std::unordered_set<state, Hash> closed;


void heuristic_1(state *st){

    st->heuristic = 0;
    for(int i = 0; i < matrix_dimension; ++i) {
        for (int j = 0; j < matrix_dimension; ++j) {
            if (st->board[i][j] != solution[i][j]){
                st->heuristic++;
            }
        }
    }
}


void print_matrix(int matrix[matrix_dimension][matrix_dimension]){
    for (int i = 0; i < matrix_dimension; ++i) {
        for (int j = 0; j < matrix_dimension; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    std::cout << "\n";
}

void copy_board(int origin[matrix_dimension][matrix_dimension], int destiny[matrix_dimension][matrix_dimension]){
    for (int i = 0; i < matrix_dimension; ++i) {
        for (int j = 0; j < matrix_dimension; ++j) {
            destiny[i][j] = origin[i][j];
        }
    }
}

bool check_solution(int matrix[matrix_dimension][matrix_dimension]){
    for (int i = 0; i < matrix_dimension; ++i) {
        for (int j = 0; j < matrix_dimension; ++j) {
            if(matrix[i][j] != solution[i][j]){
                return false;
            }
        }
    }
    return true;
}

std::queue<state> generate_sucessors(state *st){
    std::queue<state> sucessors;
    for(int i = 0; i < matrix_dimension; i++){
        for (int j = 0; j < matrix_dimension; j++) {
           if(st->board[i][j] == 0){
               if(i - 1 >= 0){ //trocar com a peça de cima
                   state up;
                   up.parent = st;
                   up.steps = st->steps + 1;
                   copy_board(st->board, up.board);

                   int aux = up.board[i][j];
                   up.board[i][j] = up.board[i - 1][j];
                   up.board[i - 1][j] = aux;

                   heuristic_1(&up);
//                   print_matrix(up.board);
                   sucessors.push(up);
               }
               if(i + 1 <= matrix_dimension - 1){ //trocar com a peça de  baixo
                   state down;
                   down.parent = st;

                   down.steps = st->steps + 1;
                   copy_board(st->board, down.board);

                   int aux = down.board[i][j];
                   down.board[i][j] = down.board[i + 1][j];
                   down.board[i + 1][j] = aux;

                   heuristic_1(&down);
//                   print_matrix(down.board);
                   sucessors.push(down);
               }
               if(j - 1 >= 0){ //trocar com a peça da esquerda
                   state left;
                   left.parent = st;
                   left.steps = st->steps + 1;
                   copy_board(st->board, left.board);

                   int aux = left.board[i][j];
                   left.board[i][j] = left.board[i][j - 1];
                   left.board[i][j - 1] = aux;

                   heuristic_1(&left);
//                   print_matrix(left.board);
                   sucessors.push(left);
               }
               if(j + 1 <= matrix_dimension - 1){ //trocar com a peça da direita
                   state right;
                   right.parent = st;
                   right.steps = st->steps + 1;
                   copy_board(st->board, right.board);

                   int aux = right.board[i][j];
                   right.board[i][j] = right.board[i][j + 1];
                   right.board[i][j + 1] = aux;

                   heuristic_1(&right);
//                   print_matrix(right.board);
                   sucessors.push(right);
               }
           }
        }
    }
    return sucessors;
}

int main() {

    int n = 1;
    for(int i = 0; i < matrix_dimension; i++){
        for (int j = 0; j < matrix_dimension; j++) {
            solution[i][j] = n;
            n++;
        }
    }
    solution[matrix_dimension - 1][matrix_dimension - 1] = 0;

    state beggin_state;
    beggin_state.parent = NULL;
    beggin_state.steps = 0;
    int value;
    for(int i = 0; i < matrix_dimension; i++){
        for (int j = 0; j < matrix_dimension; j++) {
            scanf("%i", &value);
            beggin_state.board[i][j] = value;
        }
    }
    heuristic_1(&beggin_state);

//    std::cout << "Steps: " << beggin_state.steps << std::endl << "Heuristic: " << beggin_state.heuristic << std::endl << "Board:" << std::endl;
//    print_matrix(beggin_state.board);

    //A-Star Algorith begin
    open.push(beggin_state);
    open_hash.insert(beggin_state);
    while(!open.empty()){
//        std::cout << "openlist size: " << open.size() << std::endl;
        state st = open.top();
        open.pop();
        open_hash.erase(st);
//        std::cout << "CHOOSE STATE:" << std::endl;
//        std::cout << "Steps: " << st.steps << std::endl << "Heuristic: " << st.heuristic << std::endl << "Board:" << std::endl;
//        print_matrix(st.board);
        if(check_solution(st.board)){
//            std::cout << "FIND SOLUTION\n";
            std::cout << st.steps;
//            std::cout << "Board: \n\n";
//            print_matrix(st.board);
            break;
        }
        std::queue<state> sucessors = generate_sucessors(&st);
//        std::cout << "Sucessors" << std::endl;
        while(!sucessors.empty()) {
            state suc = sucessors.front();

//            std::cout << "Steps: " << suc.steps << std::endl << "Heuristic: " << suc.heuristic << std::endl << "Board:" << std::endl;
//            print_matrix(suc.board);

            std::unordered_set<state, Hash>::const_iterator closed_it = closed.find(suc);
            std::unordered_set<state, Hash>::const_iterator open_it = open_hash.find(suc);
            if(closed_it == closed.end() && open_it == open_hash.end()){
                open.push(suc);
                open_hash.insert(suc);
            }
            sucessors.pop();
        }
        closed.insert(st);
    }

    return 0;
}