#include <cstdio>
#include <cstdlib>
#include <unordered_map>
#include "mytaq.h"

std::unordered_map<std::string, int> H;
int DLS_MAX_DEPTH = 30;
int *sol;
int sol_size;


void dls_solve(int _depth){
    if (_depth == DLS_MAX_DEPTH)return;
    int next_moves[4];
    int next_size;
    int next_start_line;
    int next_start_col;

    set_next(next_moves, next_size, next_start_line, next_start_col);
    for(int j = 0; j < next_size; j++)
    {
        play(next_moves[j], next_start_line, next_start_col);
        std::string strboard = mkH();
        std::unordered_map<std::string, int>::iterator ii = H.find(strboard);
        if(ii == H.end() || ii->second > _depth)
        {
            H[strboard] = _depth;
            sol[_depth] = next_moves[j];
            if (final_position()){sol_size = _depth+1; return;}
            dls_solve(_depth+1);
        }
        unplay(next_moves[j], next_start_line, next_start_col);
        if(sol_size != 0) break;
        
    }
    
}



int main(int argc, char const *argv[])
{
    sol_size = 0;
    sol = new int[DLS_MAX_DEPTH];
    int line, col;
    board[0][0] = 1;board[0][1] = 2;board[0][2] = 3;
    board[1][0] = 4;board[1][1] = 9;board[1][2] = 5;
    board[2][0] = 6;board[2][1] = 7;board[2][2] = 8;
 
    std::string strboard = mkH();
    H[strboard] = 0;
    
    dls_solve(0);
    
    board[0][0] = 1;board[0][1] = 2;board[0][2] = 3;
    board[1][0] = 4;board[1][1] = 9;board[1][2] = 5;
    board[2][0] = 6;board[2][1] = 7;board[2][2] = 8;
    if (sol_size != 0)
    {   
        std::string strings[] = {"UP","DOWN","LEFT","RIGHT"};
        cout << "Depth Limited Search\n";
        cout <<"La taille de la solution est: " << sol_size << "\n Sulution: ";
        for(int i = 0; i < sol_size; i++)
        {
            cout << strings[sol[i]] << "--";
        }
        cout << endl;
        print_board();
        for(int i = 0; i < sol_size; i++)
        {
            getPos(line,col);
            play(sol[i],line,col);
            print_board();

        }
        cout << endl;
    }else 
    {
        cout << "Aucune Solution n'est trouvé\n";
    }
    H.clear();
    
    return 0;
}
