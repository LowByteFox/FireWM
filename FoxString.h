/*
 * FoxString - Easy to use string implementation in C/C++
 * Copyright (C) 20022 Fire-The-Fox
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FOXSTRING_LIBRARY_H
#define FOXSTRING_LIBRARY_H

enum FoxString_Signals { NOT_FOUND = -1, NO_ISSUE = 0, OUT_OF_MEMORY = 2, NO_LIMIT = 0, EQUAL = 1, NOT_EQUAL = 0, NOT_CREATED = 3};

typedef struct {
    char *data;
    unsigned long size;
} FoxString;

FoxString
FoxString_New(const char *init);                                                    // It creates a new FoxString with the given `init` string.

void
FoxString_Clean(FoxString *string);                                                 // Cleaning the FoxString.

FoxString
FoxString_ReCreate(FoxString *string, const char *init);                            // Recreating the FoxString with the given `init` string.

FoxString
FoxStringInput();                                                                   // Reading a string from the standard input and returning it as a `FoxString`.

int
FoxString_Count(FoxString string, char detect);                                     // Counting the number of characters in the FoxString.

int
FoxString_Find(FoxString string, char detect);                                      // Finding the first occurrence of the character in the FoxString.

int
FoxString_Contains(FoxString str1, FoxString str2);                                 // Checking if the `FoxString` contains the given `FoxString`.

int
FoxString_Add(FoxString* string, char character);                                   // Adding a character to the end of the FoxString.

char
FoxString_Pop(FoxString* string);                                                   // Removing the last character from the string and returning it.

int
FoxString_Connect(FoxString* mainString, FoxString sideString);                     // Connecting the `mainString` with the `sideString` together.

FoxString
FoxString_Replace(FoxString string, char oldChar, char newChar, int count);         // Replacing the `oldChar` with the `newChar` in the `FoxString` `count` times.

int
FoxString_Compare(FoxString str1, FoxString str2);                                  // Comparing the two FoxStrings.

#endif //FOXSTRING_LIBRARY_H
