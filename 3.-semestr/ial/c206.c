	
/* c206.c **********************************************************}
{* TĂŠma: DvousmÄrnÄ vĂĄzanĂ˝ lineĂĄrnĂ­ seznam
**
**                   NĂĄvrh a referenÄnĂ­ implementace: Bohuslav KĹena, ĹĂ­jen 2001
**                            PĹepracovanĂŠ do jazyka C: Martin TuÄek, ĹĂ­jen 2004
**                                            Ăpravy: Bohuslav KĹena, ĹĂ­jen 2016
**
** Implementujte abstraktnĂ­ datovĂ˝ typ dvousmÄrnÄ vĂĄzanĂ˝ lineĂĄrnĂ­ seznam.
** UĹžiteÄnĂ˝m obsahem prvku seznamu je hodnota typu int.
** Seznam bude jako datovĂĄ abstrakce reprezentovĂĄn promÄnnou
** typu tDLList (DL znamenĂĄ Double-Linked a slouĹžĂ­ pro odliĹĄenĂ­
** jmen konstant, typĹŻ a funkcĂ­ od jmen u jednosmÄrnÄ vĂĄzanĂŠho lineĂĄrnĂ­ho
** seznamu). Definici konstant a typĹŻ naleznete v hlaviÄkovĂŠm souboru c206.h.
**
** VaĹĄĂ­m Ăşkolem je implementovat nĂĄsledujĂ­cĂ­ operace, kterĂŠ spolu
** s vĂ˝ĹĄe uvedenou datovou ÄĂĄstĂ­ abstrakce tvoĹĂ­ abstraktnĂ­ datovĂ˝ typ
** obousmÄrnÄ vĂĄzanĂ˝ lineĂĄrnĂ­ seznam:
**
**      DLInitList ...... inicializace seznamu pĹed prvnĂ­m pouĹžitĂ­m,
**      DLDisposeList ... zruĹĄenĂ­ vĹĄech prvkĹŻ seznamu,
**      DLInsertFirst ... vloĹženĂ­ prvku na zaÄĂĄtek seznamu,
**      DLInsertLast .... vloĹženĂ­ prvku na konec seznamu, 
**      DLFirst ......... nastavenĂ­ aktivity na prvnĂ­ prvek,
**      DLLast .......... nastavenĂ­ aktivity na poslednĂ­ prvek, 
**      DLCopyFirst ..... vracĂ­ hodnotu prvnĂ­ho prvku,
**      DLCopyLast ...... vracĂ­ hodnotu poslednĂ­ho prvku, 
**      DLDeleteFirst ... zruĹĄĂ­ prvnĂ­ prvek seznamu,
**      DLDeleteLast .... zruĹĄĂ­ poslednĂ­ prvek seznamu, 
**      DLPostDelete .... ruĹĄĂ­ prvek za aktivnĂ­m prvkem,
**      DLPreDelete ..... ruĹĄĂ­ prvek pĹed aktivnĂ­m prvkem, 
**      DLPostInsert .... vloĹžĂ­ novĂ˝ prvek za aktivnĂ­ prvek seznamu,
**      DLPreInsert ..... vloĹžĂ­ novĂ˝ prvek pĹed aktivnĂ­ prvek seznamu,
**      DLCopy .......... vracĂ­ hodnotu aktivnĂ­ho prvku,
**      DLActualize ..... pĹepĂ­ĹĄe obsah aktivnĂ­ho prvku novou hodnotou,
**      DLSucc .......... posune aktivitu na dalĹĄĂ­ prvek seznamu,
**      DLPred .......... posune aktivitu na pĹedchozĂ­ prvek seznamu, 
**      DLActive ........ zjiĹĄĹĽuje aktivitu seznamu.
**
** PĹi implementaci jednotlivĂ˝ch funkcĂ­ nevolejte ĹžĂĄdnou z funkcĂ­
** implementovanĂ˝ch v rĂĄmci tohoto pĹĂ­kladu, nenĂ­-li u funkce
** explicitnÄ uvedeno nÄco jinĂŠho.
**
** NemusĂ­te oĹĄetĹovat situaci, kdy mĂ­sto legĂĄlnĂ­ho ukazatele na seznam 
** pĹedĂĄ nÄkdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodnÄ komentujte!
**
** TerminologickĂĄ poznĂĄmka: Jazyk C nepouĹžĂ­vĂĄ pojem procedura.
** Proto zde pouĹžĂ­vĂĄme pojem funkce i pro operace, kterĂŠ by byly
** v algoritmickĂŠm jazyce PascalovskĂŠho typu implemenovĂĄny jako
** procedury (v jazyce C procedurĂĄm odpovĂ­dajĂ­ funkce vracejĂ­cĂ­ typ void).
**/

#include "c206.h"

int solved;
int errflg;

void DLError() {
/*
** Vytiskne upozornÄnĂ­ na to, Ĺže doĹĄlo k chybÄ.
** Tato funkce bude volĂĄna z nÄkterĂ˝ch dĂĄle implementovanĂ˝ch operacĂ­.
**/	
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;             /* globĂĄlnĂ­ promÄnnĂĄ -- pĹĂ­znak oĹĄetĹenĂ­ chyby */
    return;
}

void DLInitList (tDLList *L) {
/*
** Provede inicializaci seznamu L pĹed jeho prvnĂ­m pouĹžitĂ­m (tzn. ĹžĂĄdnĂĄ
** z nĂĄsledujĂ­cĂ­ch funkcĂ­ nebude volĂĄna nad neinicializovanĂ˝m seznamem).
** Tato inicializace se nikdy nebude provĂĄdÄt nad jiĹž inicializovanĂ˝m
** seznamem, a proto tuto moĹžnost neoĹĄetĹujte. VĹždy pĹedpoklĂĄdejte,
** Ĺže neinicializovanĂŠ promÄnnĂŠ majĂ­ nedefinovanou hodnotu.
**/
    
	// provadime kompletni inicializaci seznamu
	L->First = NULL;
	L->Act = NULL;
	L->Last = NULL;
	
 //solved = TRUE;                   /* V pĹĂ­padÄ ĹeĹĄenĂ­, smaĹžte tento ĹĂĄdek! */
}

void DLDisposeList (tDLList *L) {
/*
** ZruĹĄĂ­ vĹĄechny prvky seznamu L a uvede seznam do stavu, v jakĂŠm
** se nachĂĄzel po inicializaci. RuĹĄenĂŠ prvky seznamu budou korektnÄ
** uvolnÄny volĂĄnĂ­m operace free. 
**/
	
	tDLElemPtr pom = NULL; // nastavime pomocnou promennou na NULL
	
	while(L->First != NULL && L->Last != NULL) { // dokud prvni a posledni nejsou NULL
		L->Act = L->First; // aktivita na prvnim
		pom = L->First; // do pomocne ulozim prvni
		L->First = pom->rptr; // z prvniho se stane prvek po prvnim
		free(pom); // uvolnim pom
	}
	
	L->Act = NULL;
	
 //solved = FALSE;                   /* V pĹĂ­padÄ ĹeĹĄenĂ­, smaĹžte tento ĹĂĄdek! */
}

void DLInsertFirst (tDLList *L, int val) {
/*
** VloĹžĂ­ novĂ˝ prvek na zaÄĂĄtek seznamu L.
** V pĹĂ­padÄ, Ĺže nenĂ­ dostatek pamÄti pro novĂ˝ prvek pĹi operaci malloc,
** volĂĄ funkci DLError().
**/

	tDLElemPtr pom = malloc(sizeof(struct tDLElem)); // naalokujeme prostor pro pom
	
	if (pom != NULL) { // overime spravnost alokace
		pom->data = val; // do dat ulozime val
		pom->lptr = NULL; // levy ukazatel je NULL, protoze tvorime prvni prvek
		pom->rptr = L->First; // ukazatel na dalsi prvek je na prvni
		
		if (L->First != NULL) { 
			L->First->lptr = pom; // pokud prvni existuje ukazatel na prvni je pom
		} else { 
			L->Last = pom; // jinak je posledni pom
		}
		
		L->First = pom;	// prvni je pom
	} else {
		DLError(); // pokud se nepovedla alokace, vracime chybu
	}
	
	
 //solved = FALSE;                   /* V pĹĂ­padÄ ĹeĹĄenĂ­, smaĹžte tento ĹĂĄdek! */
}

void DLInsertLast(tDLList *L, int val) {
/*
** VloĹžĂ­ novĂ˝ prvek na konec seznamu L (symetrickĂĄ operace k DLInsertFirst).
** V pĹĂ­padÄ, Ĺže nenĂ­ dostatek pamÄti pro novĂ˝ prvek pĹi operaci malloc,
** volĂĄ funkci DLError().
**/ 	

	tDLElemPtr pom = malloc(sizeof(struct tDLElem)); // naalokujeme prostor pro pom
	
	if (pom != NULL) { // overime spravnost alokace
		pom->data = val; // do dat ulozime val
		pom->rptr = NULL; // pravy ukazatel je NULL, protoze tvorime posledni prvek
		if (L->First != NULL) { // pokud prvni existuje, levy ukazatel je posledni prvek a pravy ukazatel puvodniho posledniho prvku je pom
			pom->lptr = L->Last;
			L->Last->rptr = pom;
		} else { // jinak levy ukazatel je NULL a prvni je pom
			pom->lptr = NULL;
			L->First = pom;		
		}
		L->Last = pom;	// posledni je pom vzdy
	} else {
		DLError(); // jinak volame chybu
	}
	
	
 //solved = FALSE;                   /* V pĹĂ­padÄ ĹeĹĄenĂ­, smaĹžte tento ĹĂĄdek! */
}

void DLFirst (tDLList *L) {
/*
** NastavĂ­ aktivitu na prvnĂ­ prvek seznamu L.
** Funkci implementujte jako jedinĂ˝ pĹĂ­kaz (nepoÄĂ­tĂĄme-li return),
** aniĹž byste testovali, zda je seznam L prĂĄzdnĂ˝.
**/
	L->Act = L->First; // aktivni je prvni

 //solved = TRUE;                   /* V pĹĂ­padÄ ĹeĹĄenĂ­, smaĹžte tento ĹĂĄdek! */
}

void DLLast (tDLList *L) {
/*
** NastavĂ­ aktivitu na poslednĂ­ prvek seznamu L.
** Funkci implementujte jako jedinĂ˝ pĹĂ­kaz (nepoÄĂ­tĂĄme-li return),
** aniĹž byste testovali, zda je seznam L prĂĄzdnĂ˝.
**/
	L->Act = L->Last; // aktivni je posledni
	
 //solved = TRUE;                   /* V pĹĂ­padÄ ĹeĹĄenĂ­, smaĹžte tento ĹĂĄdek! */
}

void DLCopyFirst (tDLList *L, int *val) {
/*
** ProstĹednictvĂ­m parametru val vrĂĄtĂ­ hodnotu prvnĂ­ho prvku seznamu L.
** Pokud je seznam L prĂĄzdnĂ˝, volĂĄ funkci DLError().
**/
	if (L->First != NULL) { // zjistime pritomnost prvniho prvku seznamu
		*val = L->First->data;	// do *val ulozime data prvniho
	} else {
		DLError(); // jinak volame chybu
	}
	
	
 //solved = TRUE;                   /* V pĹĂ­padÄ ĹeĹĄenĂ­, smaĹžte tento ĹĂĄdek! */
}

void DLCopyLast (tDLList *L, int *val) {
/*
** ProstĹednictvĂ­m parametru val vrĂĄtĂ­ hodnotu poslednĂ­ho prvku seznamu L.
** Pokud je seznam L prĂĄzdnĂ˝, volĂĄ funkci DLError().
**/

	if (L->Last != NULL) { // pokud existuje posledni
		*val = L->Last->data; // do *val ulozime hodnotu posledniho
	} else {
		DLError(); // jinak volame chybu
	}
	
	
 //solved = TRUE;                   /* V pĹĂ­padÄ ĹeĹĄenĂ­, smaĹžte tento ĹĂĄdek! */
}

void DLDeleteFirst (tDLList *L) {
/*
** ZruĹĄĂ­ prvnĂ­ prvek seznamu L. Pokud byl prvnĂ­ prvek aktivnĂ­, aktivita 
** se ztrĂĄcĂ­. Pokud byl seznam L prĂĄzdnĂ˝, nic se nedÄje.
**/	
	if (L->First != NULL) { // overime prazdnost seznamu
		
		tDLElemPtr pom = NULL; // pokud neni prazdny, nastavime pom na NULL
		
		if (L->First == L->Act) { // pokud je prvni aktivni, zrusime aktivitu
			L->Act = NULL;
		}
		
		if (L->First == L->Last) { // pokud je prvni i posledni prvek, nastavime oboje na NULL
			L->First = NULL;
			L->Last = NULL;
		} else { // jinak do pom ulozime prvni prvek a do prvniho prvku ulozime nasledujici za prvnim
			pom = L->First;
			L->First = pom->rptr;
			
		}
		free(pom); // uvolnime pom z pameti
	}
	
 //solved = FALSE;                   /* V pĹĂ­padÄ ĹeĹĄenĂ­, smaĹžte tento ĹĂĄdek! */
}	

void DLDeleteLast (tDLList *L) {
/*
** ZruĹĄĂ­ poslednĂ­ prvek seznamu L. Pokud byl poslednĂ­ prvek aktivnĂ­,
** aktivita seznamu se ztrĂĄcĂ­. Pokud byl seznam L prĂĄzdnĂ˝, nic se nedÄje.
**/ 

	if (L->First != NULL) { // overime prazdnost seznamu
		
		tDLElemPtr pom = NULL; // pokud neni prazdny, nastavime pom na NULL
		
		pom = L->Last;
		
		if (L->Last == L->First) { // pokud je prvni i posledni prvek, nastavime oboje na NULL
			L->Last = NULL;
			L->First = NULL;
		} else { // jinak nastavime posledni prvek seznamu na prvek pred poslednim prvkem seznamu
			L->Last = L->Last->lptr;
		}
		
		if (L->Last == L->Act) { // pokud je posledni aktivni, zrusime aktivitu
			L->Act = NULL;
		}
		
		pom->lptr->rptr = NULL; // smazeme pravy ukazatel predposledniho (noveho posledniho) prvku na dalsi prvek
		free(pom); // uvolnime pom z pameti
	}
	
	
 //solved = FALSE;                   /* V pĹĂ­padÄ ĹeĹĄenĂ­, smaĹžte tento ĹĂĄdek! */
}

void DLPostDelete (tDLList *L) {
/*
** ZruĹĄĂ­ prvek seznamu L za aktivnĂ­m prvkem.
** Pokud je seznam L neaktivnĂ­ nebo pokud je aktivnĂ­ prvek
** poslednĂ­m prvkem seznamu, nic se nedÄje.
**/
	
	if (L->Act != NULL) { // overime aktivitu seznamu
		if (L->Act != L->Last) { // overime aktivitu posledniho
			
			tDLElemPtr pom = NULL; // nastavime pom na NULL
			
			pom = L->Act->rptr; // do pom ulozime prvek za aktivnim
			L->Act->rptr = pom->rptr; // prvek za aktivnim je nyni prvek ob jedno
			free(pom); // uvolnime pom z pameti
		}
	}
		
 //solved = FALSE;                   /* V pĹĂ­padÄ ĹeĹĄenĂ­, smaĹžte tento ĹĂĄdek! */
}

void DLPreDelete (tDLList *L) {
/*
** ZruĹĄĂ­ prvek pĹed aktivnĂ­m prvkem seznamu L .
** Pokud je seznam L neaktivnĂ­ nebo pokud je aktivnĂ­ prvek
** prvnĂ­m prvkem seznamu, nic se nedÄje.
**/

	if (L->Act != NULL) { // overime aktivitu seznamu
		if (L->Act != L->First) { // overime zda-li je aktivni i prvni
			
			tDLElemPtr pom = NULL; // nastavime pom na NULL
			
			if (L->Act->lptr == L->First) { // pokud je levy ukazatel aktivniho prvnim prvkem
				pom = L->First; // nastavime pom na prvni prvek
				L->First = pom->rptr; // prvni prvek posuneme o jedno doprava
				
			} else {
				pom = L->Act->lptr; // pokud neni levy ukazatel aktivniho prvni, nastavime levy ukazatel aktivniho do pom
				pom->lptr->rptr = L->Act; // do praveho ukazatele pom ulozime aktivni
			}
			
			free(pom); // uvolnime pom
		}
	}
			
 //solved = FALSE;                   /* V pĹĂ­padÄ ĹeĹĄenĂ­, smaĹžte tento ĹĂĄdek! */
}

void DLPostInsert (tDLList *L, int val) {
/*
** VloĹžĂ­ prvek za aktivnĂ­ prvek seznamu L.
** Pokud nebyl seznam L aktivnĂ­, nic se nedÄje.
** V pĹĂ­padÄ, Ĺže nenĂ­ dostatek pamÄti pro novĂ˝ prvek pĹi operaci malloc,
** volĂĄ funkci DLError().
**/

	if (L->Act != NULL) { // overime aktivitu seznamu
		
		tDLElemPtr pom = malloc(sizeof(struct tDLElem)); // pokud je aktivni, naalokujeme si pamet pro pom
		
		if (pom != NULL) { // pokud se alokace povedla
			if (L->Act == L->Last) { // overime aktivitu na prvnim prvku
				pom->data = val; // data jsou val
				pom->lptr = L->Act; // levy ukazatel nastavime na aktivni
				pom->rptr = NULL; // do ukazatele na dalsi prvek ulozime NULL - jsme na konci
				L->Act->rptr = pom; // pravy ukazatel aktivniho je pom
				L->Last = pom; // posledni je pom
			} else { // pokud prvni prvek na
				pom->data = val; // data jsou val
				pom->lptr = L->Act; // prvek pred pom je aktivni
				pom->rptr = L->Act->rptr; //prvek za pom je puvodni prvek za aktivnim
				L->Act->rptr = pom;	// prvek za aktivnim je pom
			}
		} else {
			DLError(); // jinak vracime chybu
		}
	}
	
	
 //solved = FALSE;                   /* V pĹĂ­padÄ ĹeĹĄenĂ­, smaĹžte tento ĹĂĄdek! */
}

void DLPreInsert (tDLList *L, int val) {
/*
** VloĹžĂ­ prvek pĹed aktivnĂ­ prvek seznamu L.
** Pokud nebyl seznam L aktivnĂ­, nic se nedÄje.
** V pĹĂ­padÄ, Ĺže nenĂ­ dostatek pamÄti pro novĂ˝ prvek pĹi operaci malloc,
** volĂĄ funkci DLError().
**/

	if (L->Act != NULL) {
	
		tDLElemPtr pom = malloc(sizeof(struct tDLElem)); // naalokujeme prostor pro novy prvek
		
		if (pom != NULL) { // pokud probehla spravne alokace a
			if (L->Act == L->First) { // aktivni prvek je zaroven prvni
				pom->data = val;
				pom->lptr = NULL;
				pom->rptr = L->First;
				L->First->lptr = pom;
				L->First = pom; // ulozim data
			} else { // pokud neni prvni
				pom->data = val;
				pom->lptr = L->Act->lptr;
				pom->rptr = L->Act;
				L->Act->lptr = pom;
			}
		} else {
			DLError(); // jinak vracime chybu
		}
	}
	
 //solved = FALSE;                   /* V pĹĂ­padÄ ĹeĹĄenĂ­, smaĹžte tento ĹĂĄdek! */
}

void DLCopy (tDLList *L, int *val) {
/*
** ProstĹednictvĂ­m parametru val vrĂĄtĂ­ hodnotu aktivnĂ­ho prvku seznamu L.
** Pokud seznam L nenĂ­ aktivnĂ­, volĂĄ funkci DLError ().
**/
	if (L->Act != NULL) {
		*val = L->Act->data; // pokud je seznam aktivni, do pointeru na val ulozime hodnotu aktivniho prvku
	} else {
		DLError(); // jinak vracime chybu
	}
	
	
 //solved = TRUE;                   /* V pĹĂ­padÄ ĹeĹĄenĂ­, smaĹžte tento ĹĂĄdek! */
}

void DLActualize (tDLList *L, int val) {
/*
** PĹepĂ­ĹĄe obsah aktivnĂ­ho prvku seznamu L.
** Pokud seznam L nenĂ­ aktivnĂ­, nedÄlĂĄ nic.
**/

	if (L->Act != NULL) {
		L->Act->data = val; // overime zda-li aktivita existuje, pokud ano, nastavime obsah data aktivniho prvku na val
	}
	
 //solved = TRUE;                   /* V pĹĂ­padÄ ĹeĹĄenĂ­, smaĹžte tento ĹĂĄdek! */
}

void DLSucc (tDLList *L) {
/*
** Posune aktivitu na nĂĄsledujĂ­cĂ­ prvek seznamu L.
** NenĂ­-li seznam aktivnĂ­, nedÄlĂĄ nic.
** VĹĄimnÄte si, Ĺže pĹi aktivitÄ na poslednĂ­m prvku se seznam stane neaktivnĂ­m.
**/
	if (L->Act != NULL) {
		L->Act = L->Act->rptr; // pokud je seznam aktivni, nastavim aktivitu na prvek za aktivnim prvkem
	}
	
 //solved = TRUE;                   /* V pĹĂ­padÄ ĹeĹĄenĂ­, smaĹžte tento ĹĂĄdek! */
}


void DLPred (tDLList *L) {
/*
** Posune aktivitu na pĹedchozĂ­ prvek seznamu L.
** NenĂ­-li seznam aktivnĂ­, nedÄlĂĄ nic.
** VĹĄimnÄte si, Ĺže pĹi aktivitÄ na prvnĂ­m prvku se seznam stane neaktivnĂ­m.
**/
	
	if (L->Act != NULL) {
		L->Act = L->Act->lptr;	// pokud je seznam aktivni, nastavim aktivitu na prvek pred aktivnim prvkem
	}
	
 //solved = TRUE;                   /* V pĹĂ­padÄ ĹeĹĄenĂ­, smaĹžte tento ĹĂĄdek! */
}

int DLActive (tDLList *L) {
/*
** Je-li seznam L aktivnĂ­, vracĂ­ nenulovou hodnotu, jinak vracĂ­ 0.
** Funkci je vhodnĂŠ implementovat jednĂ­m pĹĂ­kazem return.
**/
	
	return (L->Act != NULL ? 1 : 0); // pokud neni aktivni, vracim 1, jinak 0
	
 //solved = TRUE;                   /* V pĹĂ­padÄ ĹeĹĄenĂ­, smaĹžte tento ĹĂĄdek! */
}

/* Konec c206.c*/
