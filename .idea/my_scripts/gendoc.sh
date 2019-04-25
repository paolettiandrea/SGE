#!/usr/bin/env bash
# Script for automating the generation of the project's documentation
# Expects the cwd to be the base dir of the project

rm -drf ./doc/generated/*
./.doxygen/m.css/doxygen/dox2html5.py ./.doxygen/Doxyfile-mcss