char *commands[] = {
    "firesetalpha", "firesetgaps", "firesetbarcolor",
    "firesetbordercolor", "firesetbarlayout", "firesetbarcenter",
    "firesetbarpadding"
};

char *comments[] = {
    "Change opacity of the bar", "Change gaps between windows and bar", "Change background color of the bar",
    "Change color of borders", "Change layout of the bar\nA - App button\nT - Tags\nL - layout\nn - title\ns - status\nS - systray", "What part of bar should be centered",
    "Change padding of the bar"
};

char *params[] = {
    "INT", "INT", "STRING",
    "STRING", "STRING", "STRING",
    "INT"
};