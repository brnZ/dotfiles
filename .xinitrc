#!/bin/sh
#
# ~/.xinitrc
#
# Executed by startx (run your window manager from here)

if [ -d /etc/X11/xinit/xinitrc.d ]; then
    for f in /etc/X11/xinit/xinitrc.d/*; do
        [ -x "$f" ] && . "$f"
    done
    unset f
fi

# exec gnome-session
# exec startkde
# exec startxfce4
# ...or the Window Manager of your choice

hsetroot -fill ~/.wallpaper/retro_2560x1600.png
#exec ~/.scripts/wallpaper &

xbindkeys

xset +fp /usr/share/fonts/local
xset +fp ~/.fonts
xset fp rehash

exec ck-launch-session dbus-launch --sh-syntax --exit-with-session ~/.scripts/dwminit
