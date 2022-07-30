# FireWM
Lightweight Window manager made in C for X <br>
Created as fork of [DWM](https://dwm.suckless.org/)

### dependencies
* Xlib
* Xinerama
* fontconfig
* yajl
* Imlib2
* json-c

### installation
Edit config.mk to match your local setup

after you are done with that
it's time to compile

```sh
sudo USER=`whoami` make clean install
# the USER=`whoami` is required because you don't want to install configuration file into root's home directory
```

### starting

Add the following line to your .xinitrc to start dwm using startx:

```sh
exec firewm
```

## FireWM API
Now FireWM has it's own API, which allows you to change values such as alpha of bar or even gaps while FireWM is runnig!

### What the API can do?
For now the API can change gaps and alpha of bar

to change gaps run:
```sh
# size must be >= 0
firewm-msg run_command firesetgaps {size}
```

to change alpha of bar run:
```sh
# opacity must be >= 0
# recommended maximum number is 255 but nothing will happen if you provide higher number
firewm-msg run_command firesetalpha {opacity}
```

## Changelog
* Now you can set color to the status bar
* Fixed bugs
* Created bugs

