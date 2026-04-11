#include <stdlib.h>
#include <uchar.h>
#include <locale.h>
#include <assert.h>

#define PCMIO_IMPLEMENTATION
#include "pcmio.h"

#define WIDTH 1000
#define HEIGHT 1000

int main() {
    setlocale(LC_ALL, "en_US.utf8");

    printf("Create/Write Tests:\n");
    fflush(stdout);

    // Create .PCM File Test
    PCMFile* pcm = pcmio_new(WIDTH, HEIGHT, 255);
    
    for (unsigned long i = 0; i < pcm->width * pcm->height; i++) {
        if (pcm->cells[i].character != '\0') {
            return 1;
        }

        PCMColorRGBA no_color = {0, 0, 0, 0};

        if (pcm->cells[i].foreground.r != no_color.r) {
            return 1;
        }

        if (pcm->cells[i].foreground.g != no_color.g) {
            return 1;
        }

        if (pcm->cells[i].foreground.b != no_color.b) {
            return 1;
        }

        if (pcm->cells[i].foreground.a != no_color.a) {
            return 1;
        }

        if (pcm->cells[i].background.r != no_color.r) {
            return 1;
        }

        if (pcm->cells[i].background.g != no_color.g) {
            return 1;
        }

        if (pcm->cells[i].background.b != no_color.b) {
            return 1;
        }

        if (pcm->cells[i].background.a != no_color.a) {
            return 1;
        }

        PCMColorRGBA new_color = {255, 255, 255, 255};

        pcm->cells[i] = pcmio_newcell(U'ß',
            255, 255, 255, 255,
            255, 255, 255, 255
        );

        if (pcm->cells[i].character != U'ß') {
            return 1;
        }

        if (pcm->cells[i].foreground.r != new_color.r) {
            return 1;
        }

        if (pcm->cells[i].foreground.g != new_color.g) {
            return 1;
        }

        if (pcm->cells[i].foreground.b != new_color.b) {
            return 1;
        }

        if (pcm->cells[i].foreground.a != new_color.a) {
            return 1;
        }

        if (pcm->cells[i].background.r != new_color.r) {
            return 1;
        }

        if (pcm->cells[i].background.g != new_color.g) {
            return 1;
        }

        if (pcm->cells[i].background.b != new_color.b) {
            return 1;
        }

        if (pcm->cells[i].background.a != new_color.a) {
            return 1;
        }
    }

    //pcmio_print(pcm);

    pcmio_write(pcm, "./test.pcm");

    printf("Create/Write Tests Successful\n");
    printf(" ----- \n");
    printf("Open Tests:\n");
    fflush(stdout);

    // Open .PCM File Test

    PCMFile* pcm2 = pcmio_open("./test.pcm");

    //pcmio_print(pcm2);

    if (pcm2->width != WIDTH) {
        return 1;
    }

    if (pcm2->height != HEIGHT) {
        return 1;
    }

    for (unsigned long i = 0; i < pcm2->width * pcm2->height; i++) {
        PCMColorRGBA new_color = {255, 255, 255, 255};

        if (pcm2->cells[i].character != U'ß') {
            return 1;
        }

        if (pcm2->cells[i].foreground.r != new_color.r) {
            return 1;
        }

        if (pcm2->cells[i].foreground.g != new_color.g) {
            return 1;
        }

        if (pcm2->cells[i].foreground.b != new_color.b) {
            return 1;
        }

        if (pcm2->cells[i].foreground.a != new_color.a) {
            return 1;
        }

        if (pcm2->cells[i].background.r != new_color.r) {
            return 1;
        }

        if (pcm2->cells[i].background.g != new_color.g) {
            return 1;
        }

        if (pcm2->cells[i].background.b != new_color.b) {
            return 1;
        }

        if (pcm2->cells[i].background.a != new_color.a) {
            return 1;
        }
    }

    printf("Open Tests Successful\n");
    printf(" ----- \n");
    printf("Read Tests:\n");
    fflush(stdout);

    // Read .PCM Buffer Test

    FILE* fp = fopen("./test.pcm", "rb");
    fseek(fp, 0L, SEEK_END);
    unsigned long file_size = ftell(fp);
    rewind(fp);
    char* buffer = (char*) malloc(sizeof(char) * file_size);
    fread(buffer, file_size, 1, fp);
    fclose(fp);

    PCMFile* pcm3 = pcmio_read(buffer);

    //pcmio_print(pcm3);

    if (pcm3->width != WIDTH) {
        return 1;
    }

    if (pcm3->height != HEIGHT) {
        return 1;
    }

    for (unsigned long i = 0; i < pcm3->width * pcm3->height; i++) {
        PCMColorRGBA new_color = {255, 255, 255, 255};

        if (pcm3->cells[i].character != U'ß') {
            return 1;
        }

        if (pcm3->cells[i].foreground.r != new_color.r) {
            return 1;
        }

        if (pcm3->cells[i].foreground.g != new_color.g) {
            return 1;
        }

        if (pcm3->cells[i].foreground.b != new_color.b) {
            return 1;
        }

        if (pcm3->cells[i].foreground.a != new_color.a) {
            return 1;
        }

        if (pcm3->cells[i].background.r != new_color.r) {
            return 1;
        }

        if (pcm3->cells[i].background.g != new_color.g) {
            return 1;
        }

        if (pcm3->cells[i].background.b != new_color.b) {
            return 1;
        }

        if (pcm3->cells[i].background.a != new_color.a) {
            return 1;
        }
    }

    printf("Read Tests Successful\n");
    fflush(stdout);

    return 0;
}