#include<stdio.h>
#include<string.h>

typedef struct tagCard{
    char name;		//牌大小
    char value;		//牌字符在字符串中的索引
    char suit;		//牌花色
}Card;

typedef Card Item;

Card cardsBlack[5];		//分别储存输入的两副牌
Card cardsWhite[5];

int orderBlack[5];		//每幅牌内部大小排序信息
int orderWhite[5];

char line[32];			//存储输入

char CardValues[]="23456789TJQKA";		//所有牌的值

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

 void SelectionSort(Item a[],int left,int right){		//选择排序
     int i,j,min;
     for(i=left;i<right;i++){
         min=i;
         for(j=i+1;j<right;j++){
             if(a[i].value>a[j].value) min=j;
         }
         exchange(a,i,min);
     }
 }

 void InitCards(){			//将输入的信息输入给两副牌的数组
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

 void SortCards(){					//对每幅牌按照从小到大排序
     SelectionSort(cardsBlack,0,4);
     SelectionSort(cardsWhite,0,4);
 }

 int IsBomb(Item a[],int i){		//判断是否是铁支
     if(a[i+1].value==a[i].value
     && a[i+2].value==a[i].value
     && a[i+3].value==a[i].value)
        return 1;
    
    return 0;
 }

 int IsThree(Item a[],int i){		//判断是否有三条
     if(a[i+1].value==a[i].value
     && a[i+2].value==a[i].value)
        return 1;

    return 0;
 }

 int IsPair(Item a[],int i){		//判断是否有对子
     if(a[i+1].value==a[i].value)
        return 1;
    return 0;
 }

 int IsStraight(Item a[]){			//判断是否是顺子
     if(a[1].value-a[0].value==1
     && a[2].value-a[0].value==1
     && a[3].value-a[0].value==1
     && a[4].value-a[0].value==1)
        return 1;
    return 0;
 }

 int IsFlush(Item a[]){					//判断是否是同花
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

     level=9;						//同花顺
     if(IsStraight(a) && IsFlush(a)){
         order[0]=a[4].value;
         return level;
     }

     level--;						//铁支
     if(IsBomb(a,0) || IsBomb(a,1)){
         order[0]=a[1].value;
         return level;
     }

     
     level--;						//葫芦
     if((IsThree(a,0) && IsPair(a,3)) || (IsThree(a,2) && IsPair(a,0))){
         order[0]=a[2].value;
         return level;
     }

    level--;						//同花
     if(IsFlush(a)){
         for(i=0;i<5;i++)
            order[i]=a[4-i].value;
        return level;
     }

     level--;						//顺子
     if(IsStraight(a)){
         order[0]=a[4].value;
         return level;
     }

     level--;						//三条
     if(IsThree(a,0) || IsThree(a,1) || IsThree(a,2)){
         order[0]=a[2].value;
         return level;
     }

     level--;						//两对
     if( (i=0,IsPair(a,1) && IsPair(a,3))
     || (i=2,IsPair(a,0) && IsPair(a,3))
     || (i=4,IsPair(a,0) && IsPair(a,2))){
         order[0]=a[3].value;
         order[1]=a[1].value;
         order[2]=a[i].value;

         return level;
     }

     level--;						//对子
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

     level--;						//散牌
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
         else{								//级别相同，比较order数组
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
