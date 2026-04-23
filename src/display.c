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

void entry_callback(ExifEntry *entry, void *user_data) {
    char buf[1024];
    const char *tag = exif_tag_get_name(entry->tag);
    const char *value = exif_entry_get_value(entry, buf, sizeof(buf));
    if (tag && value && value[0] != '\0') {
        printf("%-31s : %s\n", tag, value);
    }
}

void content_callback(ExifContent *content, void *user_data) {
    exif_content_foreach_entry(content, (ExifContentForeachEntryFunc)entry_callback, user_data);
}

void process_image(const char *filename) {
    struct stat st;
    if (stat(filename, &st) != 0) {
        perror("Error opening file");
        return;
    }

    JpegInfo jf = {0};
    get_jpeg_details(filename, &jf);

    printf("Emtns Version Number         : %s\n", EMTNS_VER);
    printf("File Name                       : %s\n", filename);
    printf("File Size                       : %.1f MB\n", (double)st.st_size / (1024 * 1024));
    
    char t[64];
    strftime(t, sizeof(t), "%Y:%m:%d %H:%M:%S", localtime(&st.st_mtime));
    printf("File Modification Date/Time     : %s\n", t);
    printf("File Permissions                : %o\n", st.st_mode & 0777);
    printf("File Type                       : JPEG\n");
    printf("MIME Type                       : %s\n", get_mime_type(filename));
    
    if (jf.width > 0) {
        printf("Image Width                     : %d\n", jf.width);
        printf("Image Height                    : %d\n", jf.height);
        printf("Encoding Process                : %s\n", jf.color_process);
        printf("Bits Per Sample                 : %d\n", jf.precision);
        printf("Color Components                : %d\n", jf.components);
        printf("Image Size                      : %dx%d\n", jf.width, jf.height);
        printf("Megapixels                      : %.1f\n", (double)(jf.width * jf.height) / 1000000);
    }

    ExifData *ed = exif_data_new_from_file(filename);
    if (ed) {
        exif_data_foreach_content(ed, (ExifDataForeachContentFunc)content_callback, NULL);
        exif_data_unref(ed);
    }
}