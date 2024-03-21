#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>
#include<stdbool.h>


#define MAX_WORD_LENGTH 20
#define MAX_WORDS 100
#define ALPHABET_SIZE 26

typedef struct Node
{
    char chr;
    bool isEOF;
    struct Node* child[ALPHABET_SIZE];
}NODE;

NODE* create(char ch)//Seperating the characters of word into the trie structure
{
    NODE* tmp=(NODE*)malloc(sizeof(NODE));
    tmp->chr=ch;
    tmp->isEOF=false;
    for(int i=0;i<ALPHABET_SIZE;i++) 
    {
        tmp->child[i]=NULL;
    }
    return tmp;
}
void insert(NODE *root,char *word)//Adding the strings to the trie structure 
{
    NODE *curr=root;
    for(int i=0;word[i]!='\0';i++) 
    {
        int index=word[i]-'a';
        if(curr->child[index]==false) 
        {
            curr->child[index]=create(word[i]);
        }
        curr=curr->child[index];
    }
    curr->isEOF=true;
}
double calcAcc(NODE *root,char *typed)//doesn't check after the first incorrect character of the word
{
    int len = strlen(typed);
    NODE *curr=root;
    int correct=0;
    for (int i=0;i<len;i++) 
    {
        int index=typed[i]-'a';
        if (curr->child[index]) 
        {
            curr=curr->child[index];
            correct++;
        }
    }
    double acc=(correct/len)*100;
    return acc;
}
void display(char *word,int disptime) 
{
    printf("Memorize the word : %s\n",word);
    fflush(stdout);
    Sleep(disptime);
    //system("clear"); // For Linux 
    system("cls"); // For Windows
}

int main() 
{
    struct Node* root = create('/'); // Root node
    char words[MAX_WORDS][MAX_WORD_LENGTH]={
    "ameliorate", "bombastic", "cacophony", "debilitate", "effervescent",
    "facetious", "gregarious", "hedonistic", "idiosyncratic", "juxtaposition","kaleidoscope", "labyrinthine", "mellifluous", "nonchalant", "obsequious","panacea", "quixotic", "resplendent", "serendipity", "taciturn","ubiquitous", "verisimilitude", "wanderlust", "xenophobia", "yuletide","zealous", "abstemious", "bellicose", "cogent", "deleterious","ebullient", "fastidious", "gregarious", "histrionic", "inchoate",
    "jejune", "kaleidoscopic", "lugubrious", "magnanimous", "nadir",
    "obfuscate", "perfidious", "querulous", "rhetoric", "salubrious",
    "tantamount", "ubiquity", "verdant", "winsome", "xenial",
    "yeoman", "zeitgeist", "alacrity", "bucolic", "chicanery",
    "debacle", "efficacious", "foment", "garrulous", "heterogeneous",
    "indolent", "jubilant", "knell", "luminous", "misanthrope",
    "nefarious", "obstreperous", "palliative", "quagmire", "recalcitrant","sagacious", "tumultuous", "ubiquitous", "vacillate", "wanton",
    "xenophobia", "yeoman", "zeitgeist", "altruistic", "belligerent",
    "capitulate", "denouement", "ephemeral", "fallacious", "garrulous",
    "harangue", "impecunious", "juxtapose", "kowtow", "lachrymose",
    "magnanimous", "nebulous", "obfuscate", "palliate", "quintessential","relegate", "sycophant", "tantamount", "ubiquity", "verdant"};
    int num=100;//Number of words
    for (int i=0;i<num;i++) 
    {
        insert(root,words[i]);
    }
    srand(time(NULL));//Generate random seed
    int success_words=0;
    int total_words=0;
    int diff;
    while(diff<1 || diff>3)
    {
        printf("Choose difficulty(1-3):\n");
        printf("1 - Slow\n");
        printf("2 - Moderate\n");
        printf("3 - Fast\n");
        printf("Enter choice:");
        scanf("%d",&diff);
    }
    int disptime;
    switch(diff) 
    {
        case 1:
            disptime=500;
            break;
        case 2:
            disptime=200;
            break;
        case 3:
            disptime=100;
            break;
        default:
            disptime=200;//Default moderate speed
    } 
    double succ;
    for(int i=0;i<num;i++) 
    {
        int ri=rand()%num;//Random index
        display(words[ri],strlen(words[ri])*disptime);
        printf("Type the word:");
        char user[MAX_WORD_LENGTH];
        scanf("%s",user);
        printf("\n");
        double acc=calcAcc(root,user);
        if(acc==100) 
        {
            success_words++;
        }
        total_words++;
        succ=(((double)success_words/total_words)*100);
        printf("Success Rate:%.2f%%\n",succ);
        if(total_words%10==0) 
        {
            char choice;
            printf("\nDo you wish to stop?(y/n):");
            scanf("%c",&choice);
            if(choice=='y' || choice=='Y') 
            {
                printf("Game stopped.\n");
                break;
            }
        }
    }

    return 0;
}
