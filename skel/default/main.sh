#!/bin/sh

# This is the entry point for the desktop.
#
# 1. Start a few services.
# 2. Start the desktop itself.

dsv $(which pipewire) &
dsv $(which pipewire-pulse) &
dsv $(which wireplumber) &
exec sway -c $(dirname $0)/config
