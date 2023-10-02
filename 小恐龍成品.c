#include <stdio.h>
#include<stdlib.h>
#include <windows.h>     //�s���禡�w 
#include <conio.h>       //�s���禡�w
#include<time.h>
#define canvas 50  //�a�Ϫ��j�p

//display-->��lowerlimit��upperlimit�����e�L�X(�L�a��)
void display(char floor[],int lowerlimit,int upperlimit){ //lowerlimit-->�}�l�L��index,upperlimit-->�����L��index
    int i; //�ܼ�
    for(i = lowerlimit;i<upperlimit;i++){
        printf("%c",floor[i]);
    }
}

void shiftLeft(char *floor){ //char floor[] �i�N��    //�a�O�ʪ����� 
    int i;
    for(i = 0;i<canvas-1;i++){  
        floor[i] = floor[i+1];  //�C�����e�ƻs�@�� 
    }
    floor[canvas-1] = '_'; //���e�����᪺�Ů��W�a�O'_' 
}

void shiftLeftstar(char *floor){ //char floor[] �i�N��    //�a�O�ʪ����� 
    int i;
    for(i = 0;i<canvas-1;i++){  
        floor[i] = floor[i+1];  //�C�����e�ƻs�@�� 
    }
    floor[canvas-1] = ' '; //���e�����᪺�Ů��W�a�O'_' 
}

void insertBarrier(char *floor,int n){ //���ͻ�ê�����ƨ禡
    floor[rand() % n + (canvas-n)] = 'X';
}
void star(char *floor,int n){ //���ͬP�P���ƨ禡
    floor[rand() % n + (canvas-n)] = '*';
}
int score=0;

int main (){
    int i;
    srand(time(0)); //���F�û�ê����
    char floor1[canvas],floor2[canvas],floor3[canvas],floor4[canvas],floor5[canvas];  //floor1-->�a�O,floor2�Bfloor3-->�Ѫ�
    int playerDisplayPos = 6;
    int currentFloor = 1; //��l�ƶ}�l���Ӽh-->�N��p���s�Ҧb���Ӽh
    int sleepTime = 150 ;
    for (i=0 ; i<canvas ; i++){
        floor1[i] = '_'; //��l�Ʀa�O
        floor2[i] = ' '; //��l�ƤѪ�
        floor3[i] = ' '; //��l�ƤѪ�
        floor4[i] = ' '; //��l�ƤѪ�
        floor5[i] = ' '; //��l�ƤѪ�
    }
    int runtime,runtime1;
    floor1[canvas-1]='X'; //�[�J��ê��
    floor4[canvas-1]='*'; //�[�J�P�P
    floor5[canvas-1]='*'; //�[�J�P�P
    int count=0;
    int win=1; //����j��O�_�~��
    while(win){
    	if(kbhit()&&getch()==32 && currentFloor==1){        //32=space   //kbhit-->�O�������S�������� ,getch-->�q����xŪ���r�šA�������
    		currentFloor=2;   //�N���s��m�]�w�b2�ӡ]�Y�Ѫš^
            runtime=4;  
        }
        // if(kbhit()&&getch()==32 && currentFloor==2){
        //     currentFloor=3;
        //     runtime=4;
        // }
        runtime--;
        // if(currentFloor==3 && runtime-- ==0){//�C���P�_���|runtime--�A������0�N�|�]�wcurrentFloor=1
        // 	currentFloor=1;
		// }
        if(currentFloor==2 && runtime ==0){//�C���P�_���|runtime--�A������0�N�|�]�wcurrentFloor=1
        	currentFloor=1;
		}
        if(score++%10==0){ //���ƭp��
        	insertBarrier(floor1,15);
            star(floor4,19);
            star(floor5,4);
        }
		printf("\t\t\t\t\t\tscore : %d \n",score);
        printf("\n\n\t    __\n\t"); //�L�X�Ĥ��h 
        printf("| \\");  //�L�X�Ӷ�
        display(floor5,3,canvas);

        printf("\n\n\n\t"); //�L�X�ĥ|�h
        display(floor4,0,canvas);

        printf("\n\n\n\t"); //�L�X�ĤT�h
        display(floor3,0,playerDisplayPos);

        printf("\n\n\n\t"); //�L�X�ĤG�h
        display(floor2,0,playerDisplayPos); //�L�X�ĤG�h
        if(currentFloor==2){
            printf("O"); //�[�J�p���s
        } 
        else{
            // if(currentFloor==3){
            //     printf("O");
            // }
            printf(" "); 
        }
        display(floor2,playerDisplayPos+1,canvas);    //�i�g�i���g�A�p�G�Ѫų��O�Ů�N��A���g�]�ݤ��X�A�p�G�A�O���ѬP�i���٬O�g�@�U�a
        
        printf("\n\t"); //�L�X�Ĥ@�h
        display(floor1,0,playerDisplayPos); //�L�X�Ĥ@�h,0-5(6�O�p���s����m)

        if(currentFloor==1){ //�Ĥ���-->�p���s(�S��)
            printf("O");
            if(floor1[6]=='X'){ //���s�J���ê����-->�L�F(score++),�S�L(break)
                win=0; //����while�j��
                system("cls"); //�M�ŭ��� 
                printf("\n\t\t-------------------");
                printf("\n\t\t| GAME OVER ! ! ! |\n\t\t| your score : %2d |\n",score);
                printf("\t\t-------------------\n");
                Sleep(10000);
            }
        }
        else{
            printf("%c",floor1[playerDisplayPos]);    //�p�G���s(���F)���b�o�h�A�ڭ̥����L���W�즳���F��
            if(floor1[6]=='X'){ //���s�J���ê����-->�L�F(score++),�S�L(break)
                score++;
                sleepTime--;
                if(sleepTime==0){  
                    system("cls"); //�M�ŭ��� 
                    printf("\n\t\t-------------------");
                    printf("\n\t\t| YOU   WIN ! ! ! |\n\t\t| your score : %d  |\n",score);
                    printf("\t\t-------------------\n");
                }
            }
        }
        
        display(floor1,playerDisplayPos+1,canvas);  //�L�X�Ĥ@�h,7-49���a�O 
        printf("\n\n\n\t");
        Sleep(sleepTime); //1000==1��A����delay
        system("cls"); //�M�ŭ���
                
        shiftLeft(floor1); //�����ʰ_��
        shiftLeftstar(floor4); //���P�P�ʰ_��
        shiftLeftstar(floor5); //���P�P�ʰ_��
        }
    return 0;
}
