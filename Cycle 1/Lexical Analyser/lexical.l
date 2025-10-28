#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isKeyword(char *w) {
    char *kw[] = {"auto","break","case","char","const","continue","default","do","double","else","enum",
                  "extern","float","for","goto","if","int","long","register","return","short","signed",
                  "sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while"};
    for (int i = 0; i < 32; i++) if (!strcmp(w, kw[i])) return 1;
    return 0;
}

int isOperator(char c) { return strchr("+-*/%=<>!", c) != NULL; }
int isSeparator(char c) { return strchr("(){}[];,#", c) != NULL; }

int main() {
    char file[30], ch, buf[50]; int j = 0;
    printf("Enter file name: "); scanf("%s", file);
    FILE *fp = fopen(file, "r");
    if (!fp) return printf("File not found.\n"), 1;

    while ((ch = fgetc(fp)) != EOF) {

        if (isalnum(ch) || ch == '_') buf[j++] = ch;
        else {
            if (j) {
                buf[j] = '\0';
                printf("%s is a %s.\n", buf, isKeyword(buf) ? "keyword" : "identifier");
                j = 0;
            }
            if (!isspace(ch)) { 
                if (isOperator(ch)) printf("%c is an operator.\n", ch);
                else if (isSeparator(ch)) printf("%c is a separator.\n", ch);
            }
        }
    }

    if (j > 0) {
        buf[j] = '\0';
        printf("%s is a %s.\n", buf, isKeyword(buf) ? "keyword" : "identifier");
    }

    fclose(fp);
    return 0;
}

/*
input.txt
-------------------------
void main()
{
	int num1, num2, num3;
	num3 = num1/num2;
}
*/
