/*
 * EMTNS - Extended Metadata & Tag Navigation System
 * Copyright (C) 2026  linuxawy
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include "../include/emtns.h"

void get_jpeg_details(const char *filename, JpegInfo *info) {
    FILE *f = fopen(filename, "rb");
    if (!f) return;

    unsigned char buf[4];
    while (fread(buf, 1, 2, f) == 2) {
        if (buf[0] != 0xFF) break;
        unsigned char marker = buf[1];
        if (marker == 0xD8) continue;
        if (marker == 0xD9 || marker == 0xDA) break;

        unsigned char len_buf[2];
        if (fread(len_buf, 1, 2, f) != 2) break;
        int len = (len_buf[0] << 8) + len_buf[1];

        if (marker == 0xC0 || marker == 0xC1 || marker == 0xC2) {
            info->precision = fgetc(f);
            info->height = (fgetc(f) << 8) + fgetc(f);
            info->width = (fgetc(f) << 8) + fgetc(f);
            info->components = fgetc(f);
            snprintf(info->color_process, 64, "%s", (marker == 0xC0) ? "Baseline DCT, Huffman coding" : "Progressive DCT");
            break; 
        } else {
            fseek(f, len - 2, SEEK_CUR);
        }
    }
    fclose(f);
}

const char* get_mime_type(const char *filename) {
    if (strstr(filename, ".jpg") || strstr(filename, ".jpeg") || strstr(filename, ".JPG")) return "image/jpeg";
    if (strstr(filename, ".png") || strstr(filename, ".PNG")) return "image/png";
    return "image/unknown";
}