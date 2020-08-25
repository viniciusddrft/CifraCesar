//
//  main.c
//  cifraCesar
//
//  Created by R2D2 on 23/07/17.
//  Copyright © 2017 R2D2. All rights reserved.
//
//  modified by viniciusddrft

#include <stdio.h>
#include <string.h>

int modularArithmetic(int modulo, int currentPositionModulo, int steps);
int positionVector(char *alphabet, char value);
void code(char *alphabet, char *message, int steps);
void decode(char *alphabet, char *codedMessage, int steps);

/* modularArithmetic(int, int, int) : Retorna as opecações de adição e subtração em aritimetica modular, senao -1.
 *  int modulo = É a última posição do vetor que representa os elementos.
 *  int currentPositionModulo = É a posição atual no módulo, de onde se deve começar a contar.
 *  int steps = É a quantidade de passos a se avançar ou retroceder.
*/
int modularArithmetic(int modulo, int currentPositionModulo, int steps){
    //Clockwise
    if(steps >= 0){
        int positionReturn = currentPositionModulo + steps;
        
        if(positionReturn >= 0 && positionReturn <= modulo){
            return positionReturn;
        }else if(positionReturn > modulo){
            return (positionReturn % modulo) - 1;
        }
    }else{
        //AntiClockwise
        int positionReturn = currentPositionModulo + steps;
        if(positionReturn >= 0){
            return positionReturn;
        }else{
            do{
                for (; currentPositionModulo > -1 && steps < 0; --currentPositionModulo, ++steps);
                
                if(steps == 0)
                    return currentPositionModulo == -1 ? modulo : currentPositionModulo;
                currentPositionModulo = modulo;
                
            }while(steps != 0);
        }
    }
    //In case if error
    return -1;
}

/* positionVector(char*, char) : retorna a posição no vetor do caractere localizado, senao -1.
 *  char *alphabet = É o alfabeto, ou seja, o vetor de valores.
 *  char value = É o caractere a ser encontrado.
 */
int positionVector(char *alphabet, char value){
    char *addressOfFoundValue = strchr(alphabet, value);
    if(addressOfFoundValue){
        int lastPositionVector = (int) strlen(alphabet) - 1;
        int foundPosition = (int) ((addressOfFoundValue + lastPositionVector) - strchr(alphabet, alphabet[lastPositionVector]));
        return  foundPosition;
    }
    return -1;
}

/* code(char *, char *, int) : Codifica a mensagem com a cifragem de Cesar.
 *  alphabet = Alfabeto da cifragem de Cesar.
 *  message = Messagem a ser cifrada.
 *  steps = Passos a ser aplicado, por padrao e 3.
 */
void code(char *alphabet, char *message, int steps){
    int pos;
    int modulo = (int) strlen(alphabet) - 1;
    char *codedMessage = message;
    while(*codedMessage) {
        pos = positionVector(alphabet, *codedMessage);
        pos = modularArithmetic(modulo, pos, steps);
        printf("%c", alphabet[pos]);
        codedMessage++;
    }
}

/* decode(char *, char *, int) : Decodifica a mensagem com a cifragem de Cesar.
 *  alphabet = Alfabeto da cifragem de Cesar usada na cifragem.
 *  codedMessage = Messagem a ser decifrada.
 *  steps = Passos a ser aplicado, deve ser o mesmo da cifragem.
 */
void decode(char *alphabet, char *codedMessage, int steps){
    int pos;
    int modulo = (int) strlen(alphabet) - 1;
    char *message = codedMessage;
    while(*message) {
        pos = positionVector(alphabet, *message);
        pos = modularArithmetic(modulo, pos, steps);
        printf("%c", alphabet[pos]);
        message++;
    }
}


int main(int argc, const char * argv[]) {
    char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    char word[50];
    int answer;
    int key;

    //banner
    printf("main.c\n");
    printf("Cifra de cesar\n");
    printf("Created by R2D2 on 23/07/17.\n");
    printf("credits -> by R2D2\n");
    printf("Copyright © 2017 R2D2. All rights reserved.\n");
    printf("#################################\n");
    printf("### modified by viniciusddrft ###\n");
    printf("#################################\n");
    printf("\n");
    printf("\n");
    printf("\n");

    printf("Você quer decifrar ou cifrar?\n");
    printf("1-decifrar\n");
    printf("2-cifrar\n");
    printf("--> ");
    scanf("%d",&answer);
    if (answer == 1){
        printf("Qual palavra você quer decifrar ?\n");
        printf("--> ");
        scanf("%s",word);
        printf("\n");
        for (int counter; counter !=26; counter++){
            printf("tentativa com a chave %d --> ",counter);
            decode(alphabet, word, counter);
            printf("\n");
        }
    }
    else if (answer == 2){
        printf("Qual palavra você quer cifrar ?\n");
        printf("--> ");
        scanf("%s",word);
        printf("\n");
        printf("Qual chave você quer fazer ?\n");
        printf("--> ");
        scanf("%d",&key);
        printf("cryptografaco com a chave %d --> ",key);
        code(alphabet, word, key);
        printf("\n");
    }
    else{
        printf("opção invalida\n");
    }
    

    return 0;
}
