#include "get_text_file.h"
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

typedef struct Pos{
    int x;
    int y;
} Pos;

int getKeyFromChar(char c){
    int v = (int) c;
    if(v>=48 && v <= 57){
        return v - 48;
    }
    if(v >= 65 && v <= 90){
        return v - 55;
    }
    if(v >= 97 && v <= 122){
        return v - 61;
    }
    printf("Error : %c is not a valid character\n", c);
    return -1;
}

int first(File file){
    Pos **frequences = (Pos **)malloc(62 * sizeof(Pos *));
    int total = 0;
    Matrix matrix = *create_matrix(file.lines, file.size_of_line[0]);
    for(int k = 0; k < 62; k++){
        frequences[k] = (Pos *)malloc(10 * sizeof(Pos));
    }
    int frequences_number[62] = {0};
    for(int i = 0; i < file.lines; i++){
        for(int j = 0; j < file.size_of_line[i]; j++){
            matrix.data[i][j] = 0;
            if(file.matrice[i][j] == '.'){
                continue;
            }
            int v = getKeyFromChar(file.matrice[i][j]);
            frequences[v][frequences_number[v]++] = (Pos){i, j};
        }
    }
    
    for(int i = 0; i < 62; i++){
        for(int j = 0; j < frequences_number[i]; j++){
            for(int k = 0; k < frequences_number[i]; k++){
                if(j == k){
                    continue;
                }
                Pos p1 = frequences[i][j];
                Pos p2 = frequences[i][k];
                Pos p3 = (Pos){2*p1.x - p2.x, 2*p1.y - p2.y};
                Pos p4 = (Pos){-p1.x + 2*p2.x, -p1.y + 2*p2.y};
                if(p3.x >= 0 && p3.x < file.lines && p3.y >= 0 && p3.y < file.size_of_line[p3.x]){
                    total += 1-matrix.data[p3.x][p3.y];
                    matrix.data[p3.x][p3.y] = 1;
                }
                if(p4.x >= 0 && p4.x < file.lines && p4.y >= 0 && p4.y < file.size_of_line[p4.x]){
                    total += 1-matrix.data[p4.x][p4.y];
                    matrix.data[p4.x][p4.y] = 1;
                }
            }
        }
    }
    return total;
}

int second(File file){
    Pos **frequences = (Pos **)malloc(62 * sizeof(Pos *));
    int total = 0;
    Matrix matrix = *create_matrix(file.lines, file.size_of_line[0]);
    for(int k = 0; k < 62; k++){
        frequences[k] = (Pos *)malloc(10 * sizeof(Pos));
    }
    int frequences_number[62] = {0};
    for(int i = 0; i < file.lines; i++){
        for(int j = 0; j < file.size_of_line[i]; j++){
            matrix.data[i][j] = 0;
            if(file.matrice[i][j] == '.'){
                continue;
            }
            int v = getKeyFromChar(file.matrice[i][j]);
            frequences[v][frequences_number[v]++] = (Pos){i, j};
        }
    }
    
    for(int i = 0; i < 62; i++){
        for(int j = 0; j < frequences_number[i]; j++){
            for(int k = 0; k < frequences_number[i]; k++){
                if(j == k){
                    continue;
                }
                Pos p1 = frequences[i][j];
                Pos p2 = frequences[i][k];
                Pos vector = (Pos){p2.x - p1.x, p2.y - p1.y};
                for(int l = -2*file.lines; l < 2*file.lines; l++){
                    Pos p3 = (Pos){p2.x + l*vector.x, p2.y + l*vector.y};
                    if(p3.x >= 0 && p3.x < file.lines && p3.y >= 0 && p3.y < file.size_of_line[p3.x]){
                        total += 1-matrix.data[p3.x][p3.y];
                        matrix.data[p3.x][p3.y] = 1;
                    }
                }
            }
        }
    }
    return total;
}

int main(){
    File file = *createFile("input.txt");

    printf("Total : %d\n", first(file));
    printf("Second Calculation : %d\n", second(file));

    return 1;
}
