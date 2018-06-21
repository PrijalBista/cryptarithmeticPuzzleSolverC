#include <stdio.h>
#include <conio.h>
#include <string.h>
//simple(less efficient) implementation of solving cryptarithmetic puzzle (uses brute force) 
int len4=0;// stores current length of letters array
char distinctLetters[10];//max 10 unique distinctLetters 
int values[10]={0};//stores unique int values(0-9) to all distinctletters

//add(char[]) : function to add only unique alphabets to distinctLetters array 
// if input is send+more=money  distinctLetters arry should hold s,e,n,d,m,o,r,y
void add(char str[]){ 
	int i,j,l;
	l= strlen(str);
	for(i=0;i<l;i++){
		for (j=len4-1;j>=0;j--){
			if(distinctLetters[j]==str[i])	break;//dublicate i.e alphabet already present 
		}
		if (j==-1){
			distinctLetters[len4]=str[i];
			len4++;
		}
	}	
}

int getValueOfLetter(char str[], char x){ //eg- getvalueofletter(distinctLetters,s)=>2 ie s=2 ,m=5, etc 
	int i,l;
	l=strlen(str);
	for(i=0;i<l;i++){
		if(str[i]==x) return values[i]; // distinctLetters[?]= w1[given index]=char=w2[]=w3[]
	}
}
void assignValuesToLetters(){
	int i = len4-1;
	values[i]++;
	while(values[i]==10){
		values[i]=0;
		i--;
		values[i]++;
	}
}

int factorial(int n){
	if(n==0) return 1;
	else return n*factorial(n-1);
}
int permutation(int n,int r){//to find max no of tries we need to solve the problem
	return factorial(n)/factorial(n-r);  // P(n,r) = n! / (n-r)!
}


int main(){
	int i,j,k,n1,n2,n3,l1,l2,l3,tries;
	char w1[20],w2[20],w3[20],choice='N';
	printf("C implementation of cryptoarithmetic problem only for + ...\n");
	printf("Enter the words : \n");
	gets(w1);
	printf("+\n");
	gets(w2);
	printf("=\n");
	gets(w3);
	l1= strlen(w1); l2= strlen(w2); l3= strlen(w3);
	add(w1); add(w2); add(w3);
	if(len4>10){
		printf("Very long words");
		getch();
		return 0;
	}
	printf("\n%s",distinctLetters);
	tries = permutation(10,len4);//we have len4 number of characters which can be assigned 10 numbers (0-9) without duplication
	printf("\nThe no of tries needed  : %d \n",tries);
	getch();
	
	for(i=0;i<=tries;i++){
		assignValuesToLetters(); //tries new values 
		for(j=0;j<len4;j++){
			for(k=j+1;k<len4;k++){
				if(values[j]==values[k]){
					assignValuesToLetters();
					j=-1;
					break;
				}
			}
		}
		n1=0;n2=0;n3=0;
		for(j=0;j<l1;j++)	n1 = (n1*10) +getValueOfLetter(distinctLetters,w1[j]);		
		for(j=0;j<l2;j++)	n2 = (n2*10) + getValueOfLetter(distinctLetters,w2[j]);
		for(j=0;j<l3;j++)	n3 = (n3*10) + getValueOfLetter(distinctLetters,w3[j]);
		printf("\nchecking n1=%d n2=%d  n1+n2=%d and n3=%d",n1,n2,n1+n2,n3);
		if(n1+n2==n3){
			printf("\nSolution Found  on %d tries :D....\n",i);
			for(j=0;j<len4;j++){
				printf("%c : %d ",distinctLetters[j],values[j]);
			}
			printf("\n Search another possibility? (y/N) : ");
			scanf("%c",&choice);
			if(choice=='N' || choice=='n'||choice=='\n') return 0;
		}
		if(i==tries){
			printf("\n No solution found..");
		}
	}
	return 0;
}
