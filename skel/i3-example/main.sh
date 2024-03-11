#!/bin/bash

cd
export XINITRC=$(dirname $0)/xinitrc
exec startx
