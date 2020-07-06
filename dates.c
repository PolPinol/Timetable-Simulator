#include <stdio.h>
#include <string.h>
#include <math.h>


char *nomdiaset[7] = { "dl", "dm", "dc", "dj", "dv", "ds", "dg" };

/*
 * Canvi de data de calendari a data juliana
 */
double c2jd (double y, double m, double d) {
   double a, b;
   if (m<=2) { y--; m+=12; }
   a=floor(y/100);
   b=y+0.01*m+0.0001*d>=1582.1015 ?
      2-a+floor(a/4)	/* correcci� per la reforma gregoriana */
      : 0;
   return floor(365.25*(y+4716))+floor(30.6001*(m+1))+d+b-1524.5;
}

/*
 * Canvi de data juliana a data de calendari
 */
void jd2c (double jd, double *yy, double *mm, double *dd) {
   double z, f, b, c, d, e;
   jd+=0.5;
   z=floor(jd);
   f=jd-z;
   b=z;
   if (z>=2299161) {	/* correcci� per la reforma gregoriana */
      double alf=floor((z-1867126.25)/36524.25);
      b+=1+alf-floor(alf/4);
   }
   b+=1524;
   c=floor((b-122.1)/365.25);
   d=floor(365.25*c);
   e=floor((b-d)/30.6001);
   *dd=b-d-floor(30.6001*e)+f;
   *mm=e<14 ? e-1 : e-13;
   *yy=4716;
   if (*mm<=2) (*yy)--;
   *yy=c-(*yy);
}

//funcio que torna l'any vigent
int mm2any (int curs, int mm) {
    if(mm>=9){
        return curs;
    }
    else{
        return curs+1;
    }
}

/*
 * Suposant que estem a l'any acad�mic curs-(curs+1), incrementa la data
 * (*dd)/(*mm) en ndies dies.
 */
void incrdata (double curs, double *dd, double *mm, int ndies) {
    
    double d,m,z;
    d=*dd;
    m=*mm;
    
    z=c2jd(curs,m,d);
    z=z+ndies;
    jd2c(z,&curs,&m,&d);
    *dd=d;
    *mm=m;
}


int data2diaset(int curs, int dd, int mm){

    int regular[]={0,3,3,6,1,4,6,2,5,0,3,5};
    int bisiest[]={0,3,4,0,2,5,0,3,6,1,4,6};

    curs=mm2any(curs,mm);

    if((curs%4==0) && !(curs%100==0)){
        mm=bisiest[mm-1];
    }
    else if (curs%400==0){
        mm=bisiest[mm-1];
    }
    else{
        mm=regular[mm-1];
    }

    dd=(((curs-1)%7)+((((curs-1)/4)-((3*(((curs-1)/100)+1))/4))%7)+mm+(dd%7))%7;

    if(dd==1){
        return 0; //dilluns
    }
    else if(dd==2){
        return 1; //dimarts
    }
    else if(dd==3){
        return 2; //dimecres
    }
    else if(dd==4){
        return 3; //dijous
    }
    else if(dd==5){
        return 4; //divendres
    }
    else if(dd==6){
        return 5; //dissabte
    }
    else if(dd==0){
        return 6; //diumenge
    }
    else{
        printf("Error\n");
        return 7;
    }
}


int str2diaset (char *s){
     if(strcmp(s,"dl")==0){
         return 0;
     }
    if(strcmp(s,"dm")==0){
         return 1;
     }
    if(strcmp(s,"dc")==0){
         return 2;
     }
    if(strcmp(s,"dj")==0){
         return 3;
     }
    if(strcmp(s,"dv")==0){
         return 4;
     }
    if(strcmp(s,"ds")==0){
         return 5;
     }
    if(strcmp(s,"dg")==0){
         return 6;
     }
    else{
        return 7;
    }
}






