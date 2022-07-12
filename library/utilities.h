int strsplit(char string[100], char dl, char *splt) {
    int i = 0, j = 0, k = 0, splen = 0;

    for (i = 0; i < strlen(string); i++) {
        if (string[i] != dl) {
            *(splt + k) = string[i];
            k++;
        } else {
            // printf("%s\n", split[j]);
            *(splt + k) = '\0';
            splen++;
            j += 100;
            k = j;
        }
    }

    splen++;
    return splen;
}

int strinsen(char palavra[100], char strvet[100][100]) {
    int i;

    for (i = 0; i < sizeof(strvet)/sizeof(char); i++) {
        if (strcmp(strvet[i], palavra) == 0) {
            return 1;
        }
    }

    return 0;
}
