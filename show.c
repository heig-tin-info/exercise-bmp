#include <stdio.h>

int int_at(FILE *fp, int offset) {
    int data;
    int old_offset = ftell(fp);
    fseek(fp, offset, SEEK_SET);
    fread(&data, sizeof(int), 1, fp);
    fseek(fp, old_offset, SEEK_SET);
    return data;
}

char img[64][64][3];

int main(int argc, char *argv[]) {
    if (argc < 2) return 2;

    FILE *fp = fopen(argv[1], "r");

    int height = int_at(fp, 22), width = int_at(fp, 18);
    fprintf(stderr, "Image size: %d x %d pixels\n", width, height);
    if (int_at(fp, 28) != 24) {
        fprintf(stderr, "Error: Not a 24-bit image!\n");
        return 1;
    }

    int end = int_at(fp, 0x22) + int_at(fp, 0xa);
    fseek(fp, int_at(fp, 0xa), SEEK_SET);

    int k = 0;
    while(ftell(fp) < end) {
        char r, g, b;
        fread(&b, 1, 1, fp);
        fread(&g, 1, 1, fp);
        fread(&r, 1, 1, fp);
        printf("\033[48;2;%u;%u;%um  \033[0m", r, g, b);

        if (k++ % width == 0) printf("\n");
    }
}