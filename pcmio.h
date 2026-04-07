/*
* pcmio.h - Portable Character Map I/O library - VERSION 1
*
* USAGE:
* Put '#define PCMIO_IMPLEMENTATION' in one of the source files 
*  that include this library before the '#include "pcmio.h"' statement.
*
* .PCM files are formatted into cells similarly to pixels or bits in a .PBM or .PPM file.
*
* Each cell contains a u32 formatted character and a foreground and background color in RGBA32.
*
* PCMFile instances can be created with pcmio_new() and modified/read with either the get/set functions or directly.
* 
* Use pcmio_write() to write PCMFile instances to file or pcmio_open() to read a .PCM file into a new PCMFile instance.
*
* CREDITS:
*  Alexandria Hollingsworth
*
* CHANGELOG:
*  N/A
*
* LICENSE:
*  See the end of this file for license information.
*
*/

#ifndef PCMIO_H
#define PCMIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <uchar.h> // char32_t

#define PCMIO_VERSION 1

/**
* .PCM RGBA color structure.
*/
typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} PCMColorRGBA;

/**
* .PCM cell structure.
*/
typedef struct {
    char32_t character;
    PCMColorRGBA foreground;
    PCMColorRGBA background;
} PCMCell;

/**
* .PCM file structure.
*/
typedef struct {
    unsigned short width;
    unsigned short height;
    unsigned char max_color;
    PCMCell* cells;
} PCMFile;

/**
* Creates a PCMCell with the given character and color values.
* @param c Character to be stored in the PCMCell.
* @param fg_r Foreground color red component.
* @param fg_g Foreground color green component.
* @param fg_b Foreground color blue component.
* @param fg_a Foreground color alpha component.
* @param bg_r Background color red component.
* @param bg_g Background color green component.
* @param bg_b Background color blue component.
* @param bg_a Background color alpha component.
*/
#define pcmio_newcell(c, fg_r, fg_g, fg_b, fg_a, bg_r, bg_g, bg_b, bg_a) _Generic((c),\
    char: pcmio_newcellascii,\
    char32_t: pcmio_newcell32,\
    char16_t: pcmio_newcell16,\
    char8_t: pcmio_newcell8)\
    (c, fg_r, fg_g, fg_b, fg_a, bg_r, bg_g, bg_b, bg_a)
static PCMCell pcmio_newcellascii(const char c, 
unsigned char fg_r, unsigned char fg_g, unsigned char fg_b, unsigned char fg_a, 
unsigned char bg_r, unsigned char bg_g, unsigned char bg_b, unsigned char bg_a);
static PCMCell pcmio_newcell32(const char32_t c, 
unsigned char fg_r, unsigned char fg_g, unsigned char fg_b, unsigned char fg_a, 
unsigned char bg_r, unsigned char bg_g, unsigned char bg_b, unsigned char bg_a);
static PCMCell pcmio_newcell16(const char16_t c, 
unsigned char fg_r, unsigned char fg_g, unsigned char fg_b, unsigned char fg_a, 
unsigned char bg_r, unsigned char bg_g, unsigned char bg_b, unsigned char bg_a);
static PCMCell pcmio_newcell8(const char8_t c, 
unsigned char fg_r, unsigned char fg_g, unsigned char fg_b, unsigned char fg_a, 
unsigned char bg_r, unsigned char bg_g, unsigned char bg_b, unsigned char bg_a);


/**
* Gets the character of a single cell in the given PCMFile instance.
* @param pcm Pointer to the PCMFile instance.
* @param x X-coordinate of the cell.
* @param y Y-coordinate of the cell.
* @return UTF-32 character stored in the cell with the given coordinates.
*/
static char32_t pcmio_getchar(PCMFile* pcm, const unsigned short x, const unsigned short y);

/**
* Sets the character of a single cell in the given PCMFile instance.
* @param pcm Pointer to the PCMFile instance.
* @param x X-coordinate of the cell.
* @param y Y-coordinate of the cell.
* @param c Character to be stored in the cell.
*/
#define pcmio_setchar(pcm, x, y, c) _Generic((c),\
    char: pcmio_setcharascii,\
    char32_t: pcmio_setchar32,\
    char16_t: pcmio_setchar16,\
    char8_t: pcmio_setchar8)\
    (pcm, x, y, c)
static void pcmio_setcharascii(PCMFile* pcm, const unsigned short x, const unsigned short y, const char c);
static void pcmio_setchar32(PCMFile* pcm, const unsigned short x, const unsigned short y, const char32_t c);
static void pcmio_setchar16(PCMFile* pcm, const unsigned short x, const unsigned short y, const char16_t c);
static void pcmio_setchar8(PCMFile* pcm, const unsigned short x, const unsigned short y, const char8_t c);

/**
* Gets the foreground color of a single cell in the given PCMFile instance.
* @param pcm Pointer to the PCMFile instance.
* @param x X-coordinate of the cell.
* @param y Y-coordinate of the cell.
* @return RGBA values of the foreground color of the cell at the given coordinates.
*/
static PCMColorRGBA pcmio_getfg(PCMFile* pcm, const unsigned short x, const unsigned short y);

/**
* Sets the foreground color of a single cell in the given PCMFile instance.
* @param pcm Pointer to the PCMFile instance to be modified.
* @param x X-coordinate of the cell to modify.
* @param y Y-coordinate of the cell to modify.
* @param fg_r Foreground color red component.
* @param fg_g Foreground color green component.
* @param fg_b Foreground color blue component.
* @param fg_a Foreground color alpha component.
*/
static void pcmio_setfg(PCMFile* pcm, const unsigned short x, const unsigned short y,
unsigned char fg_r, unsigned char fg_g, unsigned char fg_b, unsigned char fg_a);

/**
* Gets the background color of a single cell in the given PCMFile instance.
* @param pcm Pointer to the PCMFile instance.
* @param x X-coordinate of the cell.
* @param y Y-coordinate of the cell.
* @return RGBA values of the background color of the cell at the given coordinates.
*/
static PCMColorRGBA pcmio_getbg(PCMFile* pcm, const unsigned short x, const unsigned short y);

/**
* Sets the background color of a single cell in the given PCMFile instance.
* @param pcm Pointer to the PCMFile instance to be modified.
* @param x X-coordinate of the cell to modify.
* @param y Y-coordinate of the cell to modify.
* @param bg_r Background color red component.
* @param bg_g Background color green component.
* @param bg_b Background color blue component.
* @param bg_a Background color alpha component.
*/
static void pcmio_setbg(PCMFile* pcm, const unsigned short x, const unsigned short y,
unsigned char bg_r, unsigned char bg_g, unsigned char bg_b, unsigned char bg_a);

/**
* Creates a new PCMFile instance with the given width, height, and max color.
* @param width Width, in cells/characters, of the new PCMFile instance.
* @param height Height, in cells/characters, of the new PCMFile instance.
* @param max_color Maximum color value of the new PCMFile instance, must be less than 256.
* @return Pointer to the newly-created PCMFile instance.
*/
static PCMFile* pcmio_new(const unsigned short width, const unsigned short height, const unsigned char max_color);

/**
* Serializes a PCMFile instance with the given filename.
* @param pcm PCMFile instance to serialize. 
* @param filename Name of the serialized .PCM file.
*/
static void pcmio_write(PCMFile* pcm, char* filename);

/**
* Deserializes a .PCM file into a PCMFile instance.
* @param path Path of the .PCM file.
*/
static PCMFile* pcmio_open(const char* path);

/**
* Frees memory allocated by a PCMFile.
* @param pcm PCMFile instance to close.
*/
static void pcmio_close(PCMFile* pcm);

/**
* Prints information about a PCMFile instance for debugging.
* @param pcm PCMFile instance to print information for.
*/
static void pcmio_print(PCMFile* pcm);

#ifdef __cplusplus
}
#endif

#endif /* PCMIO_H */

#ifdef PCMIO_IMPLEMENTATION

#include <stdio.h> // fopen(), fseek(), fwrite(), fread(), fclose()
#include <stdlib.h> // malloc(), free()

#define PCMHead "P-1"

static PCMCell pcmio_newcellascii(const char c, 
unsigned char fg_r, unsigned char fg_g, unsigned char fg_b, unsigned char fg_a, 
unsigned char bg_r, unsigned char bg_g, unsigned char bg_b, unsigned char bg_a) {
    char32_t c_32;
    mbstate_t state = {0};

    mbrtoc32(&c_32, &c, 4, &state);

    PCMCell new_cell = {c_32,
        {fg_r, fg_g, fg_b, fg_a},
        {bg_r, bg_g, bg_b, bg_a}
    };

    return new_cell;
}

static PCMCell pcmio_newcell32(const char32_t c, 
unsigned char fg_r, unsigned char fg_g, unsigned char fg_b, unsigned char fg_a, 
unsigned char bg_r, unsigned char bg_g, unsigned char bg_b, unsigned char bg_a) {
    PCMCell new_cell = {c,
        {fg_r, fg_g, fg_b, fg_a},
        {bg_r, bg_g, bg_b, bg_a}
    };

    return new_cell;
}

static PCMCell pcmio_newcell16(const char16_t c, 
unsigned char fg_r, unsigned char fg_g, unsigned char fg_b, unsigned char fg_a, 
unsigned char bg_r, unsigned char bg_g, unsigned char bg_b, unsigned char bg_a) {
    char* mbc = (char*) malloc(2);
    mbstate_t state = {0};
    c16rtomb(mbc, c, &state);
    
    char32_t c_32;

    mbrtoc32(&c_32, mbc, 4, &state);
    free(mbc);

    PCMCell new_cell = {c_32,
        {fg_r, fg_g, fg_b, fg_a},
        {bg_r, bg_g, bg_b, bg_a}
    };

    return new_cell;
}

static PCMCell pcmio_newcell8(const char8_t c, 
unsigned char fg_r, unsigned char fg_g, unsigned char fg_b, unsigned char fg_a, 
unsigned char bg_r, unsigned char bg_g, unsigned char bg_b, unsigned char bg_a) {
    char* mbc = (char*) malloc(1);
    mbstate_t state = {0};
    c8rtomb(mbc, c, &state);
    
    char32_t c_32;

    mbrtoc32(&c_32, mbc, 4, &state);
    free(mbc);

    PCMCell new_cell = {c_32,
        {fg_r, fg_g, fg_b, fg_a},
        {bg_r, bg_g, bg_b, bg_a}
    };

    return new_cell;
}

static char32_t pcmio_getchar(PCMFile* pcm, const unsigned short x, const unsigned short y) {
    return pcm->cells[(y * pcm->width) + x].character;
}

static void pcmio_setcharascii(PCMFile* pcm, const unsigned short x, const unsigned short y, const char c) {
    char32_t c_32;
    mbstate_t state = {0};

    mbrtoc32(&c_32, &c, 4, &state);

    pcm->cells[(y * pcm->width) + x].character = c_32;
}

static void pcmio_setchar32(PCMFile* pcm, const unsigned short x, const unsigned short y, const char32_t c) {
    pcm->cells[(y * pcm->width) + x].character = c;
}

static void pcmio_setchar16(PCMFile* pcm, const unsigned short x, const unsigned short y, const char16_t c) {
    char* mbc = (char*) malloc(2);
    mbstate_t state = {0};
    c16rtomb(mbc, c, &state);
    
    char32_t c_32;

    mbrtoc32(&c_32, mbc, 4, &state);
    free(mbc);

    pcm->cells[(y * pcm->width) + x].character = c_32;
}

static void pcmio_setchar8(PCMFile* pcm, const unsigned short x, const unsigned short y, const char8_t c) {
    char* mbc = (char*) malloc(1);
    mbstate_t state = {0};
    c8rtomb(mbc, c, &state);
    
    char32_t c_32;

    mbrtoc32(&c_32, mbc, 4, &state);
    free(mbc);

    pcm->cells[(y * pcm->width) + x].character = c_32;
}

static PCMColorRGBA pcmio_getfg(PCMFile* pcm, const unsigned short x, const unsigned short y) {
    return pcm->cells[(y * pcm->width) + x].foreground;
}


static void pcmio_setfg(PCMFile* pcm, const unsigned short x, const unsigned short y,
unsigned char fg_r, unsigned char fg_g, unsigned char fg_b, unsigned char fg_a) {
    PCMColorRGBA new_color = {fg_r, fg_g, fg_b, fg_a};

    pcm->cells[(y * pcm->width) + x].foreground = new_color;
}

static PCMColorRGBA pcmio_getbg(PCMFile* pcm, const unsigned short x, const unsigned short y) {
    return pcm->cells[(y * pcm->width) + x].background;
}

static void pcmio_setbg(PCMFile* pcm, const unsigned short x, const unsigned short y,
unsigned char bg_r, unsigned char bg_g, unsigned char bg_b, unsigned char bg_a) {
    PCMColorRGBA new_color = {bg_r, bg_g, bg_b, bg_a};

    pcm->cells[(y * pcm->width) + x].foreground = new_color;
}

static PCMFile* pcmio_new(const unsigned short width, const unsigned short height, const unsigned char max_color) {
    PCMFile* pcm = (PCMFile*) malloc(sizeof(PCMFile));
    
    pcm->width = width;
    pcm->height = height;
    pcm->max_color = max_color;

    pcm->cells = (PCMCell*) calloc(width * height, sizeof(PCMCell));

    return pcm;
}

static void pcmio_write(PCMFile* pcm, char* filename) {
    FILE* fp = fopen(filename, "wb");
    char head[] = PCMHead;

    fwrite(&head, sizeof(PCMHead), 1, fp);

    fseek(fp, sizeof(PCMHead), 0);
    fwrite(pcm, sizeof(PCMFile), 1, fp);

    fseek(fp, sizeof(PCMFile), 0);
    fwrite(pcm->cells, sizeof(PCMCell), pcm->width * pcm->height, fp);

    fclose(fp);
}

static PCMFile* pcmio_open(const char* path) {
    FILE* fp = fopen(path, "rb");
    PCMFile* pcm = (PCMFile*) malloc(sizeof(PCMFile));

    fseek(fp, sizeof(PCMHead), 0);
    fread(pcm, sizeof(PCMFile), 1, fp);
    pcm->cells = (PCMCell*) malloc(sizeof(PCMCell[pcm->width * pcm->height]));

    fseek(fp, sizeof(PCMFile), 0);
    fread(pcm->cells, sizeof(PCMCell), pcm->width * pcm->height, fp);

    fclose(fp);
    return pcm;
}

static void pcmio_close(PCMFile* pcm) {
    free(pcm->cells);

    free(pcm);
}

static void pcmio_print(PCMFile* pcm) {
    printf(".PCM File\nWidth: %i | Height: %i\n", pcm->width, pcm->height);

    for (int i = 0; i < pcm->width * pcm->height; i++) {

        char* c = (char*) malloc(5);
        mbstate_t state = {0};
        size_t rc = c32rtomb(c, pcm->cells[i].character, &state);
        c[rc] = '\0';

        printf("Cell #%i | Character: '%s' | Foreground: (%i, %i, %i, %i) | Background: (%i, %i, %i, %i)\n", 
            i,
            c,
            pcm->cells[i].foreground.r,
            pcm->cells[i].foreground.g,
            pcm->cells[i].foreground.b,
            pcm->cells[i].foreground.a,
            pcm->cells[i].background.r,
            pcm->cells[i].background.g,
            pcm->cells[i].background.b,
            pcm->cells[i].background.a
        );
    }
}

#endif /* PCMIO IMPLEMENTATION */

/*
* This is free and unencumbered software released into the public domain.
* 
* Anyone is free to copy, modify, publish, use, compile, sell, or
* distribute this software, either in source code form or as a compiled
* binary, for any purpose, commercial or non-commercial, and by any
* means.
* 
* In jurisdictions that recognize copyright laws, the author or authors
* of this software dedicate any and all copyright interest in the
* software to the public domain. We make this dedication for the benefit
* of the public at large and to the detriment of our heirs and
* successors. We intend this dedication to be an overt act of
* relinquishment in perpetuity of all present and future rights to this
* software under copyright law.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
* OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
* 
* For more information, please refer to <https://unlicense.org/>
*/