#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct{
    int id;
    int level;
    char name[];

}User;
typedef struct{
    int id;
    int type;
    int aloc = 0;

}Rec;
typedef struct{
    int type;
    int item;
    char titulo[];
    char descricao[];
    int *listUser;
    int contList = 0;

}Aloc;
int auxUser = 0,auxRec = 0,auxAloc = 0;
User *usuario;
Rec *recurso;
Aloc *alocacao;

void start(int size){
    recurso = (Rec*)malloc(size);
    usuario = (User*)malloc(size);
    alocacao = (Aloc*)malloc(size);
}

void alocar(int idRec,int idUser, int type, char titulo[],char descricao[]){
    if(recurso[idRec].aloc == 0){
    if(recurso[idRec].type== 1 && usuario[idUser].level == 1){
        alocacao[auxAloc].item = idRec;
        strcpy(alocacao[auxAloc].titulo,titulo);
        strcpy(alocacao[auxAloc].descricao,descricao);
        alocacao[auxAloc].type = type;
        alocacao[auxAloc].listUser[alocacao[auxAloc].contList] = idUser;
        alocacao[auxAloc].contList++;
        recurso[idRec].aloc == 1;

    }
    else if(idRec != 1 && idUser == 1){printf("Alocacao nao autorizada, para alunos.\n");}
    else{
        alocacao[auxAloc].item = idRec;
        strcpy(alocacao[auxAloc].titulo,titulo);
        strcpy(alocacao[auxAloc].descricao,descricao);
        alocacao[auxAloc].type = type;
        alocacao[auxAloc].listUser[alocacao[auxAloc].contList] = idUser;
        alocacao[auxAloc].contList++;
        recurso[idRec].aloc == 1;
    }
    }
    else{printf("Recurso ja esta alocado");}
}
void newRec(int type){
    recurso[auxRec].id = auxRec;
    recurso[auxRec].type = type;

}

void newUser(int level,char name[]){
    if(auxUser == usuario[auxUser].id){
        usuario = (User*)realloc(usuario,sizeof(User)*2);
        usuario[auxUser].id = auxUser;
        usuario[auxUser].level = level;
        strcpy(usuario[auxUser].name,name);

        auxUser++;
    }
    else{
        usuario[auxUser].id = auxUser;
        usuario[auxUser].level = level;
        strcpy(usuario[auxUser].name,name);
        auxUser++;
    }
    printf("Usuario %s cadastrado com sucesso!!\n",name);
    printf("Seu id: %d",usuario[auxUser-1].id);
}


int main(){
    start(10);
    newUser(1,"matheus inacio");
    newRec(2);
    printf("oo");
    alocar(0,0,1,"o","asd");
}
