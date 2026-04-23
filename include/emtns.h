/*
 * EMTNS - Extended Metadata & Tag Navigation System
 * Copyright (C) 2026  linuxawy
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#ifndef EMTNS_H
#define EMTNS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <libexif/exif-data.h>
#include <libexif/exif-content.h>

#define EMTNS_VER "1.0.0"

typedef struct {
    int width;
    int height;
    int precision;
    int components;
    char color_process[64];
} JpegInfo;

// Function Prototypes
void process_image(const char *filename);
void get_jpeg_details(const char *filename, JpegInfo *info);
const char* get_mime_type(const char *filename);
void entry_callback(ExifEntry *entry, void *user_data);
void content_callback(ExifContent *content, void *user_data);

#endif