#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

bool match_keyword(FILE* f, const char* keyword) {
    // Checks if the next characters in the file match `keyword`
    while (*keyword) {
        char c = fgetc(f);
        if (c != *keyword) {
            return false;
        }
        keyword++;
    }
    return true;
}

int parse_number(FILE* f) {
    // Parses an integer from the file
    int num = 0;
    char c;
    while ((c = fgetc(f)) != EOF && isdigit(c)) {
        num = num * 10 + (c - '0');
    }
    ungetc(c, f); // Push back the last non-digit character
    return num;
}

int main() {
    FILE* f = fopen("input", "r");
    if (f == NULL) {
        perror("Error opening file");
        return 1;
    }

    char c;
    int n1 = 0, n2 = 0, m = 0;
    bool b = true;

    while ((c = fgetc(f)) != EOF) {
        if (c == 'm' && match_keyword(f, "ul(")) {
            // Parse first number
            n1 = parse_number(f);
            if (fgetc(f) == ',' && (n2 = parse_number(f)) && fgetc(f) == ')') {
                if (b) {
                    m += n1 * n2;
                }
            }
        } else if (c == 'd') {
            if (match_keyword(f, "o()")) {
                b = true;
            } else if (match_keyword(f, "on't()")) {
                b = false;
            }
        }
    }

    fclose(f);

    printf("The answer to the mul problem is %d\n", m);
    return 0;
}
