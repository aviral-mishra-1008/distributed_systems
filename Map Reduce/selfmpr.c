#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 100
#define MAX_SIZE 1024

typedef struct{
    char word[MAX_WORD_LENGTH];
    int count;
}wordCount;

wordCount words[MAX_WORDS];
int uniqueWords = 0;
wordCount pairs[MAX_WORDS];
int uniquePairs = 0;

void map(char *line){
    //clean the line
    char str[MAX_SIZE];
    int len = strlen(line);
    int k = 0;
    for(int i=0; i<len; i++){
        if(line[i]=='\n' || line[i]=='\r') continue;
        str[k++] = line[i];
    }

    char *token = strtok(str," ");

    while(token!=NULL){
        strcpy(pairs[uniquePairs].word,token);
        pairs[uniquePairs].count = 1;
        uniquePairs++;

        token = strtok(NULL," ");
    }
}

void reduce(){
    for(int i=0; i<uniquePairs; i++){
        int found=0;
        for(int j=0; j<uniqueWords; j++){
            if((strcmp(pairs[i].word,words[j].word))==0){
                words[j].count++;
                found = 1;
                break;
            }
        }

        if(found==0){
            strcpy(words[uniqueWords].word,pairs[i].word);
            words[uniqueWords++].count = 1;
        }
    }

    for(int i=0; i<uniqueWords; i++){
        printf("The instance of word %s is %d \n", words[i].word, words[i].count);
    }
}

int main(int argc, char *argv[]){
    if(argc!=2){
        printf("Usage : ./filename textfilename \n\n");
    }

    FILE *fp = NULL;
    if((fp=fopen(argv[1],"r"))==NULL){
        perror("Cannot open file");
        exit(1);
    }

    char line[MAX_SIZE];
    while(fgets(line, MAX_SIZE, fp)!=NULL){
        map(line);
    }

    fclose(fp);
    reduce();

    return 0;
}