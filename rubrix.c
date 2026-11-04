/*
* RUBRIX v0
*/
/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTATTI 1000
#define MAX_LINEE_H 50

typedef struct {
    char cognome [50];
    char nome [50];
    char telefono [50];
    char note [50];
} Rubrica;

 Rubrica *contatti;


/* --- SEZIONE TERMINALE VIDEO --- 
*
*  CONTIENE LE FUNZIONI DI GESTIONE DELLE MASCHERE, DEI COLORI,
*  DEL POSIZIONAMENTO DEL CURSORE, DELLA VISUALIZZAZIONE E 
*  DELL'INSERIMENTO DELLE STRINGHE DI CARATTERI */


void colore_standard ()
{
    printf("\033[0m");
}

void colore_input_output ()
{
    printf("\033[1;33m"); 
}

void cursore (int riga, int colonna)
{
    printf("\033[%d;%dH",riga,colonna);
}

void scrivi_in (int riga, int colonna, char *stringa)
{
    cursore (riga,colonna);
    printf("%s",stringa);
}

void scrivi_posto (int numero)
{
    printf("%4d",numero);
}

void intestazione ()
{
    int conta_colonne=0;

    for (conta_colonne=2; conta_colonne<=MAX_LINEE_H; ++conta_colonne)
    {
        scrivi_in (1,conta_colonne,"─");
        scrivi_in (6,conta_colonne,"─");
    }
        scrivi_in (2,18,"R U B R I X  v.1.0");
        scrivi_in (3,8,"Rubrica contatti per sistemi Unix-like");
        scrivi_in (4,10,"Copyright (C) 2026 Cesare Gennari");
        scrivi_in (5,17,"Licenza GNU GPL v3");
}  

void menu_generale ()
{
    char *opzioni []={
        "1 - Nuovo contatto",
        "2 - Mostra contatto",
        "3 - Lista contatti",
        "4 - Modifica contatto",
        "5 - Cancella contatto",
        "6 - Ordina rubrica",
        "7 - Gestione Archivi",
        "8 - Uscita"
    };
    int conta_righe=7;
    int conta_colonne=0;
    int conta_opzioni=0;

    while ((conta_righe<=14) && (conta_opzioni<8))
    {
        scrivi_in (conta_righe,15,*(opzioni+conta_opzioni));
        conta_righe++;
        conta_opzioni++;
    }

    for (conta_colonne=2; conta_colonne<=MAX_LINEE_H; ++conta_colonne)
    {
        scrivi_in (15,conta_colonne,"─");
        scrivi_in (16,10,"Scegliere un'opzione <   >");
        scrivi_in (17,conta_colonne,"─");
    }
}

void menu_gestione_archivi ()
{
    char *opzioni []={
        "1 - Importa rubrica da file",
        "2 - Salva rubrica su file",
        "3 - Esporta su file di testo",
        "4 - Torna al menu generale"
    };

    int conta_righe=9;
    int conta_colonne=0;
    int conta_opzioni=0;

    while ((conta_righe<=12) && (conta_opzioni<4))
    {
      scrivi_in (conta_righe,12,*(opzioni+conta_opzioni));
      conta_righe++;
      conta_opzioni++;
    }

    for (conta_colonne=2; conta_colonne<=MAX_LINEE_H; ++conta_colonne)
    {
      scrivi_in (8,conta_colonne,"─");
      scrivi_in (14,conta_colonne,"─");
      scrivi_in (15,10,"Scegliere un'opzione <   >");
      scrivi_in (16,conta_colonne,"─");
    }
      scrivi_in (7,14,"-- GESTIONE ARCHIVI --");
}

void maschera_nuovo_contatto ()
{
     char *campi []={
        "N°       :",
        "COGNOME  :",
        "NOME     :",
        "TELEFONO :",
        "NOTE     :",
     };
    int conta_righe=10; 
    int conta_colonne=0;
    int conta_campi=0;

    scrivi_in (7,15,"-- NUOVO CONTATTO --");

    for (conta_colonne=2; conta_colonne<=MAX_LINEE_H; ++conta_colonne)
    {
        scrivi_in (6,conta_colonne,"─");
        scrivi_in (8,conta_colonne,"─");
        scrivi_in (20,conta_colonne,"─");
    }
   
    while ((conta_righe<=30) && (conta_campi<5))
    {
        scrivi_in (conta_righe,12,*(campi+conta_campi));
        conta_righe+=2;
        conta_campi++;
    }
}

void maschera_lista_contatti ()
{
   char *voci_lista []={
    "<Pos.>",
    "<Cognome>",
    "<Nome>",
    "<Telefono>",
   };
   int conta_colonne=2;

   for (conta_colonne=2; conta_colonne<=MAX_LINEE_H; ++conta_colonne)
   {
    scrivi_in (8,conta_colonne,"─");
    scrivi_in (10,conta_colonne,"─");
    scrivi_in (21,conta_colonne,"─");
   }

   scrivi_in (9,4,*(voci_lista));
   scrivi_in (9,12,*(voci_lista+1));
   scrivi_in (9,25,*(voci_lista+2));
   scrivi_in (9,40,*(voci_lista+3));
}

void maschera_ricerca_contatto ()
{
    char *campi[]={
        "COGNOME  :",
        "NOME     :"
    };
    int conta_colonne=0;
    int conta_campi=0;
    int conta_righe=9;

    for (conta_colonne=2; conta_colonne<=MAX_LINEE_H; ++conta_colonne)
    {
        scrivi_in (6,conta_colonne,"─");
        scrivi_in (8,conta_colonne,"─");
        scrivi_in (12,conta_colonne,"─");
    }

    while ((conta_righe<=11) && (conta_campi<=1))
    {
        scrivi_in (conta_righe,10,*(campi+conta_campi));
        conta_righe+=2;
        conta_campi++;
    }
}

void ricarica_schermo ()
{
    printf("\033[2J");
    printf("\033[H");
    
    colore_standard ();
    intestazione ();
}

void pulizia_schermo ()
{
    printf("\033[2J");
    printf("\033[H");
    colore_standard ();
}


/* --- SEZIONE OPERATIVA ---
*
*  CONTIENE LE FUNZIONI DI INSERIMENTO, STAMPA A VIDEO, RICERCA, MODIFICA E 
*  CANCELLAZIONE DEI CONTATTI IN RUBRICA */

void pulizia_buffer ()
{
    int c=0;
    while ((c=getchar ()) !='\n' && (c !=EOF))
    {
        /* ignora newline */
    } 
}

void lettura_stringa (char *buffer, int lunghezza)
{
    fgets (buffer,lunghezza,stdin);
    buffer [strcspn(buffer, "\n")] = '\0';
}

void lettura_carattere (char carattere)
{
    scanf("%c",&carattere);
}

int lettura_opzione (int numero)
{
    scanf("%d",&numero);
    return (numero);
}

Rubrica nuovo_contatto (Rubrica *contatti, int *totale_contatti)
{ 
   int conta_contatti=*(totale_contatti);
   char conferma='\0';

   if (conta_contatti>=MAX_CONTATTI)
   {
     ricarica_schermo ();
     colore_input_output ();
     scrivi_in (10,8,"ATTENZIONE, LA RUBRICA E' PIENA !!!");
     cursore (10,50); lettura_carattere (conferma);
   } else {
   colore_input_output ();
   cursore (10,24); scrivi_posto (conta_contatti+1);
   cursore (12,24); lettura_stringa ((contatti[conta_contatti].cognome),50);   
   cursore (14,24); lettura_stringa ((contatti[conta_contatti].nome),50);
   cursore (16,24); lettura_stringa ((contatti[conta_contatti].telefono),50);
   cursore (18,24); lettura_stringa ((contatti[conta_contatti].note),50);
   conta_contatti++;
   *(totale_contatti)+=1;
   }

   return (*contatti);
}

Rubrica mostra_contatto (Rubrica *contatti, int *quale_record)
{
   colore_input_output ();
   cursore (10,24); scrivi_posto (*(quale_record));
   *(quale_record)-=1;
   scrivi_in (12,24,(contatti[*(quale_record)].cognome));   
   scrivi_in (14,24,(contatti[*(quale_record)].nome));
   scrivi_in (16,24,(contatti[*(quale_record)].telefono));
   scrivi_in (18,24,(contatti[*(quale_record)].note));
 
   return *(contatti);
}

Rubrica lista_contatti (Rubrica *contatti, int totale_contatti)
{
    int conta_contatti=0;
    int conta_righe=11;
    char scrolling='\0';

    scrivi_in (7,15,"-- LISTA CONTATTI --");

    if (totale_contatti==0)
    {
        colore_input_output ();
         scrivi_in (14,10,"Nessuna corrispondenza trovata");
    }

    while ((conta_contatti<totale_contatti) && (conta_righe<conta_righe+totale_contatti))
    {
        colore_input_output ();
        cursore (conta_righe,2); scrivi_posto(conta_contatti+1);
        scrivi_in (conta_righe,12,contatti[conta_contatti].cognome);
        scrivi_in (conta_righe,25,contatti[conta_contatti].nome);
        scrivi_in (conta_righe,40,contatti[conta_contatti].telefono);

        if (conta_righe>=20)
        {
          colore_standard ();
          scrivi_in (22,7,"Premere <ENTER> per continuare ...");
          cursore (22,42); lettura_carattere (scrolling);
          ricarica_schermo ();
          intestazione ();
          maschera_lista_contatti ();
          conta_righe=10;
        }
        conta_contatti++;
        conta_righe++;
    }
    return *(contatti);
}

int ricerca_contatti (char quale_cognome[], char quale_nome[], Rubrica *contatti, int totale_contatti)
{
    int conta_contatti=0;
    int conta_righe=11;
    int trovato=0;
    char scrolling='\0';

    cursore (9,24); lettura_stringa (quale_cognome,50);
    cursore (11,24); lettura_stringa (quale_nome,50);

     ricarica_schermo ();
     maschera_lista_contatti ();
     scrivi_in (7,12,"-- CORRISPONDENZE TROVATE --");
     colore_input_output ();

    while ((conta_contatti<totale_contatti) && (conta_righe<conta_righe+totale_contatti))
    {   
      if ((strcasecmp(quale_cognome,contatti[conta_contatti].cognome)==0) && 
      (strcasecmp(quale_nome,contatti[conta_contatti].nome)==0))
      {
        cursore (conta_righe-conta_contatti,2); scrivi_posto (conta_contatti+1);
        scrivi_in (conta_righe-conta_contatti,15,contatti[conta_contatti].cognome);
        scrivi_in (conta_righe-conta_contatti,27,contatti[conta_contatti].nome);
        scrivi_in (conta_righe-conta_contatti,40,contatti[conta_contatti].telefono);
        trovato++;

        if (conta_righe>=20)
        {
          colore_standard ();
          scrivi_in (22,7,"Premere <ENTER> per continuare ...");
          cursore (22,42); lettura_carattere (scrolling);
          ricarica_schermo ();
          intestazione ();
          maschera_lista_contatti ();
          conta_righe=10;
        }
      }
      conta_contatti++;
      conta_righe++;
     }
     colore_standard ();
     return (trovato);
}

Rubrica modifica_contatto (Rubrica *contatti, int *quale_record)
{
   colore_input_output ();
   cursore (10,24); scrivi_posto (*(quale_record));
    *(quale_record)-=1;
   cursore (12,24); lettura_stringa ((contatti[*(quale_record)].cognome),50);   
   cursore (14,24); lettura_stringa ((contatti[*(quale_record)].nome),50);
   cursore (16,24); lettura_stringa ((contatti[*(quale_record)].telefono),50);
   cursore (18,24); lettura_stringa ((contatti[*(quale_record)].note),50);

   return *(contatti);
}
   
Rubrica cancella_contatto (Rubrica *contatti, int *quale_record, int *totale_contatti)
{
    int conta_record=0;
    *(quale_record)-=1;

    for ((conta_record=*(quale_record)); conta_record<*(totale_contatti); ++conta_record)
    {
      *(contatti+conta_record)=*(contatti+conta_record+1);
    }
    *(totale_contatti)-=1;
    return *(contatti);
}

void ordina_contatti (Rubrica *contatti, int totale_contatti)
{
   Rubrica temp_contatti;

   int conta_prec=0;
   int conta_succ=0;

   for (conta_prec=0; conta_prec<totale_contatti-1; ++conta_prec)
   {
      for (conta_succ=conta_prec+1; conta_succ<totale_contatti; ++conta_succ)
      {
        if (strcasecmp(contatti[conta_prec].cognome,contatti[conta_succ].cognome)>0)
        {
            (temp_contatti)=(contatti[conta_prec]);
            (contatti[conta_prec])=(contatti[conta_succ]);
            (contatti[conta_succ])=temp_contatti;
        }

        if ((strcasecmp(contatti[conta_prec].cognome,contatti[conta_succ].cognome)==0) &&
        (strcasecmp(contatti[conta_prec].nome,contatti[conta_succ].nome)>0)) 
        {
            (temp_contatti)=(contatti[conta_prec]);
            (contatti[conta_prec])=(contatti[conta_succ]);
            (contatti[conta_succ])=temp_contatti;
        }
     }
    }
}

/*--- SEZIONE ARCHIVI E PERSISTENZE ---
 *
 * CONTIENE LE FUNZIONI DI GESTIONE DEI FILE DI ARCHIVIAZIONE DATI
 * PER L'IMPORTAZIONE, IL SALVATAGGIO E L'ESPORTAZIONE DELLA RUBRICA */

 int importa_rubrica (Rubrica *contatti, char *nome_file)
 {
    int conta_contatti=0;
    char conferma='\0';

    FILE *fp_rubrica;
    fp_rubrica=fopen(nome_file,"rb");

    if (fp_rubrica==NULL)
    {
      scrivi_in (9,8,"FIle non trovato !!!");
      colore_standard ();
      cursore (9,34); lettura_carattere (conferma);
      return (0);
    }
    else {
        while (fread(&contatti[conta_contatti],sizeof(Rubrica),1,fp_rubrica)==1)
        {
          conta_contatti++;
        }
    }
    scrivi_in (9,8,"Importazione effettuata");
    scrivi_in (10,8,"Contatti presenti: ");
    cursore (10,27); scrivi_posto (conta_contatti);

    colore_standard ();
    cursore (10,36); lettura_carattere (conferma);
    fclose (fp_rubrica);
    colore_standard ();
    return (conta_contatti);
}

Rubrica salva_rubrica (Rubrica *contatti, char *nome_file, int *totale_contatti)
{
    int conta_contatti=0;
    char conferma='\0';

    FILE *fp_rubrica;
    fp_rubrica=fopen (nome_file,"wb");

    if (fp_rubrica==NULL)
    {
        scrivi_in (9,8,"Errore di scrittura su file");
        colore_standard ();
        cursore (9,34); lettura_carattere (conferma);
    }
    else {
        while (conta_contatti<*totale_contatti)
        {
            fwrite (&contatti[conta_contatti],sizeof(Rubrica),1,fp_rubrica);
            conta_contatti++;
        }
    }
    colore_input_output ();
    scrivi_in (9,8,"Salvataggio effettuato con successo");
    colore_standard ();
    cursore (9,50); lettura_carattere (conferma);
    fclose (fp_rubrica);
    return *(contatti);
}

void esporta_rubrica (Rubrica *contatti, char *nome_file, int *totale_contatti)
{
    int conta_contatti=0;
    char conferma='\0';

    FILE *fp_rubrica;
    fp_rubrica=fopen (nome_file,"wb");

    if (fp_rubrica==NULL)
    {
        scrivi_in (9,8,"Errore di esportazione dati");
        colore_standard ();
        cursore (9,34); lettura_carattere (conferma);
    }
    else {
        while (conta_contatti<*totale_contatti)
        {
            fprintf (fp_rubrica,"%s;%s;%s;%s\n",
            contatti[conta_contatti].cognome,
            contatti[conta_contatti].nome,
            contatti[conta_contatti].telefono,
            contatti[conta_contatti].note);
            conta_contatti++;
        }
    }
    scrivi_in (9,8,"Esportazione effettuata con successo");
    cursore (9,50); lettura_carattere (conferma);
    fclose (fp_rubrica);
}

/* --- PROGRAMMA PRINCIPALE --- 
*
* RICHIAMA LE ROUTINE DELLE VARIE SEZIONI 
* TRAMITE OPZIONI SCELTE DALL'UTENTE */

int main (void)
{
    int scelta=0;
    int scelta_archivi=0;
    int totale_contatti=0;
    int conta_contatti=0;
    char nome_file [256];
    char conferma='\0';

    char quale_cognome [50];
    char quale_nome [50];
    int quale_record=0;
    int trovato=0;

    contatti=malloc(MAX_CONTATTI*sizeof(Rubrica));

    if (contatti==NULL)
    {
        scrivi_in (1,2,"Errore in allocazione");
        return (1);
    }

    do {
       ricarica_schermo ();
       menu_generale ();

       colore_input_output ();
       cursore (16,33); scelta=lettura_opzione (scelta);

       switch (scelta)
       {
         case 1:
         {
            ricarica_schermo ();
            pulizia_buffer ();
            maschera_nuovo_contatto ();
            *contatti=nuovo_contatto (contatti, &totale_contatti);
            colore_standard ();
            break;
         }
         case 2:
         {
            ricarica_schermo ();
            pulizia_buffer ();
            maschera_ricerca_contatto ();
            scrivi_in (7,15," -- RICERCA CONTATTO --");
            colore_input_output ();
            trovato=ricerca_contatti (quale_cognome, quale_nome, contatti, totale_contatti);

            if (trovato==1)
            {
               scrivi_in (22,12,"Posizione da visualizzare: ");
               colore_input_output ();
               cursore (22,39); quale_record=lettura_opzione (quale_record);
               ricarica_schermo ();
               pulizia_buffer ();
               maschera_nuovo_contatto ();
               scrivi_in (7,15," -- MOSTRA CONTATTO --");
               *contatti=mostra_contatto (contatti, &quale_record);
               colore_standard ();
               scrivi_in (21,5,"Premere <ENTER> per tornare al menu generale");
               cursore (21,50); lettura_carattere (conferma);
               break;
            }
            else
            {
                colore_input_output ();
                scrivi_in (14,12,"Nessuna corrispondenza trovata");
                scrivi_in (15,5,"Premere <ENTER> per tornare al menu generale");
                cursore (15,50); lettura_carattere (conferma);
                /* torna al menu generale */
                break;
            } 
         } 
         case 3:
         {
            ricarica_schermo ();
            pulizia_buffer ();
            maschera_lista_contatti ();
            *contatti=lista_contatti (contatti,totale_contatti);
            colore_standard ();
            scrivi_in (22,4,"Premere <ENTER> per tornare al menu generale");   
            cursore (22,50); lettura_carattere (conferma);
            break;
         }
         case 4:
         {
            ricarica_schermo ();
            pulizia_buffer ();
            maschera_ricerca_contatto ();
            scrivi_in (7,15,"-- RICERCA CONTATTO --");
            colore_input_output ();
            trovato=ricerca_contatti (quale_cognome, quale_nome, contatti, totale_contatti);

            if (trovato==1)
            {
               scrivi_in (22,12,"Posizione da modificare: ");
               colore_input_output ();
               cursore (22,38); quale_record=lettura_opzione (quale_record);
               ricarica_schermo ();
               pulizia_buffer ();
               maschera_nuovo_contatto ();
               scrivi_in (7,15," -- MODIFICA CONTATTO --");
               *contatti=modifica_contatto (contatti, &quale_record);
               break;
            }
            else
            {
                colore_input_output ();
                scrivi_in (14,12,"Nessuna corrispondenza trovata");
                scrivi_in (15,5,"Premere <ENTER> per tornare al menu generale");
                cursore (15,50); lettura_carattere (conferma);
                /* torna al menu generale */
                break;
            } 
         } 
         case 5:
         {
            ricarica_schermo ();
            pulizia_buffer ();
            maschera_ricerca_contatto ();
            scrivi_in (7,15,"-- RICERCA CONTATTO --");
            colore_input_output ();
            trovato=ricerca_contatti (quale_cognome, quale_nome, contatti, totale_contatti);

            if (trovato==1)
            {
               scrivi_in (22,12,"Posizione da cancellare: ");
               colore_input_output ();
               cursore (22,38); quale_record=lettura_opzione (quale_record);
               *(contatti)=cancella_contatto (contatti, &quale_record,&totale_contatti);
               break;
            }
            else
            {
                colore_input_output ();
                scrivi_in (14,12,"Nessuna corrispondenza trovata");
                scrivi_in (15,5,"Premere <ENTER> per tornare al menu generale");
                cursore (15,50); lettura_carattere (conferma);
                /* torna al menu generale */
                break;
            } 
         }
         case 6:
         {
            ordina_contatti (contatti,totale_contatti);
            break;
         }
         case 7:
         {
          do {
            ricarica_schermo ();
            colore_standard ();
            menu_gestione_archivi ();
            colore_input_output ();
            cursore (15,33); scelta_archivi=lettura_opzione (scelta_archivi);
            
            switch (scelta_archivi)
            {
                case 1:
                {
                    ricarica_schermo ();
                    pulizia_buffer ();
                    scrivi_in (7,2,"Nome file da importare: ");
                    colore_input_output ();
                    cursore (7,28); lettura_stringa (nome_file,10);
                    strcat (nome_file,".dat");
                    conta_contatti=importa_rubrica (contatti,nome_file);
                    totale_contatti=conta_contatti;
                    break;
                }
                case 2:
                {
                    ricarica_schermo ();
                    pulizia_buffer ();

                    if (nome_file[0]=='\0')
                    {
                       scrivi_in (7,2,"Nome file da salvare: ");
                       colore_input_output ();
                       cursore (7,28); lettura_stringa (nome_file,10);
                       strcat (nome_file,".dat");
                       salva_rubrica (contatti,nome_file,&totale_contatti);
                       break;
                    }
                    else {
                     salva_rubrica (contatti,nome_file,&totale_contatti);
                    }
                    break;
                }
                case 3:
                {
                   ricarica_schermo ();
                   pulizia_buffer ();
                 
                   scrivi_in (7,2,"Nome file da esportare: ");
                   colore_input_output ();
                   cursore (7,28); lettura_stringa (nome_file,10);
                   strcat (nome_file,".csv");
                   esporta_rubrica (contatti,nome_file,&totale_contatti);
                   break;
                }
              }
            } while (scelta_archivi !=4);
           }
        }
    } while (scelta !=8);

    pulizia_schermo ();
    free (contatti);
    contatti=NULL;

    return (0);
}

