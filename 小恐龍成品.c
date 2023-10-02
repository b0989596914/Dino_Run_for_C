#include <stdio.h>
#include<stdlib.h>
#include <windows.h>     //新的函式庫 
#include <conio.h>       //新的函式庫
#include<time.h>
#define canvas 50  //地圖的大小

//display-->把lowerlimit到upperlimit的內容印出(印地圖)
void display(char floor[],int lowerlimit,int upperlimit){ //lowerlimit-->開始印的index,upperlimit-->結束印的index
    int i; //變數
    for(i = lowerlimit;i<upperlimit;i++){
        printf("%c",floor[i]);
    }
}

void shiftLeft(char *floor){ //char floor[] 可代替    //地板動的公式 
    int i;
    for(i = 0;i<canvas-1;i++){  
        floor[i] = floor[i+1];  //每次往前複製一格 
    }
    floor[canvas-1] = '_'; //往前推之後的空格填上地板'_' 
}

void shiftLeftstar(char *floor){ //char floor[] 可代替    //地板動的公式 
    int i;
    for(i = 0;i<canvas-1;i++){  
        floor[i] = floor[i+1];  //每次往前複製一格 
    }
    floor[canvas-1] = ' '; //往前推之後的空格填上地板'_' 
}

void insertBarrier(char *floor,int n){ //產生障礙物的副函式
    floor[rand() % n + (canvas-n)] = 'X';
}
void star(char *floor,int n){ //產生星星的副函式
    floor[rand() % n + (canvas-n)] = '*';
}
int score=0;

int main (){
    int i;
    srand(time(0)); //為了亂障礙物的
    char floor1[canvas],floor2[canvas],floor3[canvas],floor4[canvas],floor5[canvas];  //floor1-->地板,floor2、floor3-->天空
    int playerDisplayPos = 6;
    int currentFloor = 1; //初始化開始的樓層-->代表小恐龍所在的樓層
    int sleepTime = 150 ;
    for (i=0 ; i<canvas ; i++){
        floor1[i] = '_'; //初始化地板
        floor2[i] = ' '; //初始化天空
        floor3[i] = ' '; //初始化天空
        floor4[i] = ' '; //初始化天空
        floor5[i] = ' '; //初始化天空
    }
    int runtime,runtime1;
    floor1[canvas-1]='X'; //加入障礙物
    floor4[canvas-1]='*'; //加入星星
    floor5[canvas-1]='*'; //加入星星
    int count=0;
    int win=1; //控制迴圈是否繼續
    while(win){
    	if(kbhit()&&getch()==32 && currentFloor==1){        //32=space   //kbhit-->是偵測有沒有按按鍵 ,getch-->從控制台讀取字符，但不顯示
    		currentFloor=2;   //將恐龍位置設定在2樓（即天空）
            runtime=4;  
        }
        // if(kbhit()&&getch()==32 && currentFloor==2){
        //     currentFloor=3;
        //     runtime=4;
        // }
        runtime--;
        // if(currentFloor==3 && runtime-- ==0){//每次判斷都會runtime--，直到變0就會設定currentFloor=1
        // 	currentFloor=1;
		// }
        if(currentFloor==2 && runtime ==0){//每次判斷都會runtime--，直到變0就會設定currentFloor=1
        	currentFloor=1;
		}
        if(score++%10==0){ //分數計算
        	insertBarrier(floor1,15);
            star(floor4,19);
            star(floor5,4);
        }
		printf("\t\t\t\t\t\tscore : %d \n",score);
        printf("\n\n\t    __\n\t"); //印出第五層 
        printf("| \\");  //印出太陽
        display(floor5,3,canvas);

        printf("\n\n\n\t"); //印出第四層
        display(floor4,0,canvas);

        printf("\n\n\n\t"); //印出第三層
        display(floor3,0,playerDisplayPos);

        printf("\n\n\n\t"); //印出第二層
        display(floor2,0,playerDisplayPos); //印出第二層
        if(currentFloor==2){
            printf("O"); //加入小恐龍
        } 
        else{
            // if(currentFloor==3){
            //     printf("O");
            // }
            printf(" "); 
        }
        display(floor2,playerDisplayPos+1,canvas);    //可寫可不寫，如果天空都是空格代表，不寫也看不出，如果你是滿天星可能還是寫一下吧
        
        printf("\n\t"); //印出第一層
        display(floor1,0,playerDisplayPos); //印出第一層,0-5(6是小恐龍的位置)

        if(currentFloor==1){ //第六格-->小恐龍(沒跳)
            printf("O");
            if(floor1[6]=='X'){ //恐龍遇到障礙物時-->過了(score++),沒過(break)
                win=0; //停止while迴圈
                system("cls"); //清空頁面 
                printf("\n\t\t-------------------");
                printf("\n\t\t| GAME OVER ! ! ! |\n\t\t| your score : %2d |\n",score);
                printf("\t\t-------------------\n");
                Sleep(10000);
            }
        }
        else{
            printf("%c",floor1[playerDisplayPos]);    //如果恐龍(跳了)不在這層，我們必須印路上原有的東西
            if(floor1[6]=='X'){ //恐龍遇到障礙物時-->過了(score++),沒過(break)
                score++;
                sleepTime--;
                if(sleepTime==0){  
                    system("cls"); //清空頁面 
                    printf("\n\t\t-------------------");
                    printf("\n\t\t| YOU   WIN ! ! ! |\n\t\t| your score : %d  |\n",score);
                    printf("\t\t-------------------\n");
                }
            }
        }
        
        display(floor1,playerDisplayPos+1,canvas);  //印出第一層,7-49的地板 
        printf("\n\n\n\t");
        Sleep(sleepTime); //1000==1秒，類似delay
        system("cls"); //清空頁面
                
        shiftLeft(floor1); //讓路動起來
        shiftLeftstar(floor4); //讓星星動起來
        shiftLeftstar(floor5); //讓星星動起來
        }
    return 0;
}
