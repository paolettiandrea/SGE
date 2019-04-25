#!/usr/bin/env bash
# Script that simply opens the Doxygen documentation in a nuw instance of firefox
# Expects the cwd to be the base dir of the project

firefox -new-window ./doc/generated/html/index.html

