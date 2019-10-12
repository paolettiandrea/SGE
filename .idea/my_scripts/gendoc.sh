#!/usr/bin/env bash
# Script for automating the generation of the project's documentation
# Expects the cwd to be the base dir of the project

rm -drf ./doc/generated/*
./.doxygen/m.css/documentation/doxygen.py ./.doxygen/Doxyfile-mcss