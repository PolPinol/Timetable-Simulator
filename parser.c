#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "dates.h"
#define MAX 256

int main(int argc, char **argv){

    int i,j,t,t2=0,q,mode,curs,dd,mm,H0,HF,nnolectius,nsetmcurs;
    double x,y,a,x2,y2,a2,any;
    char ASSIG[12],SES[12],GRUP[12],DIA[2],AULA[12],paraula[MAX];

    /* Lectura de dades */
    sscanf(argv[1],"%d",&curs); //escanegem el curs donat per pantalla

    scanf("%d",&nsetmcurs); //escanegem el numero de setmanes lectives
    double setmcurs[nsetmcurs+1];
    for(i=1;i<=nsetmcurs;i++){ //escanegem cada dilluns de cada setmana lectiva
        scanf("%lf/%lf",&x,&y);
        any= (double) mm2any(curs,y);
        setmcurs[i]=c2jd(any,y,x); //guardem tots els dilluns com a dia julia per no tenir dos variables(dd/mm) per cada dilluns
    }
    scanf("%d",&nnolectius); //escanegem el numero de dies no lectius
    double nolectius[nnolectius+1];
    for(i=1;i<=nnolectius;i++){ //escanegem cada dia no lectiu
        scanf("%lf/%lf",&x,&y);
        any= (double) mm2any(curs,y);
        nolectius[i]=c2jd(any,y,x); //guardem tots els dies no lectius com a dia julia per no tenir dos variables(dd/mm)
    }

    /* Escriptura de linies */
    mode=1; //tenim 3 estats del parser on mode=1 es el primer
    t=1; //sigui t una bandera, t=1 vol dir bandera aixecada
    scanf("%s",paraula);
    while(t==1){ //mentre la bandera esta aixecada
        if(mode==1){ //estat 1 escaneja la assignatura
            if(sscanf(paraula,"assig%s",ASSIG)==1){
                mode=2;
                scanf("%s",paraula);
            }
            else{ //si la paraula no comença per assig donara un error
                fprintf(stderr, "Missatge d’error\n");
                t=0;
            }
        }
        else if(mode==2){ //estat 2 escaneja el bloc ses-grup-dia-hora-aula
            if(sscanf(paraula,"assig%s",ASSIG)==1){ //si la paraula comença per assig torna a l'estat 1
                mode=1;
            }
            else{
                sscanf(paraula,"%s",SES);
                scanf(" grup%s %s %d-%d aula%s",GRUP,DIA,&H0,&HF,AULA);
                if(scanf("%s",paraula)==EOF){ //si quan escanegem la paraula falla es baixa la bandera
                    t=0;
                }
                mode=3;
            }
        }
        else if(mode==3){ //estat 3 escaneja totes les setmanes
            if(sscanf(paraula,"setm%d-%d",&dd,&mm)==2){ //si setm*-*
                for(j=dd;j<=mm;j++){ //bucle per cada setmana
                    jd2c(setmcurs[j]+str2diaset(DIA),&a,&x,&y); //rotar el dilluns de la setmana fins al DIA
                    t2=0; //aixequem segona bandera
                    for(q=1;q<=nnolectius;q++){ //mirem si coincideix dies no lectius amb dia rotat
                        jd2c(nolectius[q],&a2,&x2,&y2);
                        if(x==x2 && y==y2){
                            t2=1; //si passa baixem segona bandera
                        }
                    }
                    if(t2==0){ //si la segona bandera esta aixecada imprimim linies
                        i=H0;
                        while(i!=HF){ //imprimim totes les hores de H0 ... (HF-1)
                            printf("%04.lf%02.lf%02.lf%02d %s %s %s %s\n",a,x,y,i,ASSIG,SES,GRUP,AULA);
                            i++;
                        }
                    }
                }
                if(scanf("%s",paraula)==EOF){ //si quan escanegem la paraula falla es baixa la bandera
                    t=0;
                }
            }
            else if(sscanf(paraula,"setm%d",&dd)==1){ //si no, si setm*
                jd2c(setmcurs[dd]+str2diaset(DIA),&a,&x,&y); //rotar el dilluns de la setmana fins al DIA
                t2=0; //aixequem segona bandera
                for(q=1;q<=nnolectius;q++){ //mirem si coincideix dies no lectius amb dia rotat
                    jd2c(nolectius[q],&a2,&x2,&y2);
                    if(x==x2 && y==y2 ){
                        t2=1; //si passa baixem segona bandera
                    }
                }
                if(t2==0){ //si la segona bandera esta aixecada imprimim linies
                    i=H0;
                    while(i!=HF){ //imprimim totes les hores de H0 ... (HF-1)
                        printf("%04.lf%02.lf%02.lf%02d %s %s %s %s\n",a,x,y,i,ASSIG,SES,GRUP,AULA);
                        i++;
                    }
                }
                if(scanf("%s",paraula)==EOF){ //si quan escanegem la paraula falla es baixa la bandera
                        t=0;
                }
            }
            else if(sscanf(paraula,"%d/%d",&dd,&mm)==2){ //si no, si */*
                t2=0; //aixequem segona bandera
                for(q=1;q<=nnolectius;q++){ //mirem si coincideix dies no lectius amb dia escanejat
                    jd2c(nolectius[q],&a,&x,&y);
                    if(mm==(int) x && dd== (int) y ){ //considerem que si dd/mm donat coincideix amb dia no lectiu existeix un error
                        t2=1;
                        fprintf(stderr, "Missatge d’error\n");
                        t=0; //imprimim missatge d'error i baixem bandera inicial (aturem programa)
                    }
                }
                if(t2==0){ //si la segona bandera esta aixecada imprimim linies
                    i=H0;
                    while(i!=HF){ //imprimim totes les hores de H0 ... (HF-1)
                        printf("%04d%02d%02d%02d %s %s %s %s\n",mm2any(curs,mm),mm,dd,i,ASSIG,SES,GRUP,AULA);
                        i++;
                    }
                }
                if(scanf("%s",paraula)==EOF){ //si quan escanegem la paraula falla es baixa la bandera
                        t=0;
                }
            }
            else{ //no hi han mes setmanes que escanejar per tant hi ha una nova linea
                mode=2;
            }
        }
    }
}