#include <cstdio>
#include <cstdlib>
#include <unordered_map>
#include "mytaq.h"

std::unordered_map<std::string, int> H;
int IDS_MAX_DEPTH = 30;
int DLS_MAX_DEPTH = 0;
int *sol;
int sol_size;


void dls_bis_solve(int _depth){
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

        if(ii == H.end() || ii->second >= _depth)
        {
            H[strboard] = _depth;
            sol[_depth] = next_moves[j];
            if (final_position()){sol_size = _depth+1; return;}
            dls_bis_solve(_depth+1);
        }
        unplay(next_moves[j], next_start_line, next_start_col);
        if(sol_size != 0) break;
        
    }
    
}


void ids_solve(void){
  sol_size = 0;
  std::string strboard = mkH();
  H[strboard] = 0;
  for (int k = 0; k <  IDS_MAX_DEPTH; k++){
    DLS_MAX_DEPTH = k;
    dls_bis_solve(0);
    if (sol_size != 0) break;
  }
  H.clear();
}

int main(void){
  sol_size = 0;
  sol = new int[IDS_MAX_DEPTH];

  board[0][0] = 1;board[0][1] = 2;board[0][2] = 3;
  board[1][0] = 4;board[1][1] = 9;board[1][2] = 5;
  board[2][0] = 6;board[2][1] = 7;board[2][2] = 8;
  
  ids_solve();
  board[0][0] = 1;board[0][1] = 2;board[0][2] = 3;
  board[1][0] = 4;board[1][1] = 9;board[1][2] = 5;
  board[2][0] = 6;board[2][1] = 7;board[2][2] = 8;
  int line,col;

  if (sol_size != 0)
    {   
        std::string strings[] = {"UP","DOWN","LEFT","RIGHT"};
        cout << "Iterative Deepening Search\n";
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
  delete[] sol;
  return 0;
}


