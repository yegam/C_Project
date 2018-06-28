#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define CARDS 52
#define BACK -1
//추가적인 전역변수 선언 금지
static char card_suit[4][4] = {"♠", "◆", "♥", "♣"};
static char card_num[13][3] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

int deck[CARDS];
int money;

void print_card(int card);
int F_bet(void);
void F_deck(void);
void F_suffle(void);
int F_point(int);
int F_calcul(int,int,int);
void F_print(int*,int*,int,int);

int main(void){
    int i,bet,dsum,psum,cardNum,pNum,pDeck[10],dNum,dDeck[10],win=1;
    char select;
    money = 200;
    srand(time(0));
    while(money>0){
        printf("\n\n==================\n");
        printf("cash : %d\n",money);
        while(win==1){
            bet=F_bet();
            money -= bet;
            F_deck();
            F_suffle();
            dDeck[0]=deck[0];
            dDeck[1]=deck[1];
            pDeck[0]=deck[2];
            pDeck[1]=deck[3];
            cardNum=4;
            
            printf("\nDealer : \n");
            print_card(BACK);
            print_card(dDeck[1]);
            printf("\nPlayer : \n");
            print_card(pDeck[0]);
            print_card(pDeck[1]);
            
            pNum=2;
            dNum=2;
            psum=F_point(pDeck[0])+F_point(pDeck[1]);
            dsum=F_point(dDeck[1]);
            
            if(psum==21){ //black jack
                printf("\n**BLACK JACK!!!!!!!**\n");
                money += bet*2+bet/2;
                break;
            }
            else if(psum>21){ //lose
                printf("\n**Dealer Win!**\n");
                break;
            }
            else{
                while(1){
                    printf("\nChoose One [h: Hit, s: Stay, d: Double down]\n");
                    scanf("%c",&select);
                    scanf("%c",&select);
                    if(select == 'h'){
                        pDeck[pNum++] = deck[cardNum++];
                        psum=0;
                        for(i=0;i<pNum;i++)
                            psum += F_point(pDeck[i]);
                        printf("\nDealer : \n");
                        print_card(BACK);
                        print_card(dDeck[1]);
                        printf("\nPlayer : \n");
                        for(i=0;i<pNum;i++)
                            print_card(pDeck[i]);
                        if (psum == 21){
                            printf("\n\nPlayer : %d  || Dealer : %d \n**Player Win!**\n",psum,dsum);
                            money += bet*2;
                            break;
                        }
                        else if (psum > 21){
                            printf("\n\nPlayer : %d  || Dealer : %d \n**Dealer win!**\n",psum,dsum);
                            break;
                        }
                    }
                    else if(select == 's'){
                        break;
                    }
                    else if(select == 'd'){
                        if(money < bet)
                            printf("배팅금액이 보유금액보다 큽니다. 다시 입력하세요.\n");
                        else if(pNum!=2)
                            printf("더블다운은 첫번째 턴에 할 수 있습니다. 다시 입력하세요.\n");
                        else {
                            money -= bet;
                            bet *= 2;
                            pDeck[pNum++] = deck[cardNum++];
                            psum = 0;
                            for(i=0;i<pNum;i++)
                                psum += F_point(pDeck[i]);
                            printf("\nDealer : \n");
                            print_card(BACK);
                            print_card(dDeck[1]);
                            printf("\nPlayer : \n");
                            for(i=0;i<pNum;i++)
                                print_card(pDeck[i]);
                            if (psum == 21){
                                printf("\n\nPlayer : %d  || Dealer : %d \n**Player Win!**\n",psum,dsum);
                                money += bet*2;
                                break;
                            }
                            else if(psum > 21){
                                printf("\n\nPlayer : %d  || Dealer : %d \n**Dealer Win!**\n",psum,dsum);
                                break;
                            }
                            else{
                                break;
                            }
                        }
                    }
                    else{
                        printf("알파벳 소문자[h,s,d]로 다시 입력해주세요.\n");
                    }
                }//while(1)
            }//else
            if (psum>=21)
                break;
            else {
                printf("\n==Dealer's Turn==\n");
                F_print(dDeck,pDeck,dNum,pNum);
                dsum=0;
                for(i=0;i<dNum;i++)
                    dsum += F_point(dDeck[i]);
                if (dsum>21){
                    printf("\n\nPlayer : %d  || Dealer : %d \n**Player Win!**\n",psum,dsum);
                    money += bet*2;
                    break;
                }
                else if (dsum == 21){
                    printf("\n\nPlayer : %d  || Dealer : %d \n**Dealer Win!**\n",psum,dsum);
                    break;
                }
                else if(dsum>16){
                    F_calcul(dsum,psum,bet);
                    break;
                }
                else{
                    while(dsum<=16){
                        dDeck[dNum++] = deck[cardNum++];
                        dsum+=F_point(dDeck[dNum-1]);
                    }
                    F_print(dDeck,pDeck,dNum,pNum);
                    if(F_calcul(dsum,psum,bet))
                        break;
                    
                }
            }
        }
    }
    printf("\nGAME OVER...BYE\n");
    return 0;
}


void print_card(int card){
    if (card == BACK)
        printf("▒▒");
    else
        printf("%s%2s\t", card_suit[card/13], card_num[card%13]);
}
int F_bet(void){
    int betCash;
    printf("\nHow much do you bet?\n");
    while(1){
        scanf("%d",&betCash);
        if(betCash <=0)
            printf("배팅금액이 0보다 작거나 같습니다. 다시 입력해주세요.\n");
        else if (money-betCash < 0)
            printf("배팅금액이 보유금액보다 큽니다. 다시 입력해주세요.");
        else
            break;
    }
    
    printf("Bet : %d\n",betCash);
    return betCash;
}
void F_deck(void){
    int i;
    for(i=0;i<CARDS;i++)
        deck[i]=i;
}
void F_suffle(void){
    int i,r,temp;
    for(i=0;i<CARDS;i++){
        r=rand()%52;
        temp=deck[r];
        deck[r]=deck[i];
        deck[i]=temp;
    }
}
int F_point(int n){
    n=n%13;
    if (n == 0)
        return 11;
    else if(n == 10 || n == 11 || n == 12)
        return 10;
    else
        return n+1;
}
int F_calcul(int dsum,int psum,int bet){
    if(dsum>=21 || dsum<psum ){
        printf("\n\nPlayer : %d  || Dealer : %d \n**Player Win!**\n",psum,dsum);
        money += bet*2;
    }
    else if (dsum>psum){
        printf("\n\nPlayer : %d  || Dealer : %d \n**Dealer Win!**\n",psum,dsum);
    }
    else {
        printf("\n\nPlayer : %d  || Dealer : %d \n**The game ended in a tie.**\n",psum,dsum);
        money += bet;
    }
    return 1;
}
void F_print(int *dDeck,int *pDeck,int dNum, int pNum){
    int i;
    printf("\n\nDealer : \n");
    for(i=0;i<dNum;i++){
        print_card(*dDeck);
        dDeck++;
    }
    printf("\nPlayer : \n");
    for(i=0;i<pNum;i++){
        print_card(*pDeck);
        pDeck++;
    }
}
