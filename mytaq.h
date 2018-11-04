#ifndef MYTAQ_H
#define MYTAQ_H
#include <iostream>
#include <ostream>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

#define NBL 3
#define NBC 3

int board[NBL][NBC];

#define MOVE_U 0
#define MOVE_D 1
#define MOVE_L 2
#define MOVE_R 3

typedef struct state state_t;
typedef std::vector<int> ivec_t;
typedef std::vector <state_t> svec_t; 
typedef svec_t::iterator svec_iter_t;
typedef ivec_t::iterator ivec_iter_t;
typedef std::unordered_map<std::string,int> hash_t;
typedef hash_t::iterator hash_iter_t; 

struct state{
  std::string state_hash;
  ivec_t state;
  int m;
  state_t *parent;
};


void init_board(void){
    for(int i = 0; i < NBL; ++i){
        for(int j = 0; j < NBC; j++)
        {
            board[i][j] = i * NBC + j + 1;
        }
        
    }
    
}

void print_board(void){
    
    for(int i = 0; i < NBL; i++)
    {
        for(int j = 0; j < NBC; j++)
        {
            if(board[i][j] == NBL*NBC) printf("* ");
            else 
            {
                printf("%d ", board[i][j]);
            }   
        }
        printf("\n");
    }
    printf("\n");
}

bool can_move_U(int _i, int _j){
    if(_i <= 0)
    {
     return false;
    }
    return true;
}

void move_U(int _i, int _j){
    board[_i][_j] = board[_i - 1][_j];
    board[_i - 1][_j] = NBL * NBC;
}

bool can_move_D(int _i, int _j){
    if(_i >= (NBL - 1))
    {
     return false;
    }
    return true;
}

void move_D(int _i, int _j){
    board[_i][_j] = board[_i + 1][_j];
    board[_i + 1][_j] = NBL * NBC;
}


bool can_move_L(int _i, int _j){
    if(_j <= 0)
    {
     return false;
    }
    return true;
}

void move_L(int _i, int _j){
    board[_i][_j] = board[_i][_j - 1];
    board[_i][_j - 1] = NBL * NBC;
}

bool can_move_R(int _i, int _j){
    if(_j >= (NBC - 1))
    {
     return false;
    }
    return true;
}

void move_R(int _i, int _j){
    board[_i][_j] = board[_i][_j + 1];
    board[_i][_j + 1] = NBL * NBC;
}


void set_next(int *_moves, int& _size, int& _line, int& _col){

    for(int i = 0; i < NBL; i++)
    {
        for(int j = 0; j < NBC; j++)
        {
            if(board[i][j] == NBL*NBC)
            {
                _line = i;
                _col = j;
                break;
            }
             
        }
     
    }

    _size = 0;
    if(can_move_U(_line, _col)){ _moves[_size]=MOVE_U; _size++;}
    if(can_move_D(_line, _col)){ _moves[_size]=MOVE_D; _size++;}
    if(can_move_L(_line, _col)){ _moves[_size]=MOVE_L; _size++;}
    if(can_move_R(_line, _col)){ _moves[_size]=MOVE_R; _size++;}
}


void play(int _move, int _line, int _col){
    if(_move == MOVE_U){move_U(_line, _col);}
    if(_move == MOVE_D){move_D(_line, _col);}
    if(_move == MOVE_L){move_L(_line, _col);}
    if(_move == MOVE_R){move_R(_line, _col);}
}

void unplay(int _move, int _line, int _col){
    if(_move == MOVE_U){move_D(_line - 1, _col);}
    if(_move == MOVE_D){move_U(_line + 1, _col);}
    if(_move == MOVE_L){move_R(_line, _col - 1);}
    if(_move == MOVE_R){move_L(_line, _col + 1);}
}

int rand_move(void){
    int next_moves[4];
    int next_size;
    int next_i_line;
    int next_i_col;
    set_next(next_moves, next_size, next_i_line, next_i_col);
    int r = ((int)rand())%next_size;
    play(next_moves[r], next_i_line, next_i_col);
    return next_moves[r];
}

bool final_position(){
    for(int i = 0; i < NBL; i++)
    {
        for(int j = 0; j < NBC; j++)
        {
            if(board[i][j] != i*NBC+j+1)
            {
                return false;
            }
            
        }
        
    }
    return true;
}


std::string mkH(){
    char strh[1024];
    strh[0] = '\0';
    for(int i = 0; i < NBL; i++)
    {
        for(int j = 0; j < NBC; j++)
        {
           char stre[16];
           sprintf(stre,"%d-", board[i][j]);
           strcat(strh,stre);  
        }
        
    }
    
    return std::string(strh);
}

std::string mkH_bfs(int m){
    char strh[1024];
    strh[0] = '\0';
    for(int i = 0; i < NBL; i++)
    {
        for(int j = 0; j < NBC; j++)
        {
           char stre[32];
           sprintf(stre,"%d-%d-", board[i][j],m);
           strcat(strh,stre);  
        }
        
    }
    
    return std::string(strh);
}


void getPos(int& _line, int& _col){
    for(int i = 0; i < NBL; i++)
    {
        for(int j = 0; j < NBC; j++)
        {
            if (board[i][j] == NBC * NBL){
                _line = i;
                _col = j;
                break;
            }
        }
        
    }
    
}

void set_board(ivec_t state){
    ivec_iter_t i = state.begin();
    int t[NBL*NBC];
    int s = 0;
    for(i = state.begin(), s = 0;i != state.end(); ++i,++s){
        t[s] = (*i);
    }
    int ii = 0, jj = 0;
    for (ii = 0; ii < NBL; ++ii){
        for (jj = 0; jj < NBC; ++jj){
            board[ii][jj] = t[ii * NBC + jj];
        }
    }
    
}

ivec_t get_board(void){
    ivec_t state = {};
    int t[NBL*NBC];
    int i = 0, j = 0;
    for (i = 0; i < NBL; ++i){
        for (j = 0; j < NBC; ++j){
            t[i * NBC + j] = board[i][j];
        }
    } 
    state = ivec_t(t,t+(NBL*NBC)); 
    return state;
}

#endif
