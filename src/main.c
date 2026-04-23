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

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: emtns <image_file>\n");
        return 1;
    }
    process_image(argv[1]);
    return 0;
}