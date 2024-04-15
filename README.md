# multidesk

**multidesk** is a set of scripts which allows the user to launch a desktop of their choice after logging in via tty. It's kinda like a desktop manager.

## But why?

This is less bloat than a desktop manager.

This allows the user to try out different Xorg desktops without editing the xinitrc for switching. Switching desktops also becomes easier in general.

This should also make it easier to create a new rice without the danger to possibly destroy the current desktop configurations.

## Setup

Desktop configuations should be stored in a directory `$DESKTOP_LIST`. This is recommended to point to `$HOME/.config/desktops`. An example of how `$DESKOP_LIST` may look like is provided in the [`skel`](skel/) directory in the git repository.

Each non-hidden sub directory in `$DESKOP_LIST` stores the configuration files of a desktop. The entry point is always `main.sh`, which may call other programs or source other configuration files. `greet.sh` is optionally a shell file which can be sourced from the shell profile (i.e. `.bashrc`, `.zshrc` or `.profile`).

The `desktop` and `get_login` scripts and the `desktopstarter` program are best installed on the `$PATH`. To build `desktopstarter`, type `make -C desktopstarter` in the root directory of this repository.

After the installation of `desktop` and `desktopstarter`, it is recommended to append the shell profile with the following lines:

```bash
if [ -n "$DISPLAY" ] || [ -n "$WAYLAND_DISPLAY" ]; then
	desktop="$(cat $XDG_CONFIG_HOME/desktops/.loaded)"
	. $XDG_CONFIG_HOME/desktops/$desktop/greet.sh
	unset desktop
elif [ -z "$DESKTOP_STARTED" ]; then
	exec desktopstarter
else
	# Set `PS1` environment variable here etc.
	# This is run whenever the fallback shell is called.
fi
```

## Usage

### `desktopstarter`

If you followed the above instructions, you should probably never call `desktopstarter` manually.

### `desktop`

`desktop -l` will list all available desktops and exit.

`desktop <your-chosen-desktop>` will start a desktop of your choice.
