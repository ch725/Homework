#include<stdio.h>
#include<string.h>

typedef struct tagCard{
    char name;		//�ƴ�С
    char value;		//���ַ����ַ����е�����
    char suit;		//�ƻ�ɫ
}Card;

typedef Card Item;

Card cardsBlack[5];		//�ֱ𴢴������������
Card cardsWhite[5];

int orderBlack[5];		//ÿ�����ڲ���С������Ϣ
int orderWhite[5];

char line[32];			//�洢����

char CardValues[]="23456789TJQKA";		//�����Ƶ�ֵ

 void exchange(Item a[],int i,int j){
     char n1=a[i].name;
     char v1=a[i].value;
     char s1=a[i].suit;

     a[i].name=a[j].name;
     a[i].value=a[j].value;
     a[i].suit=a[j].suit;

     a[j].name=n1;
     a[j].value=v1;
     a[j].suit=s1;
 }

 void SelectionSort(Item a[],int left,int right){		//ѡ������
     int i,j,min;
     for(i=left;i<right;i++){
         min=i;
         for(j=i+1;j<right;j++){
             if(a[i].value>a[j].value) min=j;
         }
         exchange(a,i,min);
     }
 }

 void InitCards(){			//���������Ϣ����������Ƶ�����
     int i;
     for(i=0;i<5;i++){
         cardsBlack[i].name=line[3*i];
         cardsBlack[i].suit=line[3*i+1];
         cardsBlack[i].value=strchr(CardValues,cardsBlack[i].name)-CardValues;

         cardsWhite[i].name=line[3*i+15];
         cardsWhite[i].suit=line[3*i+16];
         cardsWhite[i].value=strchr(CardValues,cardsWhite[i].name)-CardValues;
     }
 }

 void SortCards(){					//��ÿ���ư��մ�С��������
     SelectionSort(cardsBlack,0,4);
     SelectionSort(cardsWhite,0,4);
 }

 int IsBomb(Item a[],int i){		//�ж��Ƿ�����֧
     if(a[i+1].value==a[i].value
     && a[i+2].value==a[i].value
     && a[i+3].value==a[i].value)
        return 1;
    
    return 0;
 }

 int IsThree(Item a[],int i){		//�ж��Ƿ�������
     if(a[i+1].value==a[i].value
     && a[i+2].value==a[i].value)
        return 1;

    return 0;
 }

 int IsPair(Item a[],int i){		//�ж��Ƿ��ж���
     if(a[i+1].value==a[i].value)
        return 1;
    return 0;
 }

 int IsStraight(Item a[]){			//�ж��Ƿ���˳��
     if(a[1].value-a[0].value==1
     && a[2].value-a[0].value==1
     && a[3].value-a[0].value==1
     && a[4].value-a[0].value==1)
        return 1;
    return 0;
 }

 int IsFlush(Item a[]){					//�ж��Ƿ���ͬ��
     if(a[1].suit==a[0].suit
     && a[2].suit==a[0].suit
     && a[3].suit==a[0].suit
     && a[4].suit==a[0].suit)
        return 1;
    return 0;
 }

 int GetLevel(Item a[],int order[]){
     int level,i,t1,t2,t3;
     order[0]=order[1]=order[2]=order[3]=order[4]=0;

     level=9;						//ͬ��˳
     if(IsStraight(a) && IsFlush(a)){
         order[0]=a[4].value;
         return level;
     }

     level--;						//��֧
     if(IsBomb(a,0) || IsBomb(a,1)){
         order[0]=a[1].value;
         return level;
     }

     
     level--;						//��«
     if((IsThree(a,0) && IsPair(a,3)) || (IsThree(a,2) && IsPair(a,0))){
         order[0]=a[2].value;
         return level;
     }

    level--;						//ͬ��
     if(IsFlush(a)){
         for(i=0;i<5;i++)
            order[i]=a[4-i].value;
        return level;
     }

     level--;						//˳��
     if(IsStraight(a)){
         order[0]=a[4].value;
         return level;
     }

     level--;						//����
     if(IsThree(a,0) || IsThree(a,1) || IsThree(a,2)){
         order[0]=a[2].value;
         return level;
     }

     level--;						//����
     if( (i=0,IsPair(a,1) && IsPair(a,3))
     || (i=2,IsPair(a,0) && IsPair(a,3))
     || (i=4,IsPair(a,0) && IsPair(a,2))){
         order[0]=a[3].value;
         order[1]=a[1].value;
         order[2]=a[i].value;

         return level;
     }

     level--;						//����
     if( (i=0,t1=4,t2=3,t3=2,IsPair(a,0))
     || (i=1,t1=4,t2=3,t3=0,IsPair(a,1))
     || (i=2,t1=4,t2=1,t3=0,IsPair(a,2))
     || (i=3,t1=2,t2=1,t3=0,IsPair(a,3))){
         order[0]=a[i].value;
         order[1]=a[t1].value;
         order[2]=a[t2].value;
         order[3]=a[t3].value;

         return level;
     }

     level--;						//ɢ��
     for(i=0;i<5;i++)
		 order[i]=a[4-i].value;
     return level;
 }

 int main(){
     int levelBlack,levelWhite,i;

     while(gets(line)!=NULL && strlen(line)>2){
         InitCards();
         SortCards();
         levelBlack=GetLevel(cardsBlack,orderBlack);
         levelWhite=GetLevel(cardsWhite,orderWhite);

         if(levelBlack > levelWhite)
            printf("Black wins.\n");
         else if(levelBlack < levelWhite)
            printf("White wins.\n");
         else{								//������ͬ���Ƚ�order����
             for(i=0;i<5;i++){
                 if(orderBlack[i] > orderWhite[i]){
                     printf("Black wins.\n");
                     break;
                 }
                 else if(orderBlack[i] < orderWhite[i]){
                     printf("White wins.\n");
                     break;
                 }
             }

             if(i==5) printf("Tie.\n");
         }
     }

     return 0;
 }
