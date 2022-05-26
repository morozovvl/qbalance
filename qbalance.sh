#!/bin/sh
# Copyright BlackTulipConfidence (BTC)
 
#
############################################################
# This Unix-sh script has two purposes:
# 1. it is meant to set LD_LIBRARY_PATH
# to the directory this scripts is in
# before to start an application. In
# this way all shared objects needed by
# the application can be put in the application dir.
# The bare filename of this script should coincide with
# the bare filename of the application. In the present
# form this script and application should reside in the
# same directory.
#
# 2. this script will also generate a desktop file
# that can be used as a trigger to start the
# application. As a result this script will then
# not be necessary anymore
#
############################################################
# Absolute file path to this script
SCRIPT=$(readlink -f "$0")
# Absolute directory path where this script is in
SCRIPTPATH=$(dirname "$SCRIPT")
export LD_LIBRARY_PATH="$SCRIPTPATH"/"lib64"
filename=$(basename "$0")
extension="${filename##*.}"
filename="${filename%.*}"
desktop_filename="$SCRIPTPATH""/""$filename"".desktop"
script_filename="$SCRIPTPATH"/"$filename"".sh"
exec_filename="$SCRIPTPATH"/"$filename"
iconfilename="$SCRIPTPATH"/"resources"/"$filename"".png"
 
# rm -fv "$desktop_filename"
cat << EOF > "$desktop_filename"
#!/usr/bin/env xdg-open
[Desktop Entry]
Type=Application
Name=QBalance
Exec=$script_filename
Version=1.0
Encoding=UTF-8
GenericName=$filename
Comment=
Icon=$iconfilename
Path=
Terminal=
MimeType=application/x-executable
Categories=Other
EOF
chmod 777 $desktop_filename
$exec_filename