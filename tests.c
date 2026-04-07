#include <stdlib.h>
#include <uchar.h>
#include <locale.h>
#include <assert.h>

#define PCMIO_IMPLEMENTATION
#include "pcmio.h"

int main() {
    setlocale(LC_ALL, "en_US.utf8");

    // Create .PCM File Test
    PCMFile* pcm = pcmio_new(4, 4, 255);
    
    for (int i = 0; i < pcm->width * pcm->height; i++) {
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

    pcmio_print(pcm);

    pcmio_write(pcm, "./test.pcm");

    printf("Create/Write Tests Successful\n");

    // Read .PCM File Test

    PCMFile* pcm2 = pcmio_open("./test.pcm");

    pcmio_print(pcm2);

    if (pcm2->width != 4) {
        return 1;
    }

    if (pcm2->height != 4) {
        return 1;
    }

    for (int i = 0; i < pcm2->width * pcm2->height; i++) {
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

    printf("Read Tests Successful\n");

    return 0;
}