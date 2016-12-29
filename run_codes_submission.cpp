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

std::string strsolution = "01020304050607080910111213141500";

std::pair<int,int> correct_board_place[16] = {
    std::make_pair(3, 3), std::make_pair(0, 0), std::make_pair(0, 1), std::make_pair(0, 2),
    std::make_pair(0, 3), std::make_pair(1, 0), std::make_pair(1, 1), std::make_pair(1, 2),
    std::make_pair(1, 3), std::make_pair(2, 0), std::make_pair(2, 1), std::make_pair(2, 2),
    std::make_pair(2, 3), std::make_pair(3, 0), std::make_pair(3, 1), std::make_pair(3, 2)
};

std::pair<int,int> board_places[16] = {
    std::make_pair(0, 0), std::make_pair(0, 1), std::make_pair(0, 2), std::make_pair(0, 3),
    std::make_pair(1, 0), std::make_pair(1, 1), std::make_pair(1, 2), std::make_pair(1, 3),
    std::make_pair(2, 0), std::make_pair(2, 1), std::make_pair(2, 2), std::make_pair(2, 3),
    std::make_pair(3, 0), std::make_pair(3, 1), std::make_pair(3, 2), std::make_pair(3, 3)
};

typedef struct state {
    // state *parent;
    std::string hash_key;
    int f;
    int steps;
    int heuristic;
    int board[4][4];
} state;

struct state_cmp {
    bool operator() (const state& lhs, const state& rhs) const {
        if (lhs.f == rhs.f) return rhs.heuristic < lhs.heuristic;
        else return lhs.f < rhs.f;
    }
};

std::string generate_hash_key(int board [][4]){
    std::ostringstream hash_key;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
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
        return open_set.empty();
    }

    int size(){
        return open_set.size();
    }

} OpenCustom;

//CHECK 15-PUZZLE SOLUTION
bool check_solution(std::string board){
    // for (int i = 0; i < 4; i++) {
    //     for (int j = 0; j < 4; j++) {
    //         if(matrix[i][j] != solution[i][j]){
    //             return false;
    //         }
    //     }
    // }
    // return true;
    if(board.compare(strsolution) == 0) return true;
    else return false;
}

//HEURISTICS
int heuristic_1(int board[][4]){ //HEURISTIC 1
    int heuristic = 0;
    for(int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] != solution[i][j]){
                heuristic++;
            }
        }
    }
    return heuristic;
}

int heuristic_2(int board[][4]){ //HEURISTIC 2
    int heuristic = 0;
    for(int i = 1; i < 16; i++) {
        std::pair<int, int> last = board_places[i - 1];
        std::pair<int, int> current = board_places[i];
        if(board[current.first][current.second] != board[last.first][last.second] + 1)
        if(board[last.first][last.second] != 0)
        heuristic++;
    }
    if(board[3][3] == 0) heuristic--;
    return heuristic;
}

int manhattan_distance(int index, int r, int c){
    std::pair<int, int> correct_pos = correct_board_place[index];
    int manhattan_distance = (abs(correct_pos.first - r) + abs(correct_pos.second - c));
    return manhattan_distance;
}

int heuristic(int board[][4]){ //HEURISTIC 3
    int heuristic = 0;
    for(int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if((board[i][j] != solution[i][j]) ){
                if(board[i][j] != 0){
                    heuristic += manhattan_distance(board[i][j], i, j);
                }
            }
        }
    }
    return heuristic;
}

// int heuristic(int board[][4]){ //HEURISTIC 4
//     int h1 = heuristic_1(board);
//     int h2 = heuristic_2(board);
//     int h3 = heuristic_3(board);
//     int p1 = 0;
//     int p2 = 0;
//     int p3 = 1;
//     return p1*h1 + p2*h2 + p3*h3;
// }

// int heuristic_5(int board[][4]){ //HEURISTIC 5
//     int h1 = heuristic_1(board);
//     int h2 = heuristic_2(board);
//     int h3 = heuristic_3(board);
//     return std::max(h1, std::max(h2, h3));
// }


void copy_board(int origin[][4], int destiny[][4]){
    // for (int i = 0; i < 4; i++) {
    //     for (int j = 0; j < 4; j++) {
    //         destiny[i][j] = origin[i][j];
    //     }
    // }
     memcpy(destiny, origin, 4*4*sizeof(int));
}


std::queue<state> generate_sucessors(state st){
    std::queue<state> sucessors;
    for(int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++) {
            if(st.board[i][j] == 0){
                if(i != 0){ //trocar com a peça de cima
                    state up;
                    // up.parent = &st;
                    up.steps = st.steps + 1;
                    copy_board(st.board, up.board);

                    int aux = up.board[i][j];
                    up.board[i][j] = up.board[i - 1][j];
                    up.board[i - 1][j] = aux;

                    // up.heuristic = heuristic(up.board);
                    // up.f = up.steps + up.heuristic;
                    up.hash_key = generate_hash_key(up.board);
                    sucessors.push(up);
                }
                if(i != 3){ //trocar com a peça de  baixo
                    state down;
                    // down.parent = &st;

                    down.steps = st.steps + 1;
                    copy_board(st.board, down.board);

                    int aux = down.board[i][j];
                    down.board[i][j] = down.board[i + 1][j];
                    down.board[i + 1][j] = aux;

                    // down.heuristic = heuristic(down.board);
                    // down.f = down.steps + down.heuristic;
                    down.hash_key = generate_hash_key(down.board);
                    sucessors.push(down);
                }
                if(j != 0){ //trocar com a peça da esquerda
                    state left;
                    // left.parent = &st;
                    left.steps = st.steps + 1;
                    copy_board(st.board, left.board);

                    int aux = left.board[i][j];
                    left.board[i][j] = left.board[i][j - 1];
                    left.board[i][j - 1] = aux;

                    // left.heuristic = heuristic(left.board);
                    // left.f = left.steps + left.heuristic;
                    left.hash_key = generate_hash_key(left.board);
                    sucessors.push(left);
                }
                if(j != 3){ //trocar com a peça da direita
                    state right;
                    // right.parent = &st;
                    right.steps = st.steps + 1;
                    copy_board(st.board, right.board);

                    int aux = right.board[i][j];
                    right.board[i][j] = right.board[i][j + 1];
                    right.board[i][j + 1] = aux;

                    // right.heuristic = heuristic(right.board);
                    // right.f = right.steps + right.heuristic;
                    right.hash_key = generate_hash_key(right.board);
                    sucessors.push(right);
                }
            }
        }
    }
    return sucessors;
}

int a_star(int board[][4]){

    //BEGIN STATE
    state begin_state;
    // begin_state.parent = NULL;
    begin_state.steps = 0;
    copy_board(board, begin_state.board);
    begin_state.heuristic = heuristic(begin_state.board);
    begin_state.f = begin_state.heuristic + begin_state.steps;
    begin_state.hash_key = generate_hash_key(begin_state.board);

    //OPEN AND CLOSED SET
    OpenCustom open;
    hash_table closed;

    // int phase = 0;

    //A-STAR ALGORITHM BEGIN
    open.insert(&begin_state);
    while(!open.empty()){

        state st = open.extract_min();
        closed[st.hash_key] = st;

        if(check_solution(st.hash_key)){
            return st.steps;
        }

        std::queue<state> sucessors = generate_sucessors(st);

        while(!sucessors.empty()) {
            state suc = sucessors.front();
            hash_it open_it = open.find(suc.hash_key);
            hash_it closed_it = closed.find(suc.hash_key);
            bool isInOpen = (open_it != open.end());
            bool isInClosed = (closed_it != closed.end());

            if(isInClosed){
                if(suc.steps < closed_it->second.steps){
                    closed.erase(closed_it);
                    suc.heuristic = heuristic(suc.board);
                    suc.f = suc.steps + suc.heuristic;
                    open.insert(&suc);
                }
            }
            else if(isInOpen){
                if(suc.steps < open_it->second.steps){
                    open.remove(open_it);
                    suc.heuristic = heuristic(suc.board);
                    suc.f = suc.steps + suc.heuristic;
                    open.insert(&suc);
                }
            }
            else{
                suc.heuristic = heuristic(suc.board);
                suc.f = suc.steps + suc.heuristic;
                open.insert(&suc);
            }

            // if(isInOpen && (suc.steps < open_it->second.steps)){
            //     open.remove(open_it);
            // }
            // if(isInClosed && (suc.steps < closed_it->second.steps)){
            //     closed.erase(closed_it);
            // }
            // if(!(isInOpen || isInClosed)){
            //     suc.heuristic = heuristic(suc.board);
            //     suc.f = suc.steps + suc.heuristic;
            //     open.insert(&suc);
            // }

            // if(!isInClosed){
            //     if(isInOpen){
            //         if(suc.steps < open_it->second.steps){
            //             open.remove(open_it);
            //             suc.heuristic = heuristic(suc.board);
            //             suc.f = suc.steps + suc.heuristic;
            //             open.insert(&suc);
            //         }
            //     }
            //     else {
            //         suc.heuristic = heuristic(suc.board);
            //         suc.f = suc.steps + suc.heuristic;
            //         open.insert(&suc);
            //     }
            // }


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
