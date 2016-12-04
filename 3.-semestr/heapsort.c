
// swap pro heapsort
void swap(char *a, char *b) {
	//printf("Bude prohozen znak %c a %c \n", *a, *b);
	char c = *a;
	*a = *b;
	*b = c;
}

// pomocna funkce makeEven pro zjednoduseni vypoctu pozice prvku
int makeEven(int i) {
	if ((i % 2) != 0) {
		i += 1;
	}
	return i;
}

// fce pro korektni nastaveni pozice nejvetsiho prvku na zacatek haldy
char *repairHeap(char str[], int length) {

	int i = 0, isBiggestNotAtTop = 1;

	char biggestChar = '\0';
	int strlength = length;

	while (strlength) {
		if (str[i] > biggestChar) {
			biggestChar = str[i];
		}
		i++;
		strlength--;
	}

	i = 0;
	for (i = length-1; i >= 0; i--) {


		isBiggestNotAtTop = 0;
		//printf("Slovo str nyni vypada takto: %s\n", str);
		//printf("Znak na pozici %d je %c\n",i,str[i]);

		if (biggestChar == str[0]) {
			return str;
		}


		if ((i % 2) == 0) {
			if ((str[i] > str[(makeEven(i)/2)-1]) && (str[i-1] > str[(makeEven(i)/2)-1])) {
				isBiggestNotAtTop = 1;
				if (str[i] >= str[i-1]) {
					swap(&str[i], &str[(makeEven(i)/2)-1]);
				} else {
					swap(&str[i-1], &str[(makeEven(i)/2)-1]);
				}
				//printf("SUDE I: I je: %d a zesudele I je: %d\n", i, makeEven(i));
			}
			if (str[i] > str[(makeEven(i)/2)-1]) {
				isBiggestNotAtTop = 1;
				swap(&str[i], &str[(makeEven(i)/2)-1]);
				//printf("SUDE II: I je: %d a zesudele I je: %d\n", i, makeEven(i));
			}
		} else {
			if (str[i] > str[(makeEven(i)/2)-1]) {
				isBiggestNotAtTop = 1;
				swap(&str[i], &str[(makeEven(i)/2)-1]);
			}
			//printf("LICHE I: I je: %d a zesudele I je: %d\n", i, makeEven(i));
		}
	}

	if (isBiggestNotAtTop == 1)
		repairHeap(str, length);

	return str;
}


// samotny heapsort
char * sort(char str[]) {
	char *helpString = str;

	int length = strLength(helpString);
	while (length) {

		repairHeap(helpString, length);

		swap(&helpString[0], &helpString[length-1]);

		length--;
	}

	return helpString;
}

