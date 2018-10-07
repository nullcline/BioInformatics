#include <stdio.h>
#include <string.h>
#include <math.h>

void traceback_x(char x[],char y[],int i,int j,char trace[][211]);//1つ目の配列のアラインメントを出力する
void traceback_y(char x[],char y[],int i,int j,char trace[][211]);//2つ目の配列のアラインメントを出力する
int w(char x,char y);//スコア関数

int main(void){
  char x[] = "ATGGTTGGTTCGCTAAACTGCATCGTCGCTGTGTCCCAGAACATGGGCATCGGCAAGAACGGGGACCTGCCCTGGCCACCGCTCAGGAATGAATTCAGATATTTCCAGAGAATGACCACAACCTCTTCAGTAGAAGGTAAACAGAATCTGGTGATTATGGGTAAGAAGACCTGGTTCTCCATTCCTGAGAAGAATCGACCTTTAAAGGGTAGAATT";
  char y[] = "TAAAAACAAGCCACGAATTCGCCAGGCGGTTGGAGCCACCCGGCAATGTCGTAAACCACAGGCTTAAACTTCAACTTGGTAGCCTGTATCTTCCAGTGTGGGATTCATCGCCGCGGCACGAGCCAGTTCATCACAGCGTTCGTTTTCCGGGTGTCCGGCATGGCCTTTAACCCATTCCCATTTGATTTGATGCTGCCCCAATGCAGCATC";
  int len_x = strlen(x),len_y = strlen(y),i,j;
  int d = 7;//ギャップ開始ペナルティ
  int e = 1;//ギャップ伸長ペナルティ
  int score[len_x+1][len_y+1],D_x[len_x+1][len_y+1],D_y[len_x+1][len_y+1];//再帰式におけるD,D_x,D_y
  char trace[len_x+1][len_y+1];//trace[i,j]

  //score,D_x,D_y,traceの初期化
  D_x[0][0] = 0;
  D_y[0][0] = 0;
  score[0][0] = 0;
  trace[0][0] = ' ';
  for(i=1;i<len_x+1;i++){
    D_x[i][0] = -100;
    D_y[i][0] = -100;
    score[i][0] = - d - e*(i-1);
    trace[i][0] = 'u';
  }
  for(j=1;j<len_y+1;j++){
    D_x[0][j] = -100;
    D_y[0][j] = -100;
    score[0][j] = - d - e*(j-1);
    trace[0][j] = 'l';
  }

  //scoreの計算,traceの代入
  for(j=1;j<len_y+1;j++){
    for(i=1;i<len_x+1;i++){
      D_x[i][j] = fmax(score[i-1][j] - d,D_x[i-1][j] - e);
      D_y[i][j] = fmax(score[i][j-1] - d,D_y[i][j-1] - e);
      score[i][j] = fmax(score[i-1][j-1] + w(x[i-1],y[j-1]),fmax(D_x[i][j],D_y[i][j]));
      if(D_x[i][j] >= D_y[i][j]){
        trace[i][j] = 'u';
      }else{
        trace[i][j] = 'l';
      }
      if(score[i-1][j-1] + w(x[i-1],y[j-1]) >= fmax(D_x[i][j],D_y[i][j])){
        trace[i][j] = 'd';
      }
    }
  }

  //アラインメントの出力
  traceback_x(x,y,len_x,len_y,trace);
  printf("\n");
  traceback_y(x,y,len_x,len_y,trace);

  return 0;
}

int w(char x,char y){
  if(x == y){
    return 2;
  }else{
    return -2;
  }
}

void traceback_x(char x[],char y[],int i,int j,char trace[][211]){
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

void traceback_y(char x[],char y[],int i,int j,char trace[][211]){
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