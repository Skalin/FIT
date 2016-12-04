
void initMismatchTable(mismatchTable *Table) {
	Table->First = NULL;
	Table->Act = NULL;
}

void disposeMismatchTable(mismatchTable *Table) {

	mismatchTableItem pom = NULL;

	while (Table->First != NULL) {
		Table->Act = Table->First;
		Table->First = Table->First->next;
		pom = Table->Act;
		plusFree(pom);
	}

	Table->Act = NULL;
}

void insertNext(mismatchTable *Table, char c, int shiftValue) {

	mismatchTableItem pom = plusMalloc(sizeof(mismatchTableItem));

	if (pom != NULL) {
		if (Table->First == NULL) {
			pom->c = c;
			pom->shiftValue = shiftValue;
			pom->next = NULL;
			Table->First = pom;
		} else {
			pom->next = Table->First;
			pom->c = c;
			pom->shiftValue = shiftValue;
			Table->First = pom;
		}
	} else {
		throwException(99, 0, 0);
	}
}

int findChar(mismatchTable *Table, char c) {
	int i = -1;
	Table->Act = Table->First;
	while (Table->Act != NULL) {
		if (c == Table->Act->c) {
			i++;
			return (i);
		}
		Table->Act = Table->Act->next;
	}
	return i;
}

int getShiftValue(mismatchTable *Table, char c) {

	Table->Act = Table->First;

	while (Table->Act->c != c) {
		Table->Act = Table->Act->next;
	}
	return Table->Act->shiftValue;
}

void updateShift(mismatchTable *Table, char c, int shiftValue) {

	Table->Act = Table->First;

	while (Table->Act->c != c) {
		Table->Act = Table->Act->next;
	}
	Table->Act->shiftValue = shiftValue;

}

// samotny find
int find(char str[], char search[]) {

	int i = 0;
	char item;
	int found = -1;
	int others = strLength(search);
	int stop = -1; // zarazka
	int shiftValue = others; // prvotni nastaveni shiftu

	if (others == 0) {
		return 0;
	} else if (strLength(str) < strLength(search)) {
		return found;
	}

	mismatchTable Table;
	initMismatchTable(&Table);
	//printf("mismatch table inicializovana\n");
	// cyklus naplni mismatch Tabulku znaky ze stringu "search"
	while (i < strLength(search)) {
		item = search[i];
		//printf("%d znak: %c\n", i, item);

		//printf("Je novy znak v tabulce? -1 = ne: %d\n", findChar(&Table, item));
		if (findChar(&Table, item) == -1) {
			if (search[i+1] != '\0') { // pokud toto neni posledni prvek
				insertNext(&(Table), item, strLength(search) - i - 1);
			} else { // jinak nastavime shift posledniho prvku dle boyer-moore algoritmu
				insertNext(&(Table), item, others);
			}
			//printf("Je znak v tabulce na pozici 0? Pokud ano, je tam: %d\n", findChar(&Table, item));
		} else {
			updateShift(&(Table), item, (strLength(search)-i-1));
		}
		i++;
	}

	i = 0; // jen pro jistotu

	//printf("Tabulka byla naplnena, nyni provedeme vyhledavani\n");
	while ((found == -1) && (stop < strLength(str))) { // dokud neni string nalezen nebo neni konec stringu nebo neni eof, hledam
		stop += shiftValue;
		//printf("Hodnota zarazky? %d\n", stop);

		for (i = 0; i < others; i++) {
			if (str[stop-i] == search[others-i-1]) {
				if (str[stop-others+1] == search[0]) {
					found = stop-others+1;
					break;
				}
			} else {
				if (findChar(&Table, str[stop-i]) == -1) {
					shiftValue = others;
				} else {
					shiftValue = getShiftValue(&(Table), str[stop-i]);
				}
				break;
			}
		}

	}

	disposeMismatchTable(&Table);

	if (Table.First == NULL && Table.Act == NULL) {
		//printf("Tabulka je prazdna\n");
	}

	return found;

}
