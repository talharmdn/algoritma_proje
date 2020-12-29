 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>


const char matrix_bigram_strings[10][3] ={"th","he","in","er","an","en","ch","de","ei","te"};
const char matrix_trigram_strings[10][4]={"the","and","ing","ent","ion","der","sch","ich","nde","die"};
const char languages[2][8]={"english", "german"};
const float frequency_eng[20]={2.71, 2.33, 2.03, 1.78, 1.61, 1.13, 0.01, 0.01, 0.01, 0.01, 1.81, 0.73, 0.72, 0.42, 0.42, 0.01, 0.01, 0.01, 0.01, 0.01};
const float frequency_germ[20]={0.01, 0.89, 1.71, 3.90, 1.07, 3.61, 2.36, 2.31, 1.98, 1.98, 0.01, 0.01, 0.01, 0.01, 0.01, 1.04, 0.76, 0.75, 0.72, 0.62};
float calculated_frequencies[20];
float distances [2]={0,0};
void filter_str(char str[]);
void calculate_frequencies_bi(char str[]);
void calculate_frequencies_tri(char str[]);
void calculate_distances();
void detect_lang();

int main()
{
    char metin[2499+1];
    printf("***********************************************************************************\n\n");
    printf("Metninizi giriniz: ");
    gets(metin);
    printf("\n***********************************************************************************\n\n");
    filter_str(metin);
    calculate_frequencies_bi(metin);
    calculate_frequencies_tri(metin);
    calculate_distances();
    detect_lang();
	return 0;
}
void filter_str(char str[]) //metni filtrelem islemi
{
    for(int i=0;i<strlen(str);i++)
    {
       if((str[i]>='a'&&str[i]<='z')||(str[i]>='A'&&str[i]<='Z')||(str[i]==' ')||(str[i]=='\0'))
            str[i]=tolower(str[i]);
       else
         str[i]=' ';
    }
    printf("\n***********************************************************************************\n\n");
    printf("Filtrelenmis metin: %s\n",str);
    printf("\n***********************************************************************************\n\n");
}
void calculate_frequencies_bi(char str[])
{
    int p,j=0,k=0,f=1,sayac=0;
    p=strlen(str)/2;
    char metin_ikili_1[p][3]; // son indiste '\0' olucak --- str[0];
    char metin_ikili_2[p][3]; // son indiste '\0' olucak --- str[1];
    for(int i=0;i<p;i++)
    {
        for(j=0;j<2;j++)
        {
           metin_ikili_1[i][j]=str[k];
           k++;
           metin_ikili_2[i][j]=str[f];
           f++;
        }
        metin_ikili_1[i][j]='\0';
        metin_ikili_2[i][j]='\0';
    }
    for(int a=0;a<10;a++)
    {
        for(int i=0;i<p;i++)
        {
            if(strcmp(metin_ikili_1+i,matrix_bigram_strings+a)==0) // lab dersinde bahadir ve esma hocanin konusmasina gore bu fonksiyonu yazdim.
                sayac++;
            if(strcmp(metin_ikili_2+i,matrix_bigram_strings+a)==0)
                sayac++;
        }
        calculated_frequencies[a]=sayac;
        sayac=0;
    }
    printf("\n***********************************************************************************\n");
    printf("\nBigramlar:\n");
    for(int x=0;x<10;x++)
        printf("\n %s: %%%.0f\n",matrix_bigram_strings[x],calculated_frequencies[x]);
     printf("\n");
     printf("\n***********************************************************************************\n");
}
void calculate_frequencies_tri(char str[])
{
    int p,j=0,k=0,f=1,m=2,sayac=0;
    p=strlen(str)/3;
    char metin_uclu_1[p][4]; // son indiste '\0' olucak --- str[0];
    char metin_uclu_2[p][4]; // son indiste '\0' olucak --- str[1];
    char metin_uclu_3[p][4]; // son indiste '\0' olucak --- str[1];
    for(int i=0;i<p;i++)
    {
        for(j=0;j<3;j++)
        {
           metin_uclu_1[i][j]=str[k];
           k++;
           metin_uclu_2[i][j]=str[f];
           f++;
           metin_uclu_3[i][j]=str[m];
           m++;
        }
        metin_uclu_1[i][j]='\0';
        metin_uclu_2[i][j]='\0';
        metin_uclu_3[i][j]='\0';
    }
    for(int a=0;a<10;a++)
    {
        for(int i=0;i<p;i++)
        {
            if(strcmp(metin_uclu_1+i,matrix_trigram_strings+a)==0)
                sayac++;
            if(strcmp(metin_uclu_2+i,matrix_trigram_strings+a)==0)
                sayac++;
            if(strcmp(metin_uclu_3+i,matrix_trigram_strings+a)==0)
                sayac++;
        }
        calculated_frequencies[a+10]=sayac;
        sayac=0;
    }
    printf("\n\n***********************************************************************************\n Trigramlar:\n");
    for(int x=10;x<20;x++)
        printf("\n %s: %%%.0f\n",matrix_trigram_strings[x-10],calculated_frequencies[x]);
     printf("\n");
     printf("\n***********************************************************************************\n");
}
void calculate_distances()
{
    for(int x=0;x<20;x++)
    {
        distances[0]+=pow((calculated_frequencies[x]*frequency_eng[x]),2);
        distances[1]+=pow((calculated_frequencies[x]*frequency_germ[x]),2);
    }
    distances[0]=sqrt(distances[0]);
    distances[1]=sqrt(distances[1]);
    printf("\n***********************************************************************************\nIngilizce ve Almacanin dillerinin yuzde olarak uzakliklari: \n\n");
    printf("Ingilizce: %f\n",distances[0]);
    printf("Almanca:   %f\n",distances[1]);
    printf("***********************************************************************************\n");
}
void detect_lang()
{
    printf("\n\n***********************************************************************************\n");
    if(distances[0]>distances[1])
        printf("\nMetinin dili ingilizcedir\n");
    else
        printf("\nMetinin dili almancadir\n");
    printf("\n***********************************************************************************\n\n");
}
