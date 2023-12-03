#include <stdio.h> 
#include <ctype.h> 
 
typedef unsigned int Bitset; 
const Bitset CONSONANT = 66043630; 
 
unsigned int charToSet(char c){ 
    unsigned int l = 1; 
    c = tolower(c); 
    if (c < 'a' || c > 'z') { 
        return 0; 
    } else { 
        return l << (c - 'a'); 
    } 
} 
 
int countConsonant(Bitset set){ 
    int count = 0; 
    while(set){ 
        set = set & (set - 1); 
        count++; 
    } 
    return count; 
} // eta shtuka hvataet mladshiy bit i vikidivaet ego(t e udaliyaet odnu bukvu) | esly bukva odna, to srazu set obrashaetsya v 0
 
int main() { 
    Bitset consonantCopy, wordSet; 
    int wordCount = 0; 
    char c; 
    while (1) 
    {    
        consonantCopy = CONSONANT; 
        wordSet = 0; 
        while ((c = getchar()) != ' ') 
        { 
            if (c == '\n') break;
            if (c == EOF) break; 
            wordSet = wordSet | charToSet(c); 
        } 
        consonantCopy = consonantCopy & wordSet; 
        if(countConsonant(consonantCopy) == 1) 
            wordCount++; 
        if (c == EOF)  
            break; 
    } 
    printf("Количество слов с одной согласной буквой: %d\n", wordCount); 
    return 0; 
}