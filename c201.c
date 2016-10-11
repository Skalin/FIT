
/* c201.c *********************************************************************}
{* Téma: Jednosměrný lineární seznam
**
**                     Návrh a referenční implementace: Petr Přikryl, říjen 1994
**                                          Úpravy: Andrea Němcová listopad 1996
**                                                   Petr Přikryl, listopad 1997
**                                Přepracované zadání: Petr Přikryl, březen 1998
**                                  Přepis do jazyka C: Martin Tuček, říjen 2004
**                                            Úpravy: Bohuslav Křena, říjen 2016
**
** Implementujte abstraktní datový typ jednosměrný lineární seznam.
** Užitečným obsahem prvku seznamu je celé číslo typu int.
** Seznam bude jako datová abstrakce reprezentován proměnnou typu tList.
** Definici konstant a typů naleznete v hlavičkovém souboru c201.h.
** 
** Vaším úkolem je implementovat následující operace, které spolu s výše
** uvedenou datovou částí abstrakce tvoří abstraktní datový typ tList:
**
**      InitList ...... inicializace seznamu před prvním použitím,
**      DisposeList ... zrušení všech prvků seznamu,
**      InsertFirst ... vložení prvku na začátek seznamu,
**      First ......... nastavení aktivity na první prvek,
**      CopyFirst ..... vrací hodnotu prvního prvku,
**      DeleteFirst ... zruší první prvek seznamu,
**      PostDelete .... ruší prvek za aktivním prvkem,
**      PostInsert .... vloží nový prvek za aktivní prvek seznamu,
**      Copy .......... vrací hodnotu aktivního prvku,
**      Actualize ..... přepíše obsah aktivního prvku novou hodnotou,
**      Succ .......... posune aktivitu na další prvek seznamu,
**      Active ........ zjišťuje aktivitu seznamu.
**
** Při implementaci funkcí nevolejte žádnou z funkcí implementovaných v rámci
** tohoto příkladu, není-li u dané funkce explicitně uvedeno něco jiného.
**
** Nemusíte ošetřovat situaci, kdy místo legálního ukazatele na seznam 
** předá někdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodně komentujte!
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**/

#include "c201.h"

int solved;
int errflg;

void Error() {
/*
** Vytiskne upozornění na to, že došlo k chybě.
** Tato funkce bude volána z některých dále implementovaných operací.
**/	
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;                      /* globální proměnná -- příznak chyby */
}

void InitList (tList *L) {
/*
** Provede inicializaci seznamu L před jeho prvním použitím (tzn. žádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádět nad již inicializovaným
** seznamem, a proto tuto možnost neošetřujte. Vždy předpokládejte,
** že neinicializované proměnné mají nedefinovanou hodnotu.
**/
	L->First = NULL;
	L->Act = NULL;
	
	
 //solved = TRUE;                   /* V případě řešení, smažte tento řádek! */
}

void DisposeList (tList *L) {
/*
** Zruší všechny prvky seznamu L a uvede seznam L do stavu, v jakém se nacházel
** po inicializaci. Veškerá paměť používaná prvky seznamu L bude korektně
** uvolněna voláním operace free.
***/
	
	while (L->First != NULL) {
		tElemPtr help = malloc(sizeof(struct tElem));
		help = L->First->ptr;	
		free(L->First);
		L->First = NULL;
		L->First = help;
		free(help);
	}
	
	L->Act = NULL;

 //solved = TRUE;                   /* V případě řešení, smažte tento řádek! */
}

void InsertFirst (tList *L, int val) {
/*
** Vloží prvek s hodnotou val na začátek seznamu L.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci Error().
**/
	tElemPtr p_first = malloc(sizeof(struct tElem));	// Provedeme alokaci na velikost tElemPtr

	if (p_first == NULL) {	
		Error();					// Pokud se alokace nepovedla, voláme Error()
	} else {
		p_first->data = val;
		p_first->ptr = L->First;
		L->First->ptr = p_first;
	}

 //solved = TRUE;                   /* V případě řešení, smažte tento řádek! */
}

void First (tList *L) {
/*
** Nastaví aktivitu seznamu L na jeho první prvek.
** Funkci implementujte jako jediný příkaz, aniž byste testovali,
** zda je seznam L prázdný.
**/
	
	L->Act = L->First; 				// Do Active uložíme First

 //solved = TRUE;                   /* V případě řešení, smažte tento řádek! */
}

void CopyFirst (tList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci Error().
**/

	if (L->First == NULL) {
		Error();				 // Pokud je první prvek seznamu NULL, je celý seznam prázdný a proto voláme Error()
	} else {					
		*val = L->First->data;	// Pokud prázdný není, do *val uložíme hodnotu prvního
	}
	
	
 //solved = TRUE;                   /* V případě řešení, smažte tento řádek! */
}

void DeleteFirst (tList *L) {
/*
** Zruší první prvek seznamu L a uvolní jím používanou paměť.
** Pokud byl rušený prvek aktivní, aktivita seznamu se ztrácí.
** Pokud byl seznam L prázdný, nic se neděje.
**/
	if (L->First != NULL) {
		if (L->First == L->Act) {
			free(L->Act);
			L->Act = NULL;
		} else {
			free(L->First);
			L->First = NULL;
		}
	}

 //solved = TRUE;                   /* V případě řešení, smažte tento řádek! */
}	

void PostDelete (tList *L) {
/* 
** Zruší prvek seznamu L za aktivním prvkem a uvolní jím používanou paměť.
** Pokud není seznam L aktivní nebo pokud je aktivní poslední prvek seznamu L,
** nic se neděje.
**/

	if (L->Act != NULL) {
		if (L->Act->ptr != NULL) {
			tElemPtr help = malloc(sizeof(struct tElem));
			help = L->Act->ptr->ptr;
			free(L->Act->ptr);	
			L->Act->ptr = help;
			free(help);
		}
	}
	
	
 //solved = TRUE;                   /* V případě řešení, smažte tento řádek! */
}

void PostInsert (tList *L, int val) {
/*
** Vloží prvek s hodnotou val za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje!
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** zavolá funkci Error().
**/
	
	if (L->Act != NULL) {
		
		tElemPtr p_insert = malloc(sizeof(struct tElem));

		if (p_insert == NULL) {
			Error();
		} else {
			if (L->Act->ptr == NULL) {
				L->Act->ptr = p_insert;
				p_insert->data = val;
				p_insert->ptr = NULL;
			} else {
				p_insert->data = val;
				p_insert->ptr = L->Act->ptr;
				L->Act->ptr = p_insert;
			}
		}
	}
	
 //solved = TRUE;                   /* V případě řešení, smažte tento řádek! */
}

void Copy (tList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam není aktivní, zavolá funkci Error().
**/
	if (L->Act != NULL) {	// Pokud není aktivní volám Error()
		Error();
	} else {
		*val = L->Act->data; // Jinak ukládáme do *val data z Aktivního	
	}
	
 //solved = TRUE;                   /* V případě řešení, smažte tento řádek! */
}

void Actualize (tList *L, int val) {
/*

/* c201.c *********************************************************************}
{* Téma: Jednosměrný lineární seznam
**
**                     Návrh a referenční implementace: Petr Přikryl, říjen 1994
**                                          Úpravy: Andrea Němcová listopad 1996
**                                                   Petr Přikryl, listopad 1997
**                                Přepracované zadání: Petr Přikryl, březen 1998
**                                  Přepis do jazyka C: Martin Tuček, říjen 2004
**                                            Úpravy: Bohuslav Křena, říjen 2016
**
** Implementujte abstraktní datový typ jednosměrný lineární seznam.
** Užitečným obsahem prvku seznamu je celé číslo typu int.
** Seznam bude jako datová abstrakce reprezentován proměnnou typu tList.
** Definici konstant a typů naleznete v hlavičkovém souboru c201.h.
** 
** Vaším úkolem je implementovat následující operace, které spolu s výše
** uvedenou datovou částí abstrakce tvoří abstraktní datový typ tList:
**
**      InitList ...... inicializace seznamu před prvním použitím,
**      DisposeList ... zrušení všech prvků seznamu,
**      InsertFirst ... vložení prvku na začátek seznamu,
**      First ......... nastavení aktivity na první prvek,
**      CopyFirst ..... vrací hodnotu prvního prvku,
**      DeleteFirst ... zruší první prvek seznamu,
**      PostDelete .... ruší prvek za aktivním prvkem,
**      PostInsert .... vloží nový prvek za aktivní prvek seznamu,
**      Copy .......... vrací hodnotu aktivního prvku,
**      Actualize ..... přepíše obsah aktivního prvku novou hodnotou,
**      Succ .......... posune aktivitu na další prvek seznamu,
**      Active ........ zjišťuje aktivitu seznamu.
**
** Při implementaci funkcí nevolejte žádnou z funkcí implementovaných v rámci
** tohoto příkladu, není-li u dané funkce explicitně uvedeno něco jiného.
**
** Nemusíte ošetřovat situaci, kdy místo legálního ukazatele na seznam 
** předá někdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodně komentujte!
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**/

#include "c201.h"

int solved;
int errflg;

void Error() {
/*
** Vytiskne upozornění na to, že došlo k chybě.
** Tato funkce bude volána z některých dále implementovaných operací.
**/	
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;                      /* globální proměnná -- příznak chyby */
}

void InitList (tList *L) {
/*
** Provede inicializaci seznamu L před jeho prvním použitím (tzn. žádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádět nad již inicializovaným
** seznamem, a proto tuto možnost neošetřujte. Vždy předpokládejte,
** že neinicializované proměnné mají nedefinovanou hodnotu.
**/
	L->First = NULL;
	L->Act = NULL;
	
	
 //solved = TRUE;                   /* V případě řešení, smažte tento řádek! */
}

void DisposeList (tList *L) {
/*
** Zruší všechny prvky seznamu L a uvede seznam L do stavu, v jakém se nacházel
** po inicializaci. Veškerá paměť používaná prvky seznamu L bude korektně
** uvolněna voláním operace free.
***/
	
	while (L->First != NULL) {
		tElemPtr help = malloc(sizeof(struct tElem));
		help = L->First->ptr;	
		free(L->First);
		L->First = NULL;
		L->First = help;
		free(help);
	}
	
	L->Act = NULL;

 //solved = TRUE;                   /* V případě řešení, smažte tento řádek! */
}

void InsertFirst (tList *L, int val) {
/*
** Vloží prvek s hodnotou val na začátek seznamu L.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci Error().
**/
	tElemPtr p_first = malloc(sizeof(struct tElem));	// Provedeme alokaci na velikost tElemPtr

	if (p_first == NULL) {	
		Error();					// Pokud se alokace nepovedla, voláme Error()
	} else {
		p_first->data = val;
		p_first->ptr = L->First;
		L->First->ptr = p_first;
	}

 //solved = TRUE;                   /* V případě řešení, smažte tento řádek! */
}

void First (tList *L) {
/*
** Nastaví aktivitu seznamu L na jeho první prvek.
** Funkci implementujte jako jediný příkaz, aniž byste testovali,
** zda je seznam L prázdný.
**/
	
	L->Act = L->First; 				// Do Active uložíme First

 //solved = TRUE;                   /* V případě řešení, smažte tento řádek! */
}

void CopyFirst (tList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci Error().
**/

	if (L->First == NULL) {
		Error();				 // Pokud je první prvek seznamu NULL, je celý seznam prázdný a proto voláme Error()
	} else {					
		*val = L->First->data;	// Pokud prázdný není, do *val uložíme hodnotu prvního
	}
	
	
 //solved = TRUE;                   /* V případě řešení, smažte tento řádek! */
}

void DeleteFirst (tList *L) {
/*
** Zruší první prvek seznamu L a uvolní jím používanou paměť.
** Pokud byl rušený prvek aktivní, aktivita seznamu se ztrácí.
** Pokud byl seznam L prázdný, nic se neděje.
**/
	if (L->First != NULL) {
		if (L->First == L->Act) {
			free(L->Act);
			L->Act = NULL;
		} else {
			free(L->First);
			L->First = NULL;
		}
	}

 //solved = TRUE;                   /* V případě řešení, smažte tento řádek! */
}	

void PostDelete (tList *L) {
/* 
** Zruší prvek seznamu L za aktivním prvkem a uvolní jím používanou paměť.
** Pokud není seznam L aktivní nebo pokud je aktivní poslední prvek seznamu L,
** nic se neděje.
**/

	if (L->Act != NULL) {
		if (L->Act->ptr != NULL) {
			
			tElemPtr help = malloc(sizeof(struct tElem));
			
			help = L->Act->ptr->ptr;
			free(L->Act->ptr);	
			L->Act->ptr = help;
			free(help);
		}
	}
	
	
 //solved = TRUE;                   /* V případě řešení, smažte tento řádek! */
}

void PostInsert (tList *L, int val) {
/*
** Vloží prvek s hodnotou val za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje!
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** zavolá funkci Error().
**/
	
	if (L->Act != NULL) {
		
		tElemPtr p_insert = malloc(sizeof(struct tElem));

		if (p_insert == NULL) {
			Error();
		} else {
			if (L->Act->ptr == NULL) {
				L->Act->ptr = p_insert;
				p_insert->data = val;
				p_insert->ptr = NULL;
			} else {
				p_insert->data = val;
				p_insert->ptr = L->Act->ptr;
				L->Act->ptr = p_insert;
			}
		}
	}
	
 //solved = TRUE;                   /* V případě řešení, smažte tento řádek! */
}

void Copy (tList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam není aktivní, zavolá funkci Error().
**/
	if (L->Act == NULL) {	// Pokud není aktivní volám Error()
		Error();
	} else {
		*val = L->Act->data; // Jinak ukládáme do *val data z Aktivního	
	}
	
 //solved = TRUE;                   /* V případě řešení, smažte tento řádek! */
}

void Actualize (tList *L, int val) {
/*
** Přepíše data aktivního prvku seznamu L hodnotou val.
** Pokud seznam L není aktivní, nedělá nic!
**/

	if (L->Act != NULL) {	// Kontrola jestli je seznam aktivní
		L->Act->data = val;	// Pokud je, uložíme do aktivních dat hodnotu val
	}
	
 //solved = TRUE;                   /* V případě řešení, smažte tento řádek! */
}

void Succ (tList *L) {
/*
** Posune aktivitu na následující prvek seznamu L.
** Všimněte si, že touto operací se může aktivní seznam stát neaktivním.
** Pokud není předaný seznam L aktivní, nedělá funkce nic.
**/

	if (L->Act != NULL) {
		L->Act = L->Act->ptr;
	}
	
 //solved = TRUE;                   /* V případě řešení, smažte tento řádek! */
}

int Active (tList *L) {		
/*
** Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
** Tuto funkci je vhodné implementovat jedním příkazem return. 
**/
	
	return (L->Act != NULL ? 1 : 0);
	
 //solved = TRUE;                   /* V případě řešení, smažte tento řádek! */
}

/* Konec c201.c */
** Přepíše data aktivního prvku seznamu L hodnotou val.
** Pokud seznam L není aktivní, nedělá nic!
**/

	if (L->Act != NULL) {	// Kontrola jestli je seznam aktivní
		L->Act->data = val;	// Pokud je, uložíme do aktivních dat hodnotu val
	}
	
 //solved = TRUE;                   /* V případě řešení, smažte tento řádek! */
}

void Succ (tList *L) {
/*
** Posune aktivitu na následující prvek seznamu L.
** Všimněte si, že touto operací se může aktivní seznam stát neaktivním.
** Pokud není předaný seznam L aktivní, nedělá funkce nic.
**/

	if (L->Act != NULL) {
		L->Act = L->Act->ptr;
	}
	
 //solved = TRUE;                   /* V případě řešení, smažte tento řádek! */
}

int Active (tList *L) {		
/*
** Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
** Tuto funkci je vhodné implementovat jedním příkazem return. 
**/
	
	return (L->Act != NULL ? 1 : 0);
	
 //solved = TRUE;                   /* V případě řešení, smažte tento řádek! */
}

/* Konec c201.c */
