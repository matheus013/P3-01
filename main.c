#include <string.h>
#include <stdlib.h>
#include <stdio.h>
//User Leveis
#define ALUNO 1
#define PROFESSOR 2
#define PESQUISADOR 3
#define ADMIN 4
//Aloc Status
#define NOALOC 0
#define INPROCESS 1
#define ALOCOK 2
//Aloc Type
#define APRESENTACAO 0
#define AULA 1
#define LAB 2
int auxUser = 0,auxRec = 0,auxAloc = 0, auxLog = 0;

typedef struct{
    int cont = 0;
    char str[1000];
}Log;
typedef struct{
    int id;
    int level;
    char name[200];

}User;
typedef struct{
    int id;
    int type;
    int aloc = NOALOC;
    int idResp;

}Rec;
typedef struct{
    int type;
    int item;
    char titulo[100];
    char descricao[500];
    char inicio[50];
    char fim[50];
    int listUser[250]= {-1};
    int contList = 0;
    int idResp;
    int status;

}Aloc;

User *usuario;
Rec *recurso;
Aloc *alocacao;
Log *log;
void start(int size){
    recurso = (Rec*)malloc(size*size);
    usuario = (User*)malloc(size*size);
    alocacao = (Aloc*)malloc(size*size);
    log = (Log*)malloc(size*size*size);
}
void printRelatorio(){
    printf("Numero de Usuario %d\n",auxUser);
    printf("Numero de Alocacoes %d\n",auxAloc);
    printf("Numero de Recursos %d\n",auxRec);
    printf("Numero de Atividades %d\n",auxLog);
}
char *cat3(char inicio[],char meio[], char fim[]){
    char str[500];
    strcpy(str,inicio);
    strcat(str,meio);
    strcat(str,fim);
    return str;
}

void addList(int idAloc,int idUser){
    int aux = alocacao[idAloc].contList;
    alocacao[idAloc].listUser[aux] = idUser;
    alocacao[idAloc].contList++;
    strcpy(log[auxLog].str,cat3("Usuario ",usuario[idUser].name," foi adcionado a uma lista."));
    auxLog++;
}
void alocar(int idRec,int idUser, int type, char titulo[],char descricao[],
            char inicio[],char fim[]){

    printf("#DEBUG user> %s\n",usuario[idUser].name);
    if(recurso[idRec].aloc == NOALOC){
        if(recurso[idRec].type == APRESENTACAO && usuario[idUser].level == ALUNO){
            alocacao[auxAloc].item = idRec;
            //printf("#DEBUG * %s *\n",titulo);
            strcpy(alocacao[auxAloc].titulo,titulo);
            //printf("#DEBUG * %s *\n",descricao);
            strcpy(alocacao[auxAloc].descricao,descricao);
            strcpy(alocacao[auxAloc].inicio,inicio);
            strcpy(alocacao[auxAloc].fim,fim);
            alocacao[auxAloc].type = type;
            addList(auxAloc,idUser);
            alocacao[auxAloc].idResp = idUser;
            alocacao[auxAloc].status = INPROCESS;
            recurso[idRec].aloc == 1;
            //printf("#debug\n");
            strcpy(log[auxLog].str,cat3("Usuario ",usuario[idUser].name," alocou uma atividade."));
            printf("Recurso alocado com sucesso!! ");
            printf("Id da alocacao: %d\n",auxAloc);
            auxLog++;
            auxAloc++;

        }
        else if(recurso[idRec].type != APRESENTACAO && usuario[idUser].level == ALUNO)
        {printf("Alocacao nao autorizada, para alunos.\n");}
        else{
            alocacao[auxAloc].item = idRec;
            strcpy(alocacao[auxAloc].titulo,titulo);
            strcpy(alocacao[auxAloc].descricao,descricao);
            strcpy(alocacao[auxAloc].inicio,inicio);
            strcpy(alocacao[auxAloc].fim,fim);
            alocacao[auxAloc].type = type;
            addList(auxAloc,idUser);
            alocacao[auxAloc].idResp = idUser;
            alocacao[auxAloc].status = INPROCESS;
            recurso[idRec].aloc == 1;
            strcpy(log[auxLog].str,cat3("Usuario ",usuario[idUser].name," alocou uma atividade."));
            printf("Recurso alocado com sucesso!! ");
            printf("Id da alocacao: %d\n",auxAloc);
            auxLog++;
            auxAloc++;

        }
    }
    else{
        strcpy(log[auxLog].str,cat3("Usuario ",usuario[idUser].name," tentou alocar recurso nao autorizado"));
        printf("Recurso ja esta alocado!!\n");
        auxLog++;}

}
void newRec(int type,int idResp,int idUser){
    if(auxRec == recurso[auxRec].id){
        recurso = (Rec*)realloc(recurso,sizeof(Rec)*2);
    }
    recurso[auxRec].id = auxRec;
    recurso[auxRec].type = type;
    recurso[auxRec].idResp = idResp;
    //printf("#DEBUG\n");
    strcpy(log[auxLog].str,cat3("Usuario ",usuario[idUser].name," criou um novo recurso"));
    printf("Recurso cadastrado com sucesso!! ");
    printf("Id do recurso: %d\n",auxRec);
    auxRec++;
    auxLog++;

}
void newUser(int level,char name[]){
    if(auxUser == usuario[auxUser].id){
        usuario = (User*)realloc(usuario,sizeof(User)*2);
    }
    usuario[auxUser].id = auxUser;
    usuario[auxUser].level = level;
    strcpy(usuario[auxUser].name,name);
    strcpy(log[auxLog].str,cat3("Novo usuario criado ",name,""));
    auxUser++;
    auxLog++;
    printf("Usuario %s cadastrado com sucesso!! ",name);
    printf("Seu id: %d\n",usuario[auxUser-1].id);
}
void printAloc(int idAloc){
    int aux;
    char status[500];
    if(alocacao[idAloc].contList > 0){
        if(alocacao[idAloc].status == INPROCESS){strcpy(status,"Em Processo de Alocacao");}
        else if(alocacao[idAloc].status == ALOCOK){strcpy(status,"Alocacao confirmada");}
        printf("Tipo  |  Titulo  |  Recurso  |  Descricao  |  Inicio  |  Fim  |  Responsavel  |  Status\n");
        printf("%d | %s | %d | %s | %s | %s | %s | %s\n",
               alocacao[idAloc].type,alocacao[idAloc].titulo,
               alocacao[idAloc].item,alocacao[idAloc].descricao,
               alocacao[idAloc].inicio,alocacao[idAloc].fim,
               usuario[alocacao[idAloc].idResp].name,status);
        printf("Usuarios cadastrados:\n");
        for(int j = 0;j < alocacao[idAloc].contList;j++){
            aux = alocacao[idAloc].listUser[j];
            printf("    %s\n",usuario[aux].name);
        }
    }
    else{
        printf("Nao ha Alocacoes\n");
    }

}
void okAloc(int idUser,int idAloc){
    char auxStr[] = "Usuario ";
    if(usuario[idUser].level != ADMIN){
        printf("Usuario não tem autorizacao!\n");
    }
    else{
        alocacao[idAloc].status = ALOCOK;
        strcat(auxStr,usuario[idUser].name);
        strcat(auxStr," autorizou alocacao");
        strcpy(log[auxLog].str,cat3("Usuario ",usuario[idUser].name," Altorizou alocacao."));
        auxLog++;
    }
}
void printLog(){
    printf("Log de Atividades\n");
    if(auxLog == 0){
        printf("Nao ha registros.\n");
    }else{
        for(int i = 0;i < auxLog;i++){
            printf("    %s\n",log[i].str);
        }
    }
}

int main(){
    start(10);
    newUser(ADMIN,"Admin");
    newUser(ALUNO,"matheus inacio");
    newRec(LAB,1,0);
    //printf("#DEBUG\n");
    alocar(0,0,1,"Titulo","Descricao","10/08/2014 - 13:23:00","15/08/2014 - 13:23:00");
    okAloc(0,0);
    alocar(0,0,1,"Titulo","Descricao","10/08/2014 - 13:23:00","15/08/2014 - 13:23:00");
    printAloc(0);
    printLog();
    printRelatorio();
}
