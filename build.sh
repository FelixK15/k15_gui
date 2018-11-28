#!/bin/bash
clang x11_example.c -g -o x11_gui_example.out -L/usr/X11/lib -lX11 -lGL -lm
