#ifndef FOXBOX_LIBRARY_H
#define FOXBOX_LIBRARY_H

#ifndef __cplusplus

typedef void **FoxBox;

FoxBox FoxBox_New();

int FoxBox_Append(FoxBox *box, void *item);
int FoxBox_Expand(FoxBox *box);

unsigned int FoxBox_Size(FoxBox box);

void FoxBox_Clean(FoxBox box);

#endif

#endif //FOXBOX_LIBRARY_H
