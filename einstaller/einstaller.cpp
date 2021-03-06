/*
 * $Id: einstaller.cpp 1654 2006-06-09 13:44:34Z karijes $
 *
 * Einstaller, frontend for package installation
 * Part of Equinox Desktop Environment (EDE).
 * Copyright (c) 2000-2006 EDE Authors.
 *
 * This program is licenced under terms of the 
 * GNU General Public Licence version 2 or newer.
 * See COPYING for details.
 */

#include "einstaller.h"
#include <efltk/Fl_File_Dialog.h>
#include "einstall.h"
#include <edeconf.h>

static Fl_Text_Buffer *out_buffer;

static Fl_Window* install_window;

#include <efltk/Fl_Image.h>

#include <efltk/Fl_Images.h>
static const char *datas_install[] = {
  /* columns rows colors chars-per-pixel */
  "120 260 224 2",
  "   c Gray0",
  ".  c #0f0f3f3f0f0f",
  "X  c #0f0f37372f2f",
  "o  c #202018180f0f",
  "O  c #20201f1f1f1f",
  "+  c #2f2f28281010",
  "@  c #2f2f28281f1f",
  "#  c #3f3f37371f1f",
  "$  c #2f2f27272020",
  "%  c #2f2f2f2f2f2f",
  "&  c #202037372f2f",
  "*  c #202038383030",
  "=  c #20203f3f3f3f",
  "-  c #30302f2f2f2f",
  ";  c #303037372f2f",
  ":  c #3f3f37372f2f",
  ">  c #3f3f37373030",
  ",  c #000017174040",
  "<  c #00001f1f4040",
  "1  c #00001f1f4f4f",
  "2  c #00001f1f5050",
  "3  c #00001f1f5f5f",
  "4  c #000000007f7f",
  "5  c #00001f1f6060",
  "6  c #00001f1f6f6f",
  "7  c #00001f1f7f7f",
  "8  c #000028285f5f",
  "9  c #0f0f37374040",
  "0  c #000027276f6f",
  "q  c #000028286060",
  "w  c #000028286f6f",
  "e  c #000027277070",
  "r  c #000028287070",
  "t  c #00002f2f7070",
  "y  c #00003f3f7f7f",
  "u  c #20203f3f5050",
  "i  c #0f0f67670000",
  "p  c #0f0f68681f1f",
  "a  c #2f2f4f4f1010",
  "s  c #3f3f40403030",
  "d  c #2f2f68680000",
  "f  c #2f2f6f6f1010",
  "g  c #0f0f58584f4f",
  "h  c #000050505f5f",
  "j  c #101048484040",
  "k  c #0f0f60605f5f",
  "l  c #000068686060",
  "z  c #0f0f68686060",
  "x  c #000067677070",
  "c  c #000070706060",
  "v  c #000070706f6f",
  "b  c #000070707070",
  "n  c #000078787070",
  "m  c #00007f7f7f7f",
  "M  c #2f2f48484040",
  "N  c #2f2f50504f4f",
  "B  c #2f2f57575f5f",
  "V  c #202060604040",
  "C  c #2f2f68686060",
  "Z  c #303070707070",
  "A  c #4f4f38382020",
  "S  c #404048481010",
  "D  c #4f4f48482020",
  "F  c #4f4f40403030",
  "G  c #4f4f47473f3f",
  "H  c #5f5f47472f2f",
  "J  c #4f4f60601f1f",
  "K  c #707048481f1f",
  "L  c #6f6f68681f1f",
  "P  c #4f4f48484040",
  "I  c #4f4f50504040",
  "U  c #4f4f50504f4f",
  "Y  c #4f4f58584f4f",
  "T  c #5f5f57574f4f",
  "R  c #50505f5f5f5f",
  "E  c #4f4f70707070",
  "W  c #6f6f67674f4f",
  "Q  c #6f6f67675f5f",
  "!  c #6f6f6f6f6f6f",
  "~  c #707070706060",
  "^  c #707070706f6f",
  "/  c #707078786f6f",
  "(  c #707078787070",
  ")  c Gray50",
  "_  c #00001f1f8f8f",
  "`  c #00000f0fa0a0",
  "'  c #00001717a0a0",
  "]  c #00001717afaf",
  "[  c #00001f1fafaf",
  "{  c #000027278080",
  "}  c #000027278f8f",
  "|  c #00002f2f8080",
  " . c #00002f2f8f8f",
  ".. c #000027279090",
  "X. c #00002f2f9090",
  "o. c #00002f2f9f9f",
  "O. c #0f0f37379090",
  "+. c #00002727afaf",
  "@. c #00002f2fa0a0",
  "#. c #00002f2fafaf",
  "$. c #00002f2fb0b0",
  "%. c #00003737a0a0",
  "&. c #00003737b0b0",
  "*. c #00003737bfbf",
  "=. c #00002f2fd0d0",
  "-. c #00004f4f9f9f",
  ";. c #1f1f58589f9f",
  ":. c #00004040a0a0",
  ">. c #00004040bfbf",
  ",. c #00004848bfbf",
  "<. c #00005858afaf",
  "1. c #000078788080",
  "2. c #00004747c0c0",
  "3. c #00004040cfcf",
  "4. c #00005050c0c0",
  "5. c #00005858c0c0",
  "6. c #00005858cfcf",
  "7. c #00004848e0e0",
  "8. c #00005050e0e0",
  "9. c #00005757ffff",
  "0. c #00006060cfcf",
  "q. c #10106060cfcf",
  "w. c #00006060ffff",
  "e. c #00006f6ff0f0",
  "r. c #0f0f6868f0f0",
  "t. c #1f1f6f6fffff",
  "y. c #3f3f7070cfcf",
  "u. c #4f4f68689090",
  "i. c #0000bfbf0000",
  "p. c #202088881010",
  "a. c #1f1f90906060",
  "s. c #0000a0a04040",
  "d. c #2f2fc7c72020",
  "f. c #1f1fd0d04f4f",
  "g. c #5f5f88881f1f",
  "h. c #6060a0a01010",
  "j. c #505090906f6f",
  "k. c #6060cfcf2020",
  "l. c #4040dfdf6f6f",
  "z. c #000080808080",
  "x. c #0000bfbfbfbf",
  "c. c #3f3f90909090",
  "v. c #20208f8fdfdf",
  "b. c #707090909090",
  "n. c #70709090afaf",
  "m. c #50509797c0c0",
  "M. c #6f6f9f9fcfcf",
  "N. c #6060f0f0a0a0",
  "B. c #bfbf00000000",
  "V. c #a0a038381010",
  "C. c #90906f6f1f1f",
  "Z. c #9f9f70704f4f",
  "A. c #808078786f6f",
  "S. c #8f8f78786060",
  "D. c #909088883f3f",
  "F. c #8f8fb8b81010",
  "G. c #9090b8b83f3f",
  "H. c #bfbfbfbf0000",
  "J. c #8f8f80806f6f",
  "K. c #808080807070",
  "L. c #8f8f87877070",
  "P. c #bfbf98984040",
  "I. c #afaf88886060",
  "U. c #afaf98986f6f",
  "Y. c #c0c0a7a77070",
  "T. c #c0c0d8d82f2f",
  "R. c Yellow",
  "E. c #dfdfdfdf4f4f",
  "W. c #808087878080",
  "Q. c #8f8f88888f8f",
  "!. c #8f8f90908f8f",
  "~. c #909088888080",
  "^. c #909090908080",
  "/. c #9f9f90908f8f",
  "(. c #9f9f98988f8f",
  "). c #9f9f98989090",
  "_. c #9f9f98989f9f",
  "`. c #80809f9fa0a0",
  "'. c #8f8fa0a0b0b0",
  "]. c #a0a098989090",
  "[. c #a0a0a7a79f9f",
  "{. c #afafa8a89f9f",
  "}. c #bfbfafaf9090",
  "|. c #a0a0a8a8afaf",
  " X c #afafa8a8a0a0",
  ".X c #a0a0b7b7afaf",
  "XX c #b0b0afafa0a0",
  "oX c #b0b0b0b0afaf",
  "OX c #bfbfb7b7afaf",
  "+X c #b0b0b8b8bfbf",
  "@X c #bfbfb8b8b0b0",
  "#X c Gray75",
  "$X c #80809797f0f0",
  "%X c #8080a7a7cfcf",
  "&X c #9f9fb7b7c0c0",
  "*X c #b0b0b8b8cfcf",
  "=X c #a0a0afaff0f0",
  "-X c #9090cfcfcfcf",
  ";X c #9090f0f0efef",
  ":X c #afafc8c8d0d0",
  ">X c #b0b0c7c7c0c0",
  ",X c #a0a0c8c8efef",
  "<X c #b0b0cfcff0f0",
  "1X c #b0b0f0f0ffff",
  "2X c #c0c0b8b8b0b0",
  "3X c #e0e0b0b0efef",
  "4X c #c0c0c7c7bfbf",
  "5X c #cfcfc7c7b0b0",
  "6X c #dfdfdfdfd0d0",
  "7X c #c0c0dfdfefef",
  "8X c #d0d0d0d0e0e0",
  "9X c #cfcfe8e8efef",
  "0X c #dfdfe7e7efef",
  "qX c #d0d0e8e8ffff",
  "wX c #d0d0f8f8ffff",
  "eX c #dfdff8f8ffff",
  "rX c #e0e0dfdfcfcf",
  "tX c #ffffd8d8ffff",
  "yX c #e0e0e0e0dfdf",
  "uX c #efefe8e8e0e0",
  "iX c #efeff0f0ffff",
  "pX c #f0f0efefefef",
  "aX c #f0f0f7f7efef",
  "sX c Gray100",
  /* pixels */
  ") ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m V M k z z z z z z z k k z z z z v v c z k k c v z v v v v n n n m n n m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m Z L.oX2X2X2X2X2X2X4X#X|.)././././././.).).)./././.!.!.!.!.K.) ) ) ) E E E E C C N z z z z z k k k z z z z z z z z z z k k k z z k k z g k z j j k v v l m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m Z #X4XsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsX; O * G s s s > j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m Z sX4X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6XuX; ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m Z aX5X6X6X5X5X5X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6XuX; ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m Z pX5X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6XuX; ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m Z pX5X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6XuX; ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m Z pX5X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6XuX; ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m Z pX5X6X6X6X6X|.`.`.`.`.'.+X+X+X+X#X#X#X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6XuX- ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m Z pX6X6X6X6X4 , , 4 4 4 , , 4 4 4 5 5 4 2 5 5 5 5 5 5 y ;.B B B ;.;.u.u.n.n.n.n.|.+X+X+X+X+X+X+X#X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6XuX% ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m Z aX6X6X6X6X4 , 5 4 4 4 4 4 4 4 4 4 4 4 4 4 4 , , , , , , , , , , , , , , , , , , 2 2 2 , , , 2 3 2 2 2 3 q q w u.6X6X6X6X6X6X6X6X6XuX% ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m Z sX6X6X6X6X4 , 6 ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 , , , , q 6X6X6X6X6X6X6X6X6XuX% ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m Z sX6X6X6X6X4 , 7 ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` q 6X6X6X6X6X6X6X6X6XuX% ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m Z sX6X6X6X6X4 , _ ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` 4 q 6X6X6X6X6X6X6X6X6XuX% ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m Z sX6X6X6X6X4 , 4 ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` 4 q 6X6X6X6X6X6X6X6X6XpX@ ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m Z sX6X6X6X6X4 , 4 ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` 4 q 6X6X6X6X6X6X6X6X6XpX@ ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m Z sX6X6X6X6X4 , 4 ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` 4 q 6X6X6X6X6X6X6X6X6XuX% ; s s s s s s = m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m Z sX6X6X6X6X4 , ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` 4 0 5X6X6X6X6X6X6X6X6XuX% ; s s s s s s = m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m Z sX6X6X6X6X4 , ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` 6 5X6X6X6X6X6X6X6X6XuX% ; s s s s s s = m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m Z sX6X6X6X6X4 , ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` 6 5X6X6X6X6X6X6X6X6XuX% ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m Z sX4X6X6X6X4 , ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` 6 5X6X6X6X6X6X6X6X6XuX% ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m Z sX5X6X6X6X4 , ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` 6 5X6X6X6X6X6X6X6X6XuX% ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m C sX6X6X6X6X4 , ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` 0 5X6X6X6X6X6X6X6X6XuX$ ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m C sX6X6X6X6X4 , ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` 0 5X6X6X6X6X6X6X6X6XpX$ ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m C sX6X6X6X6X4 , ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` 0 5X6X6X6X6X6X6X6X6XpX$ ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m C sX6X6X6X6X4 , ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` 0 5X6X6X6X6X6X6X6X6XpX$ ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m C sX6X6X6X6X4 , ' ' ' ' ' ' ' ' ' ' ' ' ' ' ' ' ' ' ' ' ' ' ' ' ' ' ' ' ' ' ' ' ' ' ' ' ' ' ' ' ' ' ' ' ' ' ' ' 0 4X6X6X6X6X6X6X6X6XpX$ ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m C sX6X6X6X6X4 , ' ' ' ' ] ' ] ' ' ' ' ] ' ' ' ' ' ] ' ' ] ] ' ' ] ' ] ' ' ' ] ' ] ' ' ' ] ' ] ' ' ] ' ' ' ] ' ] 0 4X6X6X6X6X6X6X6X6XpX$ ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m C aX6X6X6X6X4 , [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ 0 4X6X6X6X6X6X6X6X6XpX@ ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m C aX5X6X6X6X4 , [ [ [ [ [ [ [ [ [ [ [ +.o.X.#.#.#.#.#.#.#.+.+.[ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ t 4X6X6X6X6X6X6X6X6XpX$ ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m C aX4X6X6X6X4 , +.+.+.+.+.+.+.+.+.+.+.X.y                        .X.X.X.#.#.$.#.#.#.+.+.+.+.+.+.+.+.+.+.+.+.+.+.t 4X6X6X6X6X6X6X6X6XpX% ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m C pX5X6X6X6X4 , +.+.$.$.$.$.$.+.+.+.$.;.  m.M.M.M.m.m.m.u.;.;.y                     &.$.+.$.$.+.$.+.+.+.+.+.+.+.t 4X6X6X6X6X6X6X6X6XpX$ ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m C uX5X6X6X6X4 , $.$.$.$.$.$.$.$.$.$.&.q.  &X&X&X&X&X&X&X&X%X%XM.M.M.M.M.M.M.M.M.m.  ;.&.$.$.$.$.$.$.$.$.$.$.$.$.t 4X6X6X6X6X6X6X6X6XpX$ ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m C uX6X4X6X6X4 , $.$.$.$.$.$.$.$.$.$.>.q.  +X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X&X  ;.>.$.$.$.$.$.$.$.$.$.$.$.$.t 4X6X6X6X6X6X6X6X6XpX$ ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m C yX6X4X6X6X4 , &.&.&.&.&.&.&.&.&.&.>.q.  +X+X&X&X&X>X>X>X>X>X+X+X+X+X+X+X+X+X+X&X  ;.>.&.&.&.&.&.&.&.&.&.&.&.&.t >X6X6X6X6X6X6X6X6XpX% ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m C sX6X4X6X6X4 , *.&.*.*.&.*.&.&.*.&.,.q.  +X+X-Xu.;.;.u.m.m.n.%X:X9X9X7X:X-X>X+X&X  ;.,.&.*.&.*.&.&.*.&.&.*.&.*.t >X6X6X6X6X6X6X6X6XpX$ ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m C sX6X5X6X6X4 2 >.>.>.>.>.>.>.>.>.>.,.q.  +X>X-X%Xn.m.m.u.;.;.u.sXsXsXsXsXsX>X+X&X  ;.,.>.>.>.>.>.>.>.>.>.>.>.>.t >X6X6X6X6X6X6X6X6XpX@ ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m C sX6X5X6X6X4 2 >.>.>.>.>.>.>.>.>.>.,.q.  +X&X-X-X-X-X-X-X-X-X-X:X:X7X9XsXsXsX+X&X  ;.,.>.>.>.>.>.>.>.>.>.>.>.>.t >X6X6X6X6X6X6X6X6XpX@ ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m C sX6X4X6X6X4 , ,.,.,.,.,.,.,.,.,.,.,.q.  M.M.M.M.%X%X-X-X-X-X-X-X-X-X-X-X-X>X+X-X  ;.,.,.,.,.,.,.,.,.,.,.,.,.,.y >X6X6X6X6X6X6X6X6XpX@ ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m C sX6X4X6X6X4 2 2.,.2.,.2.2.2.,.2.,.,.6.  q.q.y.y.m.M.M.M.M.M.M.M.M.M.M.%X-X-X-X%X  ;.6.2.,.2.,.2.2.,.2.2.2.2.2.y >X6X6X6X6X6X6X6X6XpX@ ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m C sX6X4X6X6X4 2 4.4.4.4.4.4.4.4.4.4.4.4.            y y ;.;.;.q.q.y.y.y.m.M.M.M.M.  ;.6.4.4.4.4.4.4.4.4.4.4.4.4.y >X6X6X6X6X6X6X6X6XpX@ ; s s s s s s g m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m C sX6X4X6X6X4 2 4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.5.<.                    y y ;.;.;.  <.5.4.4.4.4.4.4.4.4.4.4.4.4.y >X6X6X6X6X6X6X6X6XpX@ ; s s s s s s g m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m C sX6X4X6X6X4 2 5.5.5.5.5.5.5.5.5.5.5.5.5.5.5.5.5.5.5.5.5.5.5.5.5.5.5.<.            5.5.5.5.5.5.5.5.5.5.5.5.5.5.y >X6X6X6X6X6X6X6X6XpX@ ; s s s s s s g m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m C sX6X4X6X6X4 2 6.5.6.6.6.6.6.6.6.6.6.5.6.6.6.6.6.6.6.6.6.6.6.6.6.6.6.6.6.6.6.6.6.6.6.5.6.6.6.6.6.6.6.6.6.6.6.6.y >X6X6X6X6X6X6X6X6XpX@ ; s s s s s : k m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m C sX6X4X6X6X4 2 5.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.y *X6X6X6X6X6X6X6X6XpX$ ; s s s s s ; k m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m C sX6X4X6X6X4 2 0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.y *X6X6X6X6X6X6X6X6XpX$ ; s s s s s s * m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m B sX6X4X6X6X4 2 5.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.y *X6X6X6X6X6X6X6X6XpX$ ; s s s s s s & m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m k sX6X4X6X6X4 2 5.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.y *X6X6X6X6X6X6X6X6XpX$ ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m C sX6X4X6X6X4 5 5.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.y *X6X6X6X6X6X6X6X6XpX$ ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m C sX6X6X6X6X4 5 0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.y *X6X6X6X6X6X6X6X6XpX$ ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m C sX6X6X6X6X4 5 0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.y +X6X6X6X6X6X6X6X6XpX$ ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m C sX6X6X6X6X4 %.5.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.y +X>X6X6X6X6X6X6X6XpX@ ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m C sX6X6X6X6X4 4 y 0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.y +X6X6X6X6X6X6X6X6XpX$ ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m C sX6X6X6X6X4 4 4 4 4 <.5.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.5.y &X6X6X6X6X6X6X6X6XpX% ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m C sX5X6X6X6X6Xn.'.u.;.4 4 4 4 4 4 4 <.5.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.5.q 6X6X6X6X6X6X6X6X6XpX$ ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m C sX5X6X6X6X6X6X6X6X6X6X+X&X&X&Xu.;.4 4 4 4 4 4 4 <.5.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.5.q 6X6X6X6X6X6X6X6X6XpX$ ; s s s s s s j m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m C sX4X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X>X+X&X&Xn.;.4 4 4 4 4 4 4 <.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.5.q 6X6X6X6X6X6X6X6X6XpX$ ; s s s s s s j n z j k m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m C sX4X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X4X>X+X&Xn.u.4 4 4 4 4 4 4 <.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.5.q 6X6X6X6X6X6X6X6X6XpX% ; s s s s > ; * * = k * z m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m C sX4X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X4X>X&X'.u.4 4 4 4 4 4 4 5.0.0.0.0.0.0.0.0.0.q 6X6X6X6X6X6X6X6X6XpX$ ; > ; ; % ; * W U.U.U.z = m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m C sX5X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X>X+X'.b.4 4 4 4 4 4 4 5.0.<.y 6X6X6X6X6X6X6X6X@X).$ % ; * W I.U.U.U.U.U.U.U.= k m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m z sX#X4X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X>X.X'.4 4 4 4 6X6X6X6X2X!.R > s s W S.U.U.U.U.U.U.U.U.U.U.U.U.* n m m m m m m m m m m m m m m m m n m m m ",
  ") m m m m m m m m m m m m m m m m z aX#X#X#X#X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X#X).Q > > G W S.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.j k m m m m m m m m m m m m m v k * * n m m ",
  ") m m m m m m m m m m m m m m m m m n v v z C `.#X#X#X#X#X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X5X[.^ G > G T S.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.* v m m m m m m m m m n k = * M N M m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m n v v z z Z |.#X#X#X#X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6XR > I T S.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.k m m m m m m n k * * D D D D ; v m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m n v v z z Z _.oX#X#X#X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X|.~ U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.v m m m m n k * ; D D F D D D M m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m n v z z I [.#X#X#X#X#X#X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6XS.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.Z.W I.sXsX5Xn & g G D D D D D D D D * v m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m E I > % % - ; L.OX#X#X#X#X#X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X4X~ U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.I.W I.5XsXaXZ.D # D D D D D D D D D D D D = m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m g B I U U U I s o     o o $ Q #X#X#X#X#X6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X+X~ U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.Z.W Y.sXsXsX}.# D D D D D D D D D D D D D O   j m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m z l P I I I I I I I G U P > @ O o o   o o O #X#X#X#X#X#X6X6X6X6X6X6X6X6X6X6XW.T U.U.U.U.U.U.U.U.U.U.U.U.U.U.U.I.Z.U.rXsXsXsXsXsX# D D D D D D D D D D : $ o       = m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m j C Q R R T U I I I I G I I P G G > ; % $ O o o o     o O #X#X#X#X#X6X6X6X6X6X6XW D U.U.U.U.U.U.U.U.U.U.U.U.Z.D.}.sXsXsXsXsXsXsXI.D D D D D D D D D D o o           = m m m m m ",
  ") m m m m m m m m z N N j j N N z n n n n m m m m m m m m m z l E ) / ^ ! Q R R T U I G I I I P G G > ; % % @ O O o o o o o o o     #X#X#X#X#X6X6XW H U.U.U.U.U.U.U.U.I.Z.Y.yXsXsXsXsXsXsXsXsXsXo D D D D D D D #                   = m m m m m ",
  ") m m m m m m n Y Y Q ~ (.[.[.~.!./.L./ E E C C z m m m m g n ).!.Q.W.) K.( ^ ! ! Q R T U U I I I P G s > ; % % @ @ O O O o o o o O O O o o o #X#X#XY # U.U.U.U.U.Z.I.OXsXsXsXsXsXsXsXsXsXsXsXW D D D D D D                   & Z c.M m m m m m ",
  ") m m m m m m v oXyXpXaXuXyX6XoX/.~ T T ~ (.].XXZ m m k v `.oX|. X[._./.!.Q.W.) ) / ^ ! T R R T U I I P G s > ; ; % % % % @ @ @ @ @ % % % ; ; ; ; $ % ; # U.I.I.}.aXsXsXsXsXsXsXsXsXsXsXsXsXyXo D D D #                   A OX+XsXsXR m m m m m ",
  ") m m m m m m v oX~     G I ~ ~.OXuXsXsXpXyXL.XXZ j j z.4X4X4X+X@XoXXX X_._.).!.Q.W.) K.^ Q ! ! Q R R T U P P G G s > > ; ; ; ; ; ; ; ; > s s G G P I G W # H ^.6XuXsXsXsXsXsXsXsXsXsXsXsXsXD D D                     Z.sXsXsX:XsXsXR m m m m m ",
  ") m m m m m m k @X~                       {.~.! o $ 2X6X6X6X6X5X5X#X2X@X@XoX|. X[._./.!.Q.K.! ( / ^ ! Q R R T U I P P G G G G G G G G G G G P P I I I s U.S.W D D : # D H W S.OXuXsXsXsX}.o                     A }.sXsXsXsXsX7XsXsXR m m m m m ",
  ") m m m m m m k 5XI                       OXO o !.6X6X6X6X6X6X6X6X6X6X4X4X4X2X@XoXXX X[._.).!.) ) ) K.( ^ ! ! Q R R T U I I I I I I I I I I I I I P G : U.U.U.U.U.U.U.S.S.W W D : # D o                     W sXsXsXsXsXsXsXsX7XsXsXR m m m m m ",
  ") m m m m m m k 6XF                       o s 2X6X6X6X6X6X6X6X6X6X6X6X6X6X6X5X5X#X2X@X@XoX|. X[./.W.K.W.W.) ) / ^ ! Q R R T U I I I I I I I I P G G P F U.U.U.U.U.U.U.U.U.U.U.U.U.U.~                 @ Y.sXsXsXsXsXsXsXsXsXsX9XsXsXR m m m m m ",
  ") m m m m m m z 6XG                     o ~ yXsXsXsXsX6X6X6X6X6X6X6X6X6X6X6X6X6X6X6X4X4X4X2X@XoXXX X[./.W.K.) K.K.( ^ ! ! ! Q R T U I P G G G G P I I F U.U.U.U.U.U.U.U.U.U.U.U.U.U.W             H aXsXsXsXsXsXsXsXsXsXsXsXsX0XsXsXR m m m m m ",
  ") m m m m m m k 6XO                     O ) ~ W.) !.|.sXsXsXsXsXsXsX6X6X6X6X6X6X6X6X6X6X6X5X5X#X2X@X@XoX X X[./.Q.W.) / ^ ! Q Q R R R R T U I I I I I F U.U.U.U.U.U.U.U.U.U.U.U.U.U.W         Z.sXsXsXsXsXsXsXsXsXsXsXsXsXsXsX0XsXsXC m m m m m ",
  ") m m m m m m k yX                      O / / / / / / ) W.Q./.W._._.sXsXsXsXsXsXsX6X6X6X6X6X6X6X6X4X4X4X+X@XoXXX X_._.).!.Q.W.) K.( ^ ! ! Q R R T U I F U.U.U.U.U.U.U.U.U.U.U.U.U.U.W         rXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsX0XsXsXN m m m m m ",
  ") m m m m m m k pX                      O / / / / / / / / / / / / / / W.Q.!.!.{.oXsXsXsXsXsXsXsXsX6X6X6X5X5X#X2X@X@XoX X X[._./.!.Q.W.) ) / ^ ! Q R R G U.U.U.U.U.U.U.U.U.U.U.U.U.U.W         sXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsX0XsXsXN m m m m m ",
  ") m m m m m m k aX                      O / / / / / / / / / / / / / / / / / ~.L.~.) W.!.!.Q._._.|.sXsXsXsXsX#X#X#X#X4X+X@XoXXX X_._.).!.Q.W.) K.( ^ ! I U.U.U.U.U.U.U.U.U.U.U.U.U.U.W         sXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsX0XsXsXN m m m m m ",
  ") m m m m m m g aX                      O / / / / / / / / / / / / / / / / / L.^./.K./ / / / / / ^ W.Q.!.!.!._._.sXsX#X#X#X#X#X#X#XoX|. X[._./.!.Q.W.) T U.U.U.U.U.U.U.U.U.U.U.U.U.U.W         sXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsX0XsXsXN m m m m m ",
  ") m m m m m m j aX                      O / / / / / / / / / / / / / / / / / K.L.(.L./ / / / / / / / / / / / / ~ W.Q.!.!.W.) Q.sXsX#X#X#X#X#X#X_._.).!.T U.U.U.U.U.U.U.U.U.U.U.U.U.U.W         sXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsX0XsXsXN m m m m m ",
  ") m m m m m m k rX                      O / / / / / / / / / / / / / / / / / ) L.(.~./ / / / / / / / / / / / / / / / / / / / ~ ) Q.!.!.( ( ( sX#X#X#X#XT U.U.U.U.U.U.U.U.U.U.U.U.U.U.W         sXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXaXsXsXN m m m m m ",
  ") m m m m m m j {.                      O / / / / / / / / / / / / / / / / / / L.^.(.L./ / / / / / / / / / / / / / / / / / / / / / / / / / ~ ) Q.!._.^ P U.U.U.U.U.U.U.U.U.U.U.U.U.U.W         sXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXaXsXsXN m m m m m ",
  ") m m m m m m j XX                      O / / / / / / / / / / / / / / / / / / ) L.(./.L./ / / / / / / / / / / / / / / / / / ~ ~ ~ / / / / / / / / / ~ : U.U.U.U.U.U.U.U.U.U.U.U.U.U.W         sXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXaXsXsX= m m m m m ",
  ") m m m m m m j ^.                      O A./ / / / / / / / / / / / / / / / / / K.L.(.(.L.A./ / / / / / / / / / / / / / / |.|.|.|._.!.W./ ~ ~ ~ ~ / / ; U.U.U.U.U.U.U.U.U.U.U.U.U.U.D         sXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXaXsXsX= m m m m m ",
  ") m m m m m m N J.                      O K.K.K.K.K.) A.A.A./ / / / / / / / / / / L.^.^.(.^.L.A./ / / / / / / / / / / / ~ |.|.|.|.|.|.|.|.|.|.|.|._.Q.s U.U.U.U.U.U.U.U.U.U.U.U.U.U.@         sXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXaXsXsX= m m m m m ",
  ") m m m m m m N 5XuX6XXX~ I %           O W.W.W.W.W.L.L.L.K.K.K.K.) ) ) A./ / / / / K.~.L.^.(.^.L.A./ / / / / / / / / / / |.|.|.|.|.|.|.|.|.|.|.|.|.|.P U.U.U.U.U.U.U.U.U.U.U.U.U.U.@         sXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXaXsXsX= m m m m m ",
  ") m m m m m m N 4X4X4X5X5X6XyXaXsX6X].T O !.!.Q.~.~.~.~.W.W.W.W.W.W.L.L.L.K.K.K.K.) ) K.L.~.L.^.(.^.L.) / / / / / / / / / K.W.[.|.|.|.|.|.|.|.|.|.|.|.P U.U.U.U.U.U.U.U.U.U.U.U.U.U.@         sXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXaXsXsX= m m m m m ",
  ") m m m m m m N 5X6X6X5X4X4X5X].~ OX6X_.O )./././././.!.!.!.!.Q.~.~.~.~.W.W.W.W.W.W.L.L.L.L.W./.^.(.^.^.~.L.L.L.K.A./ / / / / / / ~ ~ ~ ~ W.Q._.|.|.|.P U.U.U.U.U.U.U.U.U.U.U.U.U.U.@         sXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsX= m m m m m ",
  ") m m m m m m B oXoX2XOX4X4X[.O % o OX!.O ].].].].].).).).)./././././.!.!.!.!.Q.~.~.~.~.W.W.W.W.~.(.].].^.^.^.^././.^.~.~.L.L.L.K.A./ / / / / / ~ ~ ~ ; U.U.U.U.U.U.U.U.U.U.U.U.U.U.@         sXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsX= m m m m m ",
  ") m m m m m m C 2XT ~ 2X4X4X^.@ s @ /.!.$ [.[.[.[.[.[.[.[.].].].].].).).).)./././././.!.!.!.!.Q.~.Q./.(.].].].(.(.(.(.^.(.(.(.(.(./.^.~.~.W.L.L.K.A./ % U.U.U.U.U.U.U.U.U.U.U.U.U.U.@         sXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXiX= m m m m m ",
  ") m m m m m v C 5X4X4X4X4X4X5X; @ ; 5X!.O (.[.oXXX X X X[.[.[.[.[.[.[.[.[.].].].].].).).).)././././././././././.(.(.(.(.(.(.^.(.^.^.^.(.(.].].(.(./.^.; U.U.U.U.U.U.U.U.U.U.U.U.U.U.@         sXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXaX= m m m m m ",
  ") m m m m m n z z E `..X4X4X5XyXOXyX6X_.O J.Q T W ~ L.^.].[.XXXX X X X X[.[.[.[.[.[.[.[.[.].].].].].).).).)././././././././././.(.(.(.(./.^./.(.^.^.(.: U.U.U.U.U.U.U.U.U.U.U.U.U.U.@         sXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXaX= m m m m m ",
  ") m m m m m m m m k v j j j * Y ) !.Q : ; @XOXOXOX[./.~.S.W T W S.~.(.].oXXXXXXX X X X X[.[.[.[.[.[.[.[.[.].].].].].).).).)./././././././././.(.(.(.(.: U.U.U.U.U.U.U.U.U.U.U.U.U.U.@         sXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXaX= m m m m m ",
  ") m m m m m m n C z.4X4XOX).W.R G $ % ; G R ( ). XXXoXoXoXoXOXXX[./.J.~ W T Q A./.].[.oXXXXXXXXX X X X X[.[.[.[.[.[.[.[.[.].].].].].).).).)./././././.s U.U.U.U.U.U.U.U.U.U.U.U.U.U.@         sXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXaX= m m m m m ",
  ") m m m m m m B C 4X4X4X4X4X4X4X4X4X@X[.) Q G % @ ; I Y ) ). XoXoXoXoXoXOX@X[.]./.A.Q T W ~ J./.[. XoXXXXXXXXXXX X X X X[.[.[.[.[.[.[.[.[.].].].].].).T U.U.U.U.U.U.U.U.U.U.U.U.U.U.+         sXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXaX= m m m m m ",
  ") m m m m m v P @X4X4X4X4X4X4X4X4X4X4X4X4X4X4X4X4X XW.! P ; O ; P R ) `. XoXoXoXoXoXoXOXOX[.].~.S.W T W S.~./.[.OXoXoXXXXXXXXXXX X X X X[.[.[.[.[.[.[.T U.U.U.U.U.U.U.U.U.U.U.U.U.U.+         sXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXaX= m m m m m ",
  ") m m m m m N ) 4X4X4X4X5X6X6X4X4X4X4X4X4X4X4X4X4X4X4X4X4X4X4X[.Q.! P ; O ; G R ( !.[.oXoXoXoXoXoXOXOXXX[./.L.~ W T W A./.].[.OXoXoXXXXXXXXXXXXX X X XT U.U.U.U.U.U.U.U.U.U.U.U.U.U.+         sXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXaX= m m m m m ",
  ") m m m m v R 4X4X4XJ.~ XXW   6X4X4X4X5X6X5X4X4X4X4X4X4X4X4X4X4X4X4X4X4X4X XQ.Q I ; O ; G R ( !.[. XoXoXoXoXoXoXOXOX{.]./.A.Q T W ~ J./.].XXOXoXoXoXXXT U.U.U.U.U.U.U.U.U.U.U.U.U.U.+       @ sXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsX0X= m m m m m ",
  ") m m m m B !.4X4X4X].T @   2X5XXX/.2XOX  uX5X6X4X5X4X4X4X4X4X4X4X4X4X4X4X4X4X4X4X4X#XoX~.Q P - O @ G R ( !.[.|.oXoXoXoXoXoXOXOXOX[.].^.A.W T W ~ ~./.T U.U.U.U.U.U.U.U.U.U.U.U.U.U.+       @ sXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsX0X= m m m m m ",
  ") m m m z R 4X4X4X4X4X5X6X6X4X4X[.F o   Q T J.L.  6X6X6XL.5X4X4X4X4X4X4X4X4X4X4X4X4X4X4X4X4X4X4X5X@X~.Q G % O O ; Y ( !._.|.@XOXoXoXoXoXoXOXOXXX[./.L.F U.U.U.U.U.U.U.U.U.U.U.U.U.U.+       @ sXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsX0X= m m m m m ",
  ") m m m Y !.4X4X4X4X4X4X4X4X4X4X4X5X6X6X5X~.Q   ~   - Q   5XyXuXT [.4X4X4X4X4X4X4X4X4X4X4X4X4X4X4X4X4X4X4X5X5X2XQ.Q F @ O O @ G R !._..X4X@XOXoXoXoXoXG U.U.U.U.U.U.U.U.U.U.U.U.U.U.+         sXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsX0X= m m m m m ",
  ") m m z R b.4X4X4X4X4X4X4X4X4X4X4X4X4X4X4X4X5X6X6X5X[.T ].o   o   5X5X5X6XyX~./.4X4X5X5X4X4X4X4X4X4X4X4X4X4X4X4X4X4X5X5X6X4X~.Q F $ O O O - Y ! '.+X4XI U.U.U.U.U.U.U.U.U.U.U.U.U.U.o         sXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsX0X= m m m m m ",
  ") m m U !.b.4X4X6X6XyX~ 5X4X4X4X4X4X4X4X4X4X4X4X4X4X4X5X5X6X6X2X{.5X5X    :   L.2XuX~.o 6X4X5X6X5X4X4X4X4X4X4X4X4X4X4X4X4X4X4X4X5X6X6X5X~.Q T @ O O O # U.U.U.U.U.U.U.U.U.U.U.U.U.U.o         sXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsX0X= m m m m m ",
  ") m z R b.#X4XXX  - T   5X4X5X6X6X[.5X4X4X4X4X4X4X4X4X4X4X4X4X4X4X4X4X5X6X[.~.J.      A.J.XX^.  uX6X6XXX5X4X4X4X4X4X4X4X4X4X4X4X4X4X4X4X4X4X5X6X6X5X^.F U.U.U.U.U.U.U.U.U.U.U.U.U.U.o         sXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsX0X= m m m m m ",
  ") m U _.+X4X4X4X5X[.G {.5X5X  P A.  XXyXuXJ.[.4X4X5X5X4X4X4X4X4X4X4X4X4X4X4X4X5X6X6XuX].Q @   ~ - ~ W   6X4X5X5X6X4X5X4X4X4X4X4X4X4X4X4X4X4X4X4X4X4X4XT U.U.U.U.U.U.U.U.U.U.U.U.U.U.o         sXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsX8X= m m m m m ",
  ") z R .X4X4X4X4X4X4X5X5X4X5XXX~.P ~ O   -   L.2XuXJ.: 6X5X5X6X4X4X4X4X4X4X4X4X4X4X4X4X4X5X6X6X5X[.J.o {.5XXX@ J.(.  6X6X6X/.2X4X4X4X4X4X4X4X4X4X4X4X4XT U.U.U.U.U.U.U.U.U.U.U.U.U.U.          sXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsX:X= m m m m m ",
  ") U  X4X4X+X4X4X4X5X6X6X[.5X5X6X6X6X6X6X].(.A.      A.J.XX~   6X4X4X4X5X6X5X4X4X4X4X4X4X4X4X4X4X4X5X5X5X4X2X~.Q   ~   - Q   (.yXuXJ./.5X4X5X5X4X4X4X4XT U.U.U.U.U.U.U.U.U.U.U.U.U.U.          sXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsX:X= m m m m m ",
  ") R @X4X4X+X4X4XXX  T T   6XyXuXT XX4X5X6X6X6X6XyXuX].T @   {.5XXX/.5XOX  uX5X6X4X5X4X4X4X4X4X4X4X4X4X4X4X4X4X5X6X6X6X].Q L.@   o   A.[.pX~ o 4X4X4X4XT U.U.U.U.U.U.U.U.U.U.U.U.U.U.          sXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsX:X= m m m m m ",
  ") oX4X4X4X@X5X6X5XOX~.F {.    O   ].5XpX- J.6X5X6X6X5X5X6X6X5X4XXX- o   Q T J.L.  6X6X6X/.5X4X4X5X4X4X4X4X4X4X4X4X4X4X4X5X5X6X6X2X].L.@     2X4X4X5X6XG U.U.U.U.U.U.U.U.U.U.U.U.U.U.          sXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsX:X= m m m m m ",
  ") .X4X4X4X.XJ.L.  5X6X6X6XyX6X].5XT       J.L.XXo   5X4X5X4X5X6X5X6X6XyX4X~.T   ~   - Q   XXyXuXQ [.4X4X4X4X4X4X4X4X4X4X4X4X4X4X4X4X5X6X6X6X4X4X4X~   # U.U.U.U.U.U.U.U.U.U.U.U.U.U.          sXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXc.* z m m m m ",
  ") Z .X4X4X.XQ o J.5X4XA.~.2XuXaX~ ~.yXyXuX/.T %   6X5X(./.6XJ.  yX6X6X5X5X5X6X6X6X6X].T ^.o   o   OX5X5X6XyX/./.4X4X4X5X4X4X4X4X4X4X4X4X4X4X4X4X4X5X6XF U.U.U.U.U.U.U.U.U.U.U.U.U.U.        o sXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsX&XN k m m m m m ",
  ") B b.4X4X.X6X6X5X4X4XA.G o   o   OX4X5X6XyXyXuXyX5X5X].:     A.I L.~   pX6XyX~.6X4X5X6X6X6X6XOX].5X5Xo   F   A.2XuX(.o 6X5X5X6X5X4X4X4X4X4X4X4X4X4X4XF U.U.U.U.U.U.U.U.U.U.U.U.U.U.        @ sXsXsXsXsXsXsXsXsXsXsXsXsXsXsXsXC * z m m m m m m ",
  ") U c.'.`.z.6X6X6X4X4X5X6X6X6X2X].5X4X[.  @ Q ~.2X6X6X6XyXuXuX4X~.T   A.  ; :   5XyXuX: XX4X4X4X5X5X5X6X6X{.J.L.      ~ J.XX^.  uX6X6XXX5X4X4X4X4X4X4XF U.U.U.U.U.U.U.U.U.U.U.U.U.U.        @ sXsXsXsXsXsXsXsXsXsXsXsXsXsX@X* M n m m m m m m m ",
  ") n U U U B G : T ~.6X6X6X6X6X5X5X4X4X4X6X[.L.G o     : J.[.6XyXyXuXuXyX5X].T [.o       6X5X6X6XuX~ [.4X5X6X6X6X6XyXuX[.W @   ~ - ~ Q   6X4X4X4X4X5X6XF U.U.U.U.U.U.U.U.U.U.U.U.U.U.        # sXsXsXsXsXsXsXsXsXsXsXsXsX! * k m m m m m m m m m ",
  ") m n z C C P * M N N G s s A.[.6X6X6X6X5X5X5X6X6X6X5X/.~ @     @ Q ~.2XyXuXuXyXyXpXOX5X5X5X    -   (.5XpXW T 6X5X6X6X5X5X6XyX6X].J.o {.5X4X4X~ [.aX  I U.U.U.U.U.U.U.U.U.U.U.U.U.U.        W sXsXsXsXsXsXsXsXsXsXsXuXk * z m m m m m m m m m m ",
  ") m m m m m m m m m n z * = N N T G : T L.6X6X6X6X6X5X5X5X6X6X6X[.L.G o   o : J.[.pX  J.4X4X6X6X^.{.Q       J.L.XXQ   uX6X6X[.5X4X5X6X4X4X4X2XG @     !.U.U.U.U.U.U.U.U.U.U.U.U.U.U.        W sXsXsXsXsXsXsXsXsXsX5X= = n m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m k & = M M N T F P A.XX6X6X6X6X5X5X5X6X6X6X5X/.~ %     yX4X4X5X6XyXyXyXyXuXaX].T %   ~ F A.%   6X4X4X4X4X5X6X5X5X6X6X6X) U.U.U.U.U.U.U.U.U.U.U.U.U.U.        W sXsXsXsXsXsXsXsXsX).* k m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m n z & M N M T P F W L.6X6X6X6X6X5X5X5X6X6X6X4X4X4Xo   o : J.[.yXJ.  yX6X6X5X].J.  6X5X4XOXS.[.yX  4X4X4X4X4X) U.U.U.U.U.U.U.U.U.U.U.U.U.U.        D sXsXsXsXsXsXsXsXk * z m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m n k & * M N F T P P ~ XX6X6X6X6X5X4X4X4X6X6XOX/.~ @     {.4X4X4X5X6XuXyX6X4X5X5XT @   F 6X4X4X4X4X) U.U.U.U.U.U.U.U.U.U.U.U.U.U.        # sXsXsXsXsXsXyXM = n m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m z & & M M s P T F W L.5X6X6X6X6X5X5X5X6X6X6X5X4X4X4X(.  : J.].6XaX  6X6X6X5X4X4X4X4X4XR U.U.U.U.U.U.U.U.U.U.U.U.U.U.o       # sXsXsXsXsX@X* j n m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m n z X * M M F T T T ~ XX6X6X6X6X5X4X4X4X4X5X2X/.~ @       6X4X4X4X4X4X4X4X@X! U.U.U.U.U.U.U.U.U.U.U.U.U.U.o       # sXsXsXsXE * z m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m n z X & * M s P T P W L.5X6X6X6X5X5X5X5X6X6X6X6X4X4X4X4X4X4X4X5X^.M U.U.U.U.U.U.U.U.U.U.U.U.U.U.o       # sXsXaXj * v m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m n z & X * M M F T T I ~ [.6X6X6X6X5X4X4X4X4X4X4X4X4X].A.= U.U.U.U.U.U.U.U.U.U.U.U.U.U.o       # sX6X* M n m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m n z X X = M > P T P T L.2X6X6X6X5X4X4X5X(.* k U.U.U.U.U.U.U.U.U.U.U.U.U.U.        # _.* k m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m n z & X = M > F T T T ~ ].5XL.~ v k N z S.I.U.U.U.U.U.U.U.U.U.U.        M * v m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m n z & X X = > F P J.v n z j = * * M N ~ U.U.U.U.U.U.U.      $ = n m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m z z X l v m m m m m v k M * * = T ~ U.U.U.  o * g m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m n m m m m m m m m m m v k j * * = T O * k m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m n z j = v m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m n v c c c v n m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m c g V c <.z.r.q.e.e.0.a.p.p p k c m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m n c f k.d.z.9.9.8.6.8.6.6.,.6.7.q.W J p.p.a.g v n m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m a.b.b.b.n.n.%X%X=X<X:Xc.c.m m m m m m m m m m m m m m m m m m m m m m m m m m m m k k.x.9.9.7.9.9.8.7.7.7.7.6.3.3.3.3.3.7.7.q.C.d z p.g n k.n m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m a.f.f.f.j.b.b.n.n.n.%X$X=XqXsXsX7X-Xm.m m m m m m m m m m m m m m m m m m m m m m m V F.c.0.9.9.9.9.9.8.8.7.7.q.Z C 5.e.7.7.2.2.2.2.3.2.O.:.c g._ E j.m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m a.f.f.f.f.f.j.b.`.n.n.%X$X=X<XiXsXsXsXtXtXc.m m m m m m m m m m m m m m m m m m m l D.k.z.w.w.w.w.9.w.9.9.9.9.w.G.V.V.V.V.A ;.,.3.3.;.3.,.2.z %.-.g.J C m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m N.l.f.f.f.f.f.j.b.`.n.n.%X$X<XqXsXsXsXtXtXtX8Xc.m m m m m m m m m m m m m m m m V P.m x.9.r.w.w.9.9.9.9.9.r.C.G T.B.V.B.B.B.B.V.&.3.D.e 2.>.>.;.p p p.J j m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m c.;X;XN.N.f.f.f.f.f.j.b.b.n.n.$X=XqXsXsXsXtXtXtXtXiX:Xm.m m m m m m m m m m m m 1.u.T.F.b.9.r.r.r.r.9.9.9.r.e.! j.B u.y ;.Z.V.V.V.B.< 7.3.3.2.2.>.*.-.h *.p.L o.b m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m c.1X1X;X;XN.l.f.f.f.f.j.b.n.n.%X=X<XsXsXsXtXtXtXtXiXeXwX1Xm m m m m m m m m m x r.J C.T.b.r.r.w.9.9.9.r.z.0.0.c.j.B 9.7.7.8.q.Z C.V.o 8.2.2.>.>.>.>.%.&.:.$.#.J #.l m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m ,XwX1X1X1X;XN.N.f.f.f.f.j.`.n.n.$X<XsXsXsXtXtXtXtXeXwXwX1X;Xc.m m m m m m m x N.j.T.d.k.9.e.x.9.r.r.r.c.0.q.e.c.c.G.h.D.E 7.7.8.Z C.V.$ 7.2.2.>.>.&.%.#.@.@.@.Y S | k m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m n sXeXwXwX1X1X;X;XN.l.f.f.f.j.b.n.%X=XiXsXsXtXtXtXiXeXwX1X;X;XN.N.m m m m m x b.q.2.c.q.v.q.R.k.m.9.w.9.j.k.d.0.c.6.n z ;.V g.U 3.7.3.u.P y 2.2.>.>.&.%.%.@.@.o.o.G S Y k m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m X sXiXiXeXwXwX1X1X;X;Xl.f.f.f.b.b.n.$X7XsXsXtXtXtXeXwX1X;X;XN.N.N.l.m m m x r.9.9.r.r.r.j.k.D.C.H.l.k.l.v.a.p.n a.k.j.g.9.q.d.D.:.2.2.2.3.3.>.>.>.>.&.%.%.@.o.o...' V 8 K l m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m j sXiXiXiXiXeXwXwX1X1X;XN.f.f.f.b.n.%X<XsXsXtXtXiXwX1X1X;XN.N.l.l.l.a.a.n 9.9.9.w.e.w.d.k.G.G.E.P.k.k.F.T.E.k.k.d.F.g.j.-.<.8.,.2.6.3.2.2.*.>.*.*.&.&.#.%.%.%.o. .} } _ D L v m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m v sXsXsXsXiXiXiXeXeXwX1X;XN.l.f.a.`.n.=XsXsXtXtXeXwX1X;XN.N.l.l.a.a.a.a.;.9.w.w.r.e.c.T.D.P.P.P.P.Z.k.G.T.E.T.k.d.d.<.r.q.q.F.g.O.G.s 7.=.2.&.&.&.$.#.#.@.@.O. . .} { { | K J m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m v _.sXsXsXsXsXsXiXiXiXeXwX1X;XN.f.f.b.%XqXsXtXtXwX1X;XN.l.l.a.a.a.a.V V V 6.r.w.r.e.v.c.y.u.Z.P.P.Z.G.F.k.G.T.G.k.p.9.8.8.7.a.h.h.g.H.g.g.V 3.>.%.%.@.@.@.@.o.O. .} { { { y J V m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m v 0XsXsXsXsXsXsXsXsXsXiXiXeXwX1XN.f.a.'.<XsXtXeX1XN.N.l.a.a.a.V V V V V V B r.t.t.v.v.t.t.t.B P.P.D.E.T.k.T.E.T.G.p.9.9.8.8.7.j.F.F.C.C.C.a y -.*.%.:.@.@.o.o.o. . .{ { e } L d l m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m n o sXsXsXsXsXsXsXsXsXsXsXsXiXiXwX1Xl.a.$XsXtX1XN.l.a.a.a.V V V V V N N N N B 9.9.9.r.t.t.t.t.I.P.P.E.G.F.E.E.T.G.k.d.d.;.z.7.k.h.F.C.C.& o.j.d y >.o.o.o.o.o. . .} { 7 7 { h d f m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m g |.eXeXiXiXiXsXsXsXsXsXsXsXsXsXsXsXN.g u.qXN.a.V V V N N N N N N N N N N N ;.r.r.t.t.t.v.v.U.Z.P.E.E.E.E.E.G.G.k.k.d.d.p.:.c.h.F.C.9 E =.:.*.&.:.O.o.o..... . .{ | 7 7 { ..f g.g m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m v = 7X*X:X:X:X:X:X:X:X7X7X7XqXqXeXiXc.z.z.x X N = = u u u u u u u B u B B B B r.r.t.t.t.t.v.~ E.Y.P.P.E.E.E.h.k.k.G.G.h.p.p.k.h.h.h.W g.h V >.o.@.@.@.o..... . .{ { e 6 7 { h J f m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m . P &X'.'.'.'.'.'.'.'.'.'.'.'.'.'.&Xz.z.z.z.* qX'.b.u.E E E B B B B B B B B B t.t.t.t.v.v.m.Z.P.Z.C.E.E.E.E.h.k.T.G.h.g.h.h.h.h.a D.i k ..%.@.@.o.......}  . .{ e 7 7 7 { @.d J g m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m N `.'.'.'.'.'.'.'.'.'.'.&X&X:X7XiX7Xz.z.z.z.iXsXsXsXsXiX7X,X&X'.n.b.u.u.u.E u.t.t.t.v.v.m.( P.I.Z.E.E.T.E.E.h.G.T.a p.G.g.h.d g.C.7 *.%.o.o.o.o.....} } } | { e 6 7 7 { } y d f n m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m l $ &X'.'.'.'.'.&X&X&X:X:X7XeXiXsXsX9X<X,X9XsX<X=X8XsXsXsXsXsXsXiXqX<X,X&X%Xn.t.t.t.v.v.v.b.P.E.I.C.P.E.P.T.g.E.g.E.f h.i G.p G.J q :.o.o.o....... .} { } | e e 7 7 7 { { @.p J c m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m g O &X&X&X&X&X:X:X:X7XqXeXsXsXsXsXsXeX9XeXsXsXeX=X=X<XiXsXsXsXsXsXsXsXsXiXqX$Xt.t.v.t.v.G.g.E.Y.Z.C.P.P.P.G.F.h.g.g.h.g.p.T.L X *.O.o.o.o.....} } } { { | e 0 e e e e } }  .d j m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m , U &X:X:X:X:X7X7XeXiXiXsXsXsXsXiXeXqX9XeXsXsXsXqX=X=X=X7XiXsXsXsXsXsXsXsX<Xt.t.v.t.M.P.Y.I.K I.K C.C.P.G.G.h.g.g.h.p.g.D.i h #.o...o.....} } } { { { r r 0 e e { { } | o.p J m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m n   `.:X:X7X7XqXeXiXsXsXsXsXsXsXiXeXqXqXwXiXsXsXsXiX7X=X=X=X<XqXsXsXsXsXsXsXt.t.t.t.m.P.Z.P.P.Y.C.Z.C.C.D.h.h.p.g.g.g.d Y.i y o. .......} } } { { { e e r r r e | { }  .} @.g.c m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m l   7X7XqXeXeXiXsXsXsXsXsXsXsXiXeXeXqX9XeXiXsXsXsXsXqX<X=X=X=X=X7XqXsXsXsXt.t.t.t..XP.C.Z.K K Z.W C.C.D.h.g.g.p.p.g.h.H i g o...} ....{ { { { { e e r r r r | | } { } } ..O.h m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m l   ! iXeXiXsXsXsXsXsXsXsXsXiXiXeXqXwXwXeXiXsXsXsXsXiXqX<X=X=X=X=X<XqXiXt.t.t.t.u.G.Z.Z.Z.Z.Z.Z.K K D.h.g.G.i p.g.D.. i | ..} } } } { { { e e e r w r | | | | | } } } } ..y m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m n o   sXsXsXsXsXsXsXsXsXsXiXiXeXqXqX9XwXeXiXsXsXsXsXsXeX7X<X=X=X=X=X<Xt.t.t.t.t.G.T W Z.K P.K K K C.g.g.f p.p.f d i 9 o. .{ } } { { 7 e e e w w w r | | | | | | } } ..} y m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m g   iXsXsXsXsXsXsXsXsXiXiXeXqXqXqX9XeXeXiXsXsXsXsXsXiXqX7X<X=X=X=Xr.t.t.t.t.j.P.D.Z.K Z.K K K L g.p.i i p.p.i i .. .{ } { { { 7 7 7 6 0 w w r r | | | | | |  .}  .} @.m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m h * $ sXsXsXsXsXsXsXiXiXeXqXqXqX9XwXeXeXiXsXsXsXsXsXsXeXqX<X<X=X8.8.t.t.8.t.;.f G.D.K W S K C.g.p.p.p.p j 9 h p o.| { e 7 7 7 6 6 6 w w w r | O.O.O.| | | |  .} } &.m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m . M sXsXsXsXsXsXiXiXeXeXqXqXqXwXwXeXiXiXsXsXsXsXsXsXiXqX7X=X8.8.8.8.8.8.t.J j.P.C.C.K C.D.J p.9 q q o.O.@.p j } 7 7 7 6 6 6 6 5 q q w | | | O.O.O.| | |  . ...*.n m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m 9 o *X9XsXsXsXiXiXeXeXqXqXqX9XwXeXeXiXiXsXsXsXsXsXsXsXeXy.8.8.8.8.8.8.8.u.6.G.W K C.K f i 9 %.O. .| { | ..2 t 0 0 6 5 6 5 5 q 5 q w r | | O.O.O.O.O.O.|  . .*.v m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m n , =   sXsXiXiXeXeXqXqXqXwX9XwXeXeXiXiXsXsXsXsXsXsX7X8.8.8.8.8.6.6.2.6.g.-.P.A K K S i y  . .{ | | { { k h y e 6 5 8 3 q q 8 q w r | | O.O.O.O.X.X.X. . .*.v m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m c . M ) 9XeXiXeXeXqXqXqX9XwXwXeXeXiXsXsXsXsXsXiX8.8.8.8.2.2.2.2.2.2.-.B x C.A H K d 0 {  .e | } e j 3 8 9 X 0 Y < 5 3 q q q q w | | O.O.| O.X.X.X. ...*.v m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m b z * j.'.7XeXeXwXqX9X9XwXwXeXiXiXsXsXsX,X3.3.3.3.2.2.2.2.2.2.>.>.z O.;.K A K S 8 } {  .h p 6 7 e 6 0 8 q 3 5 3 3 q 8 r q | | | O.O.O.O.X.X. .....*.n m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m n m u.j.|.`.8XwXwXwXwXwXeXeXiX7XR u.3.3.2.2.2.2.2.2.2.>.>.>.>.>. .&.;.K A + a } | _ p . 7 e 3 5 w 3 3 3 2 2 2 5 q q r r O.| | O.| O.X. . ...o.*.m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m.Z -Xu.n.n.u.u.u z q.3.3.3.2.3.*.2.2.*.2.*.>.>.%.%.%.-.o.;.K K H A X y g d . 6 0 e q 3 3 2 2 8 q 8 8 * p j y y V y O.| | X.X.o. .o.&.m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m O.2.2.3.3.3.3.3.*.*.*.*.*.*.*.*.&.&.&.%.%.%.O.O.X. .{ , S H # S K S * D.S X 5 2 2 2 5 & J + . i J f d f J d y O.X.O.g y o.o. .m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m y *.*.*.*.*.*.*.*.*.*.*.*.*.&.&.&.%.%.%.@.O.O. . .X. .} 7 5 , 6 5 $ + + + . 5 2 2 3 f . U . p.A L + a J J d h g p p.f S +.@.y m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m l 3.*.*.*.*.*.*.*.*.*.*.&.$.&.%.%.@.%.@.o.o. .X.{  .| e e e 0 5 3 5 5 3 9 + 1 2 9 j a F . . g.A # a a f J a p p.i f C.& @.$.l m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m b 3.*.&.*.*.&.*.*.&.&.$.$.#.%.#.@.@.o.o.o. . . .{ | t e 0 0 5 3 3 3 2 2 3 2 $ % 2 & o A . a . f # a f p f i i f J f L } o.3.v m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m %.$.&.&.$.&.$.$.#.#.#.#.#.@.@.@.o.o. . . . .{ { e e 0 q 5 3 3 2 2 2 1 1 1 1 1 1 2 G # a a . a . i a i p f J f J C.a $.@.*.m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m h #.#.%.#.#.#.#.#.#.@.@.o.@.o.o. . . . .{ { e e 0 0 5 5 3 2 2 1 1 1 1 1 1 , 1 , q : a a . a i i i i i p J J f L L & $.@.h m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m v &.@.@.#.#.@.@.@.@.@.o.o.o. . . . . .{ { e e 0 0 q q 3 3 2 1 1 1 1 1 1 , , , 2 E + a . i i i i i i p J J J f K C.j #.*.v m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m n n m c.c.m.&X0XtX3X3X3X3X<X=Xm.;.;.-.-.@.o.o.o. .....} } } { e e e 0 0 5 5 3 3 2 2 1 < 1 < < , , , 1 8 W o a a . i i i i i d J J f L L L y #.&.m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m Z Z Z u.u.n.$X=X<XiXtXtX3X3X3X<X<X;X;XN.l.l.a.s.k h  . .....} } { { { e e e 0 0 5 5 3 3 2 1 1 < < , < < , 1 1 1 Y + . i i i i i p f J L J J K L S +.$.l m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m n Z Z E E u.u.u.u.n.$X<XiXtXtX3X3X3X<X;XN.N.l.a.s.p p p X X 9  .} } } { { { e e 0 0 q 5 3 3 2 2 1 1 , < , < < < 1 1 1 q W o i a a a a f J J J J L L L C.= $.:.m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m a.s.s.s.s.s.a.Z E E u.u.u.M.=X0XtX3X3X3X,X;XN.l.s.p p X X X X 9 9 9 9 q { { { { e e e 6 0 5 5 5 3 2 2 2 1 , , < < < , < 1 1 2 2 M o # a a a d d f f H i L S C.S #.2.h m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m a.f.f.m i.i.i.s.s.s.s.C E u.u.u.$X<XtX3X3X1XN.l.s.p j X X X X , , 9 u B E u.%X{ { { e e e 0 0 5 5 3 3 3 2 1 1 , < < < < < , < 1 1 2 2 q 8 o # J S J d f a d i L g.L #.%.:.m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m N.N.N.N.N.l.l.f.f.f.d.i.s.a.E u.u.=XtX3X,Xl.p . X = = u B E u.'.*X<XqXeXiXsXsX`.{ e e 7 0 0 6 5 5 3 3 2 2 1 1 , , < < < < , , 1 1 2 2 3 3 r u + A A + # S g.a g.J C.@.%.3.v m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m.-X;X;X;X;X;X;X;X;X;X;XN.N.l.l.f.f.C <X3X%Xa.`.'.%X%X=X<XqXeXiXsXsXsXiXiXiXeXqXqX:X9 e 7 6 6 6 5 5 5 3 3 2 2 2 1 , , < < < < , , 1 1 2 2 3 3 q 5 r u - A A # o J p.f C.S $.&.y m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m %X<X<X<X<X<X<X<X<X<X8X8X8XtXtXiXsXeXE a.j.k 9 <X=X=X$X$X$X$X$X$X$X$X$X$X$X$X$X$X$X`.B r 6 0 6 6 5 5 5 3 3 2 2 1 1 1 , < < < < , < < 1 1 2 2 2 q q w q 0 { O.A A + f p.f L _ %.%.m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m %XtXtXtXtXiXiXiXiXsXiXiXqX:X'.b.b.'.7XiX&X-X7XwXeXsXiXiXeXqX7X<X<X=X=X=X=X$X$X$X$X`.g 0 6 6 6 5 5 5 3 3 3 2 2 1 1 < , < < < , , < < 1 1 1 2 3 3 q q q w w | } H + a i i d y #.*.n m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m -XsXsXiXiXqX:X:X%X`.b.b.b.b.`.&X7XiXiXqX:X:X:X-X:X<X7XwXeXiXiXiXiXiXeXeXqXqXqX%X&Xb.y 5 5 q 5 5 3 3 3 3 2 2 1 1 1 < < < , , , , < < 1 1 2 2 3 3 3 q r q w r | | A o p.i p.p $.*.v m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m :X&X'.b.b.b.b.b.b.b.`.'.:X7XeXsXeXeX7X:X:X:X:X-X:X:X7X7X7XwXeXeXiXiXiXiXiX&X`.) ;.l 6 3 3 3 3 3 3 3 2 2 2 1 1 < , < , , , < , < < < 1 1 2 3 3 8 q w q w r r { u.+ S i i g +.*.l m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m R b.u.b.b.b.`.'.&X:X7XqXiXiXiXeXqX7X:X:X:X:X:X-X>X:X:X7X<X7XqXwXeX7X-Xn.! E u.m m m l 3 2 2 2 2 2 1 1 1 1 , , < < < < < < 1 < 1 1 1 1 2 2 3 8 8 q q w w r r } F D S p.p +.*.l m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m o B %X`.'.&X:X:X7XeXiXsXiXeXqX7X7X:X:X:X:X:X:X-X-X:X:X:X<XeXeX'.j.%XC n n m m m m m m b 2 2 1 1 1 1 1 , , , , 1 1 1 < 1 1 1 1 1 1 1 2 2 8 8 8 q q w r r r | O.A J d j $.*.b m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m n     7X:X:XqXeXiXsXiXeXeXqX7X7X:X:X:X:X&X&X&X-X-X:XiXeX8XN.%X8Xn m m m m m m m m m m m n 1 1 , , , , , , 1 < 1 1 1 1 1 1 1 1 1 2 1 2 8 8 q q q w w r r | ..Y S d h $.O.n m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m g 9   . ) :X'.`.`.`.`.b.b.b.b.b.b.'.`.b.E `.*X-Xc.%XM.m m m m m m m m m m m m m m m m m h 3 1 , 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 8 8 8 q q w w r r | | y K K y 2.x m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m n l c v 9 , o ,     m , , * u B u.n n v n n m m m m m m m m m m m m m m m m m m m m m m v 1 3 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 8 q q q w w r | | ..N K -.y v m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m h 8 3 2 1 1 2 1 2 2 2 8 2 2 2 2 8 8 8 q w w w r r | | y S O.l m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m l 8 5 2 2 2 2 2 2 3 8 2 2 2 2 3 q q q w r r | | O.y l m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m b h 3 6 5 3 3 3 8 8 3 3 3 3 q q w r | X. .h b m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m b l h 8 8 w w e r r e { t q h x v m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m n n n n n m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m ",
  ") m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m m "
  };

Fl_Group* steps_group;

Fl_Group* step1_group;

Fl_Input* package_name_input;

static void cb_Browse(Fl_Button*, void*) {
  char *file_types = _("Packages (*.rpm; *.tgz; *.deb), *.{rpm|tgz|deb}, All files (*.*), *");
  const char *f = fl_select_file(package_name_input->value(), file_types, _("Package selection"));
      	  
      if (f) { 
  	package_name_input->value(f);
  next_button->activate();
      }
;}

Fl_Check_Button* nodeps_button;

Fl_Group* step2_group;

Fl_Text_Editor* result_output;

Fl_ProgressBar* install_progress;

Fl_Button* prev_button;

static void cb_prev_button(Fl_Button*, void*) {
  step1_group->show();
  step2_group->hide();
  prev_button->deactivate();
  next_button->activate();
}

Fl_Button* next_button;

static void cb_next_button(Fl_Button*, void*) {
  step1_group->hide();
  step2_group->show();
  prev_button->activate();
  next_button->deactivate();
  install_package();
}

static void cb_Close(Fl_Button*, void*) {
  exit(0);
}

int main (int argc, char **argv) {

  Fl_Window* w;
  fl_init_locale_support("einstaller", PREFIX"/share/locale");
  out_buffer = new Fl_Text_Buffer();
   {Fl_Window* o = install_window = new Fl_Window(505, 310, _("Install software package"));
    w = o;
     {Fl_Box* o = new Fl_Box(5, 5, 135, 270);
      o->image(Fl_Image::read_xpm(/*"icons/install.xpm"*/0, (const char**)datas_install));
      o->box(FL_DOWN_BOX);
      o->color((Fl_Color)0x7d8300);
    }
     {Fl_Group* o = steps_group = new Fl_Group(140, 0, 355, 275);
      o->box(FL_FLAT_BOX);
       {Fl_Group* o = step1_group = new Fl_Group(5, 5, 350, 270);
        o->box(FL_ENGRAVED_BOX);
         {Fl_Input* o = package_name_input = new Fl_Input(10, 132, 250, 23, _("Enter the name of software package you want to install:"));
          o->align(133);
          
        }
         {Fl_Button* o = new Fl_Button(265, 132, 80, 25, _("&Browse..."));
          o->callback((Fl_Callback*)cb_Browse);
        }
         {Fl_Box* o = new Fl_Box(5, 5, 340, 90, _("Welcome. This installation wizard will help you to install new software on yo\
ur computer."));
          o->label_size(18);
          o->align(133|FL_ALIGN_INSIDE);
          
        }
         nodeps_button = new Fl_Check_Button(7, 165, 338, 25, _("Ignore dependencies"));
          
        
        o->end();
      }
       {Fl_Group* o = step2_group = new Fl_Group(5, 5, 350, 270);
        o->box(FL_ENGRAVED_BOX);
        o->hide();
         {Fl_Text_Editor* o = result_output = new Fl_Text_Editor(10, 25, 335, 155, _("Installation results:"));
          o->align(133);
          
          o->buffer(out_buffer);
        }
         {Fl_ProgressBar* o = install_progress = new Fl_ProgressBar(10, 215, 335, 20, _("Installation status:"));
          o->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
          
        }
        o->end();
      }
      o->end();
    }
     {Fl_Button* o = prev_button = new Fl_Button(230, 280, 80, 25, _("<< &Previous"));
      o->callback((Fl_Callback*)cb_prev_button);
      o->deactivate();
      
    }
     {Fl_Button* o = next_button = new Fl_Button(315, 280, 80, 25, _("&Install"));
      o->callback((Fl_Callback*)cb_next_button);
      o->deactivate();
      
    }
     {Fl_Button* o = new Fl_Button(415, 280, 80, 25, _("&Close"));
      o->callback((Fl_Callback*)cb_Close);
      
    }
    
    o->end();
  }
  w->show(argc, argv);
  return  Fl::run();
}
