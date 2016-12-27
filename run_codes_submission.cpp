#include <iostream>
#include <sstream>
#include <queue>
#include <tr1/unordered_map>
// #include <unordered_map>
#include <string.h>
#include <set>
#include <map>
#include <stdlib.h>

int solution[4][4] =  {
                        {1, 2, 3, 4},
                        {5, 6, 7, 8},
                        {9, 10, 11, 12},
                        {13, 14, 15, 0}
                      };

std::pair<int,int> correct_board_place[16] = { std::make_pair(3, 3), std::make_pair(0, 0), std::make_pair(0, 1), std::make_pair(0, 2),
                                               std::make_pair(0, 3), std::make_pair(1, 0), std::make_pair(1, 1), std::make_pair(1, 2),
                                               std::make_pair(1, 3), std::make_pair(2, 0), std::make_pair(2, 1), std::make_pair(2, 2),
                                               std::make_pair(2, 3), std::make_pair(3, 0), std::make_pair(3, 1), std::make_pair(3, 2)
                                            };


typedef struct state {
    state *parent;
    std::string hash_key;
    int f;
    int steps;
    int heuristic;
    int board[4][4];
} state;

struct state_cmp {
    bool operator() (const state& lhs, const state& rhs) const {
        if (lhs.f == rhs.f) return lhs.heuristic < rhs.heuristic;
        else return lhs.f < rhs.f;
    }
};

std::string generate_hash_key(int board [][4]){
    std::ostringstream hash_key;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if(board[i][j] < 10) hash_key << 0;
            hash_key << board[i][j];
        }
    }
    return hash_key.str();
}

typedef std::tr1::unordered_map<std::string, state> hash_table;
// typedef std::unordered_map<std::string, state> hash_table;
typedef std::multiset<state, state_cmp> mset;
typedef mset::iterator set_it;
typedef hash_table::iterator hash_it;


typedef struct OpenCustom{
    mset open_set;
    hash_table open_hash;

    void insert(state *st){
        open_set.insert(*st);
        open_hash[st->hash_key] = *st;
    }

    void remove(hash_it it){
        state st = it->second;
        std::string backup_key = it->first;
        open_set.erase(st);
        open_hash.erase(backup_key);
    }

    state extract_min(){
        set_it it = open_set.begin();
        state st = *it;
        std::string backup_key = it->hash_key;
        open_set.erase(it);
        open_hash.erase(backup_key);

        return st;
    }

    hash_it find(std::string hash_key){
        return open_hash.find(hash_key);
    }

    hash_it begin(){
        return open_hash.begin();
    }

    hash_it end(){
        return open_hash.end();
    }

    bool empty(){
        return open_hash.empty();
    }

} OpenCustom;

bool check_solution(int matrix[][4]){
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if(matrix[i][j] != solution[i][j]){
                return false;
            }
        }
    }
    return true;
}


int heuristic(int board[][4]){ //HEURISTIC 1
    int heuristic = 0;
    for(int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (board[i][j] != solution[i][j]){
                heuristic++;
            }
        }
    }
    return heuristic;
}

int heuristic_2(int board[][4]){ //HEURISTIC 2

    int heuristic = 0;
    int current;
    int last = board[0][1];
    for(int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            current = board[i][j];
            if(i != 0 || j != 0){
                if (current != last + 1 && (last != 0) ){
                    heuristic++;
                }
            }

            last = current;
        }
    }
    if(board[4 - 1][4 - 1] == 0) heuristic--;
    return heuristic;
}

int heuristic_3(int board[][4]){ //HEURISTIC 3
    int heuristic = 0;
    for(int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (board[i][j] != solution[i][j]){
                std::pair<int, int> correct_pos = correct_board_place[board[i][j]];
                heuristic += (abs(correct_pos.first - i) + abs(correct_pos.second - j));
            }
        }
    }
    return heuristic;
}

// int heuristic_4(int board[][4]){ //HEURISTIC 4
//     int h1 = heuristic_1(board);
//     int h2 = heuristic_2(board);
//     int h3 = heuristic_3(board);
//     int p1 = 0;
//     int p2 = 0;
//     int p3 = 0;
//     return p1*h1 + p2*h2 + p3*h3;
// }
//
// int heuristic_5(int board[][4]){ //HEURISTIC 5
//     int h1 = heuristic_1(board);
//     int h2 = heuristic_2(board);
//     int h3 = heuristic_3(board);
//     return std::max(h1, std::max(h2, h3));
// }


void copy_board(int origin[4][4], int destiny[4][4]){
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            destiny[i][j] = origin[i][j];
        }
    }
}


std::queue<state> generate_sucessors(state st){
    std::queue<state> sucessors;
    for(int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++) {
           if(st.board[i][j] == 0){
               if(i - 1 >= 0){ //trocar com a peça de cima
                   state up;
                   up.parent = &st;
                   up.steps = st.steps + 1;
                   copy_board(st.board, up.board);

                   int aux = up.board[i][j];
                   up.board[i][j] = up.board[i - 1][j];
                   up.board[i - 1][j] = aux;

                   up.heuristic = heuristic(up.board);
                   up.f = up.steps + up.heuristic;
                   up.hash_key = generate_hash_key(up.board);
                   sucessors.push(up);
               }
               if(i + 1 <= 4 - 1){ //trocar com a peça de  baixo
                   state down;
                   down.parent = &st;

                   down.steps = st.steps + 1;
                   copy_board(st.board, down.board);

                   int aux = down.board[i][j];
                   down.board[i][j] = down.board[i + 1][j];
                   down.board[i + 1][j] = aux;

                   down.heuristic = heuristic(down.board);
                   down.f = down.steps + down.heuristic;
                   down.hash_key = generate_hash_key(down.board);
                   sucessors.push(down);
               }
               if(j - 1 >= 0){ //trocar com a peça da esquerda
                   state left;
                   left.parent = &st;
                   left.steps = st.steps + 1;
                   copy_board(st.board, left.board);

                   int aux = left.board[i][j];
                   left.board[i][j] = left.board[i][j - 1];
                   left.board[i][j - 1] = aux;

                   left.heuristic = heuristic(left.board);
                   left.f = left.steps + left.heuristic;
                   left.hash_key = generate_hash_key(left.board);
                   sucessors.push(left);
               }
               if(j + 1 <= 4 - 1){ //trocar com a peça da direita
                   state right;
                   right.parent = &st;
                   right.steps = st.steps + 1;
                   copy_board(st.board, right.board);

                   int aux = right.board[i][j];
                   right.board[i][j] = right.board[i][j + 1];
                   right.board[i][j + 1] = aux;

                   right.heuristic = heuristic(right.board);
                   right.f = right.steps + right.heuristic;
                   right.hash_key = generate_hash_key(right.board);
                   sucessors.push(right);
               }
           }
        }
    }
    return sucessors;
}

int a_star(int board[][4]){
    state begin_state;
    begin_state.parent = NULL;
    begin_state.steps = 0;
    for(int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++) {
            begin_state.board[i][j] = board[i][j];
        }
    }
    begin_state.heuristic = heuristic(begin_state.board);
    begin_state.f = begin_state.heuristic + begin_state.steps;
    begin_state.hash_key = generate_hash_key(begin_state.board);

    OpenCustom open;
    hash_table closed;

    open.insert(&begin_state);
    while(!open.empty()){
        state st = open.extract_min();
        closed[st.hash_key] = st;

        if(check_solution(st.board)){
            return st.steps;
        }

        std::queue<state> sucessors = generate_sucessors(st);

        while(!sucessors.empty()) {
            state suc = sucessors.front();
            hash_it open_it = open.find(suc.hash_key);
            hash_it closed_it = closed.find(suc.hash_key);
            if(open_it != open.end()){
                if(suc.steps < open_it->second.steps){
                    open.remove(open_it);
                    open.insert(&suc);
                }
            }
            else if(closed_it != closed.end()){
                if(suc.steps < closed_it->second.steps){
                    closed.erase(closed_it->first);
                    open.insert(&suc);
                }
            }
            else{
                open.insert(&suc);
            }
            sucessors.pop();
        }
    }
    return 0;
}


int main(int argc, char *argv[]) {
    int initial_board[4][4];
    int count = 1;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
          initial_board[i][j] = atoi(argv[count]);
          count++;
          // std::cin >> initial_board[i][j];
        }
    }
    int solution = a_star(initial_board);
    std::cout << solution << std::endl;
    return 0;
}
