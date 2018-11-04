#include "mytaq.h"

void print_state(ivec_t state){
    ivec_iter_t i = state.begin();
    for (; i != state.end(); ++i)
        cout << (*i) << " ";
    cout << endl;    
}

int BFS_MAX_DEPTH = 30;
int *sol;
int sol_size = 0; 

state_t fin;

hash_t H;
svec_t initial;
svec_t nexts;
svec_t evolution;


void bfs_solve(svec_t initial, int _depth){

    int next_line;
    int next_col;
    int next_size;
    int next_moves[4];
    state_t state;
    if (_depth == BFS_MAX_DEPTH)
      return;

    nexts.clear();
    svec_iter_t s = initial.begin();
    for(;s != initial.end(); ++s){
        set_board((*s).state);
        set_next(next_moves,next_size,next_line,next_col);
        
        for (int i = 0; i < next_size; ++i){
            play(next_moves[i],next_line, next_col);
            state.state_hash = mkH_bfs(next_moves[i]);
            state.state = get_board();
            state.m = next_moves[i];
            state.parent = &(*s);
            nexts.push_back(state);
            unplay(next_moves[i],next_line,next_col);
        }      
    }
    evolution.clear();
    svec_iter_t n = nexts.begin();

    for(; n != nexts.end(); ++n){
        hash_iter_t ii = H.find((*n).state_hash);
        
        if (ii == H.end() || ii->second >= _depth){
            H[(*n).state_hash] = _depth;
            set_board((*n).state);
            if (final_position()){
                fin = (*n);
                sol_size = _depth + 1;
                return;
            }
            evolution.push_back(*n);
        }
        
    }
    bfs_solve(evolution, _depth + 1);       
    if (sol_size > 0)return;
}


 
int main(int argc, char const *argv[])
{
    sol_size = 0;
    sol = new int[BFS_MAX_DEPTH];

    board[0][0] = 1;board[0][1] = 2;board[0][2] = 3;
    board[1][0] = 4;board[1][1] = 9;board[1][2] = 5;
    board[2][0] = 6;board[2][1] = 7;board[2][2] = 8;
  
    state_t state = {};
    state.state = get_board();
    state.state_hash = mkH();
    state.m = 0;
    state.parent = NULL;
    initial.push_back(state);

    bfs_solve(initial, 0);
    state_t *n = &fin;
    int d = sol_size;
    while(n->parent != NULL){
        sol[d--] = n->m;
        n = n->parent;
    }
    cout << endl;
    if (sol_size != 0)
    {   
        std::string strings[] = {"UP","DOWN","LEFT","RIGHT"};
        cout << "Breadth First Search\n";
        cout <<"La taille de la solution est: " << sol_size << "\n Sulution: ";
        for(int i = 1; i < sol_size+1; i++)
        {
            cout << strings[sol[i]] << "--";
        }
        cout << endl;
    
        set_board(state.state);
        print_board();
        int _line = 0,_col = 0;
        for (int i = 1; i < sol_size+1; i++){
            getPos(_line,_col);
            play(sol[i],_line,_col);
            print_board();
        }
        cout << endl;
    }
    else
    {
        cout << "Aucune Solution n'est trouvé\n";
    }
    cout << endl;
    H.clear();  
    delete[] sol;
    initial.clear();
    evolution.clear();
    nexts.clear();    
    return 0;
}

