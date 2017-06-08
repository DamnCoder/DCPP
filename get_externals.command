#!/bin/sh

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
if [ ! -d ./externals ]; then
	mkdir externals
fi

cd externals

if [ ! -d ./dcpp_signals ]; then
	git clone https://github.com/DamnCoder/dcpp_signals.git
else
	cd dcpp_signals
	git config --global alias.up '!git remote update -p; git merge --ff-only @{u}'
	git checkout development && git up
fi

if [ ! -d ./dcpp_math ]; then
	git clone https://github.com/DamnCoder/dcpp_math.git
else
	cd dcpp_math
	git config --global alias.up '!git remote update -p; git merge --ff-only @{u}'
	git checkout development && git up
fi

