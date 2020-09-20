#!/bin/sh

files=('.vimrc' '.tmux.conf' '.zshrc' '.xinitrc')

for i in {1..50}
do
  ./client "$HOME/${files[i%5]}" & 
done

wait
