# Ratakor's build of dwm

## patch added and changes iirc
- attach aside
- rainbow tab
- dracula theme
- alpha (transparency)
- quitprompt (Super + Shift + E)
- bartab (all app are shown in status bar and have an optional border)
- 3 layouts, tile, bottom stack and floating
- true fullscreen with Super + F
- color in status bar
- statusbar on all monitors
- cycle layouts
- smartborders
- high priority patch for dmenu_run, set up with DMENUHP env variable (add something like `export DMENUHP="chromium,st"` to your .profile)

- bindings are set for [st](https://git.ratakor.com/st.git) and my [scripts](https://git.ratakor.com/dotfiles.git/tree/.local/bin)
- modify line 106 and 107 in config.h to match with your version of dmenu otherwise use [mine](https://git.ratakor.com/dmenu.git)
- the man page is not up to date

---

dwm - dynamic window manager
============================
dwm is an extremely fast, small, and dynamic window manager for X.


Requirements
------------
In order to build dwm you need the Xlib header files.


Installation
------------
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install


Running dwm
-----------
Add the following line to your .xinitrc to start dwm using startx:

    exec dwm

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
    	sleep 1
    done &
    exec dwm


Configuration
-------------
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.
