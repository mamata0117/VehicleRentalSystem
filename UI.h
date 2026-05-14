// ui.h

#pragma once

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// MENU / DISPLAY UI
void printMenuHeader(string title);
void printMenuItem(string text);
void printMenuFooter();

// INPUT UI
void printInputHeader(string title);

// MESSAGE UI
void printMessage(string msg);

// LINE
void printLine();