#include <stdio.h>
#include <string.h>
#include <math.h>

#define X_width 8
#define Y_width 8
#define epsilon 0.95
#define gamma 0.9

enum Direction {E,W,S,N};

void traceback_x(char x[],char y[],int i,int j,char trace[][7]);
void traceback_y(char x[],char y[],int i,int j,char trace[][7]);
int w(char x,char y);

int main(void){
  enum Direction direction;
  int t = 0;
  double Q[X_width][Y_width][4];
  int map[X_width][Y_width] = {
    {1,1,1,1,1,0,1,1},
    {1,1,1,1,1,0,1,1},
    {1,1,0,1,1,1,1,1},
    {1,1,0,1,1,1,1,1},
    {1,1,0,1,1,0,0,0},
    {1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1}
  };
  int start_x = 0,stat_y = 4,goal_x = 7,goal_y = 7;
  int p_x = start_x,p_y = start_y;
  double reward = 1,penalty = 0.1;

  for(int i=0;i<X_width;i++){
    for(int j=0;j<Y_width;j++){
      for(int k=0;k<4;k++){
        Q[i][j][k] = 0;
      }
    }
  }

  return 0;
}

int w(char x,char y){
  if(x == y){
    return 2;
  }else{
    return -2;
  }
}

void traceback_x(char x[],char y[],int i,int j,char trace[][7]){
  if(i == 0 && j == 0){
    printf("array1: ");
  }else if(trace[i][j] == 'd'){
    traceback_x(x,y,i-1,j-1,trace);
    printf("%c",x[i-1]);
  }else if(trace[i][j] == 'u'){
    traceback_x(x,y,i-1,j,trace);
    printf("%c",x[i-1]);
  }else if(trace[i][j] == 'l'){
    traceback_x(x,y,i,j-1,trace);
    printf("-");
  }
}

void traceback_y(char x[],char y[],int i,int j,char trace[][7]){
  if(i == 0 && j == 0){
    printf("array2: ");
  }else if(trace[i][j] == 'd'){
    traceback_y(x,y,i-1,j-1,trace);
    printf("%c",y[j-1]);
  }else if(trace[i][j] == 'u'){
    traceback_y(x,y,i-1,j,trace);
    printf("-");
  }else if(trace[i][j] == 'l'){
    traceback_y(x,y,i,j-1,trace);
    printf("%c",y[j-1]);
  }
}