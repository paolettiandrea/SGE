#!/usr/bin/env bash

# Simple script for exporting SGE readable objects from blender files
# Takes only one argument, a path to a .blend file or to a directory:
# - if the path points to a file exports it in its same dir
# - if the path points to a directory explore recursivelly down the folder exporting in the same way every .blend file found


# Function that opens the given blender file and executes the python script where the actual export logic is
export_blend_file() {
  script_full_path=$(dirname "$0")
  echo "$script_full_path"
  blender --background "$1" --python "$script_full_path/sgexport.py"
}


if [ -f "$1" ]
then
  if [[ "$1" == *.blend ]]
  then
    export_blend_file "$1"
  else
    echo "ERROR: the given file wasn't a .blend"
  fi
else
  if [ -d "$1" ]
  then
      echo "The given path is a directory, exporting recursivelly every .blend file inside it"
      while IFS= read -r -d '' file
      do
        export_blend_file "$file"
      done < <(find "$1" -name "*.blend" -print0)
  else
    echo "ERROR: the given argument wasn't a path to a file or a directory"
  fi
fi





