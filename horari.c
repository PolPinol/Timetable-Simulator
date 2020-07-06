#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "dates.h"
#define MAX 4745
#define MAX2 256



int main(int argc, char **argv){

    int curs,i=0,j,lenlinies,x2,y2,a2,h,t,q;
    double x,y,any,primerdia;
    //13 hores cada dia * 365 dies a l'any = 4745 (maxim de linies en 1 any sencer) = MAX
    char paraula[MAX2],dia[MAX][12],ASSIG[MAX][12],SES[MAX][12],GRUP[MAX][12],AULA[MAX][12];

    /* Lectura de dades*/
    sscanf(argv[1],"%d",&curs); //escanegem el curs donat per pantalla
    sscanf(argv[2],"%lf/%lf",&x,&y); //escanegem el dia/mes donat per pantalla, pot ser tant dll,dm..

    any= (double) mm2any(curs,y); //any corresponent al dia i mes en varaible double
    primerdia=c2jd(any,y,x); //dia donat rotarlo fins el dilluns corresponent
    x2= (int) x;
    y2= (int) y;
    primerdia=primerdia-data2diaset(curs,x2,y2); //primer dia de la setmana = dilluns de la setmana

    while(scanf("%s %s %s %s %s",dia[i],ASSIG[i],SES[i],GRUP[i],AULA[i])!=EOF){ //escanegem totes les linies del document txt
        i++;
    }
    lenlinies=i; //0 .. (lenlinies-1) = llargada de dades agafades = quantes linies hi havia al document (lenlinies)
    
    /* Escriptura d'horari */
    printf("        ");
    for(i=0;i<5;i++){ //escriptura de:  dll 15/4 dm 16/4 dc 17/4 ...
        jd2c(primerdia+i,&any,&y,&x);
        printf("%s %02.lf/%02.lf      ",nomdiaset[i],x,y);
    }
    printf("\n      .......................................................................\n");
    h=8;
    while(h!=21){ //bucle per escriure totes les hores de 8-9 ... 20-21
        q=0;
        while(q!=3){
            //bucle per escriure les 3 linies buides: q=0 (ASSIG) , q=1 (SES-GRUP) , q=2 (AULA)
            if(q==0){
                printf("%02d-%02d ",h,h+1); //si q=0 (primera linea buida) s'escriu la hora corresponent
            }
            j=0;
            while(j!=5){ //bucle per cada dia (j=0 (dl), j=1 (dm), j=2 (dc), j=3 (dj), j=4 (dv))
                t=0;
                i=0;
                while(i!=lenlinies){
                    jd2c(primerdia+j,&any,&x,&y); //es rota el dia a traves del dia julia de dilluns a divendres
                    a2= (int) any;
                    x2= (int) x;
                    y2= (int) y;
                    sprintf(paraula,"%04d%02d%02d%02d",a2,x2,y2,h);
                    //escriure el dia que estem comparant de la forma YYYYMMDDHH per compararho amb tots els de linies.txt
                    if(strcmp(paraula,dia[i])==0){
                        if(q==0){ //estem a la linea 1 buida
                            if(j==0){
                                printf("|%-13s|",*(ASSIG+i));
                            }
                            else{
                                printf("%-13s|",*(ASSIG+i));
                            }
                        }
                        else if(q==1){ //estem a la linea 2 buida
                            sprintf(paraula,"%s-%s",*(SES+i),*(GRUP+i));
                            if(j==0){
                                printf("      |%-13s|",paraula);
                            }
                            else{
                                printf("%-13s|",paraula);
                            }
                        }
                        else{ //estem a la linea 3 buida
                            if(j==0){
                                printf("      |%-13s|",*(AULA+i));
                            }
                            else{
                                printf("%-13s|",*(AULA+i));
                            }
                        }
                        t=1;
                    }
                    i++;
                }
                if(t==0){ //si no ha coincidit res utilitzem t com a bandera per escriureho tot en blanc
                    if(j==0){
                        if(q==0){
                            printf("|             |");
                        }
                        else{
                            printf("      |             |");
                        }
                    }
                    else{
                        printf("             |");
                    }
                }
            j++;
            }
            if(q!=2){
                printf("\n");
            }
            q++;
        }
        printf("\n      |.............|.............|.............|.............|.............|\n");
        h++;
    }
    printf("\f"); //salt de pagina
    return 0;

}