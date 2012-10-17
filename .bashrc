#
# ~/.bashrc
#

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

#alias ls='ls --color=auto'
#PS1='[\u@\h \W]\$ '

alias ls='ls -X --color=auto'
alias ll='ls -Ahl'
alias emacs='emacs -nw'
alias vlc='cvlc'
alias dwmi='~/scripts/dwmi'
alias nyc='urxvt -fn "xft:nyc:pixel=10"'
alias hcl='rm ~/.bash_history; history -c;'
#PS1='\[\e[0;30m\]\u \W\[\e[m\] \[\e[0;33m\]\$\[\e[m\] '
PS1='\[\e[1;30m\]\u \W\[\e[m\] \[\e[1;33m\]\$\[\e[m\] '

# Hz
hz() {
    cp -a ~/{dwm,scripts,.gtkrc-2.0,.bash_profile,.bashrc,.emacs,.hgrc,.ncmpcpp,.rtorrent.rc,.vimrc,.xbindkeysrc,.xinitrc,.Xresources,.mozilla/firefox/h30r20tn.default/chrome/userChrome.css,.fonts} ~/hz
    cd ~/hz
    git add . -A
    git commit -m 'auto update'
    git push -u origin master
    cd -
}

# movez
mvz() {
    a=1
    for i in *.$2; do
        new=$(printf "$1%02d.$2" ${a})
        mv ${i} ${new}
        let "a = a + 1"
    done
}

# screenshot
sshot() {
    i=$1
    if [[ "$i" == "" ]]; then
        i="sshot.png"
    else
        if [[ ! "$i" == *.png ]]; then
        i="$i.png"
        fi
    fi
    import -window root ~/$i
}

# xztract
xzt() {
    7z x ${1}
}

# refresh
fresh() {
    xrdb -merge ~/.Xresources
    cd ~/.fonts
    mkfontscale
    mkfontdir
    xset fp rehash
    cd -
}
