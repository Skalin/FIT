
/* ******************************* c202.c *********************************** */
/*  PĹedmÄt: Algoritmy (IAL) - FIT VUT v BrnÄ                                 */
/*  Ăkol: c202 - ZĂĄsobnĂ­k znakĹŻ v poli                                        */
/*  ReferenÄnĂ­ implementace: Petr PĹikryl, 1994                               */
/*  VytvoĹil: VĂĄclav Topinka, zĂĄĹĂ­ 2005                                       */
/*  Ăpravy: Bohuslav KĹena, ĹĂ­jen 2016                                        */
/* ************************************************************************** */
/*
** Implementujte datovĂ˝ typ zĂĄsobnĂ­k znakĹŻ ve statickĂŠm poli. ADT zĂĄsobnĂ­k je
** reprezentovĂĄn zĂĄznamem typu tStack. StatickĂŠ pole 'arr' je indexovĂĄno
** do maximĂĄlnĂ­ hodnoty STACK_SIZE. PoloĹžka zĂĄznamu 'top' ukazuje na prvek
** na vrcholu zĂĄsobnĂ­ku. PrĂĄzdnĂŠmu zĂĄsobnĂ­ku odpovĂ­dĂĄ hodnota top == -1,
** zĂĄsobnĂ­ku s jednĂ­m prvkem hodnota 0, atd. PĹesnou definici typĹŻ neleznete
** v hlaviÄkovĂŠm souboru c202.h. 
**
** Implementujte nĂĄsledujĂ­cĂ­ funkce:
**
**    stackInit .... inicializace zĂĄsobnĂ­ku
**    stackEmpty ... test na prĂĄzdnost zĂĄsobnĂ­ku
**    stackFull .... test na zaplnÄnost zĂĄsobnĂ­ku
**    stackTop ..... pĹeÄte hodnotu z vrcholu zĂĄsobnĂ­ku
**    stackPop ..... odstranĂ­ prvek z vrcholu zĂĄsobnĂ­ku
**    stackPush .... vloĹžĂ­ prvku do zĂĄsobnĂ­ku
**
** SvĂŠ ĹeĹĄenĂ­ ĂşÄelnÄ komentujte!
**
** TerminologickĂĄ poznĂĄmka: Jazyk C nepouĹžĂ­vĂĄ pojem procedura.
** Proto zde pouĹžĂ­vĂĄme pojem funkce i pro operace, kterĂŠ by byly
** v algoritmickĂŠm jazyce PascalovskĂŠho typu implemenovĂĄny jako
** procedury (v jazyce C procedurĂĄm odpovĂ­dajĂ­ funkce vracejĂ­cĂ­ typ void).
**
**/

#include "c202.h"

int STACK_SIZE = MAX_STACK;
int solved;

void stackError ( int error_code ){
/*   ----------
** Vytiskne upozornÄnĂ­, Ĺže doĹĄlo k chybÄ pĹi prĂĄci se zĂĄsobnĂ­kem.
**
** TUTO FUNKCI, PROSĂME, NEUPRAVUJTE!
*/
	static const char* SERR_STRINGS[MAX_SERR+1] = {"Unknown error","Stack error: INIT","Stack error: PUSH","Stack error: TOP"};
	if ( error_code <= 0 || error_code > MAX_SERR )
		error_code = 0;
	printf ( "%s\n", SERR_STRINGS[error_code] );
	err_flag = 1;
}

void stackInit ( tStack* s ) {
/*   ---------
** Provede inicializaci zĂĄsobnĂ­ku - nastavĂ­ vrchol zĂĄsobnĂ­ku.
** Hodnoty ve statickĂŠm poli neupravujte - po inicializaci zĂĄsobnĂ­ku
** jsou nedefinovanĂŠ.
**
** V pĹĂ­padÄ, Ĺže funkce dostane jako parametr s == NULL,
** volejte funkci stackError(SERR_INIT). U ostatnĂ­ch funkcĂ­ pro zjednoduĹĄenĂ­
** pĹedpoklĂĄdejte, Ĺže tato situace nenastane. 
*/
	
	if (s == NULL) {
		stackError(SERR_INIT);		// pokud dostaneme NULL, vypisujeme poĹžadovanĂ˝ error
	} else {
		s->top = -1;				// jinak inicializujeme konec zĂĄsobnĂ­ku
	}
	
	//  solved = 0;                      /* V pĹĂ­padÄ ĹeĹĄenĂ­, smaĹžte tento ĹĂĄdek! */
}

int stackEmpty ( const tStack* s ) {
/*  ----------
** VracĂ­ nenulovou hodnotu, pokud je zĂĄsobnĂ­k prĂĄzdnĂ˝, jinak vracĂ­ hodnotu 0.
** Funkci implementujte jako jedinĂ˝ pĹĂ­kaz. Vyvarujte se zejmĂŠna konstrukce
** typu "if ( true ) b=true else b=false".
*/
	
	return (s->top == -1 ? 1 : 0);	// overime zda-li je zasobnik prazdny, pokud ano vracime 1, pokud ne, vracime 0
	
	//  solved = 0;                      /* V pĹĂ­padÄ ĹeĹĄenĂ­, smaĹžte tento ĹĂĄdek! */
}

int stackFull ( const tStack* s ) {
/*  ---------
** VracĂ­ nenulovou hodnotu, je-li zĂĄsobnĂ­k plnĂ˝, jinak vracĂ­ hodnotu 0.
** Dejte si zde pozor na Äastou programĂĄtorskou chybu "o jedniÄku"
** a dobĹe se zamyslete, kdy je zĂĄsobnĂ­k plnĂ˝, jestliĹže mĹŻĹže obsahovat
** nejvĂ˝ĹĄe STACK_SIZE prkvĹŻ a prvnĂ­ prvek je vloĹžen na pozici 0.
**
** Funkci implementujte jako jedinĂ˝ pĹĂ­kaz.
*/
	
		return ((s->top == (STACK_SIZE-1) && (s->arr[0] != '\0')) ? 1 : 0); // overime, zda-li je zasobnik plny a pro jistotu overime, ze je prvek na prvni pozici, viz zadani, pokud jsou obe podminky splneny, vracime 1, jinak 0
	
	//  solved = 0;                      /* V pĹĂ­padÄ ĹeĹĄenĂ­, smaĹžte tento ĹĂĄdek! */
}

void stackTop ( const tStack* s, char* c ) {
/*   --------
** VracĂ­ znak z vrcholu zĂĄsobnĂ­ku prostĹednictvĂ­m parametru c.
** Tato operace ale prvek z vrcholu zĂĄsobnĂ­ku neodstraĹuje.
** VolĂĄnĂ­ operace Top pĹi prĂĄzdnĂŠm zĂĄsobnĂ­ku je nekorektnĂ­
** a oĹĄetĹete ho volĂĄnĂ­m funkce stackError(SERR_TOP). 
**
** Pro ovÄĹenĂ­, zda je zĂĄsobnĂ­k prĂĄzdnĂ˝, pouĹžijte dĹĂ­ve definovanou
** funkci stackEmpty.
*/
	
	if (stackEmpty(s)) {
		stackError(SERR_TOP);	// overime, zda-li je zasobnik prazdny, pokud ano, vracime chybu
	} else {
	
		*c = s->arr[s->top];	// jinak predame pomoci pointeru hodnotu vrcholu zasobniku do c
		
	}

	//  solved = 0;                      /* V pĹĂ­padÄ ĹeĹĄenĂ­, smaĹžte tento ĹĂĄdek! */
}


void stackPop ( tStack* s ) {
/*   --------
** OdstranĂ­ prvek z vrcholu zĂĄsobnĂ­ku. Pro ovÄĹenĂ­, zda je zĂĄsobnĂ­k prĂĄzdnĂ˝,
** pouĹžijte dĹĂ­ve definovanou funkci stackEmpty.
**
** VyvolĂĄnĂ­ operace Pop pĹi prĂĄzdnĂŠm zĂĄsobnĂ­ku je sice podezĹelĂŠ a mĹŻĹže
** signalizovat chybu v algoritmu, ve kterĂŠm je zĂĄsobnĂ­k pouĹžit, ale funkci
** pro oĹĄetĹenĂ­ chyby zde nevolejte (mĹŻĹžeme zĂĄsobnĂ­k ponechat prĂĄzdnĂ˝).
** SpĂ­ĹĄe neĹž volĂĄnĂ­ chyby by se zde hodilo vypsat varovĂĄnĂ­, coĹž vĹĄak pro
** jednoduchost nedÄlĂĄme.
** 
*/
	if (!stackEmpty(s)) {
		s->arr[s->top] = '\0'; // overime, zda-li zasobnik je prazdny, pokud neni, "popneme" vrchol
		s->top -= 1;		// a ponizime pocet prvku o 1
	}
	
	//  solved = 0;                      /* V pĹĂ­padÄ ĹeĹĄenĂ­, smaĹžte tento ĹĂĄdek! */
}


void stackPush ( tStack* s, char c ) {
/*   ---------
** VloĹžĂ­ znak na vrchol zĂĄsobnĂ­ku. Pokus o vloĹženĂ­ prvku do plnĂŠho zĂĄsobnĂ­ku
** je nekorektnĂ­ a oĹĄetĹete ho volĂĄnĂ­m procedury stackError(SERR_PUSH).
**
** Pro ovÄĹenĂ­, zda je zĂĄsobnĂ­k plnĂ˝, pouĹžijte dĹĂ­ve definovanou
** funkci stackFull.
*/

	if (stackFull(s)) {		
		stackError(SERR_PUSH);	// overime zda-li je zasobnik plny, pokud ano, volame chybove hlaseni
	} else {
		s->arr[s->top+1] = c;	// pokud ne, na vrchol+1 ulozime parametr c
		s->top += 1;		// a navysime pocet prvku o 1
	}

	//  solved = 0;                      /* V pĹĂ­padÄ ĹeĹĄenĂ­, smaĹžte tento ĹĂĄdek! */
}

/* Konec c202.c */
