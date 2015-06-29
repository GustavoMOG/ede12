/*
 * $Id: erun.cpp 1654 2006-06-09 13:44:34Z karijes $
 *
 * Part of Equinox Desktop Environment (EDE).
 * Copyright (c) 2000-2006 EDE Authors.
 *
 * This program is licenced under terms of the 
 * GNU General Public Licence version 2 or newer.
 * See COPYING for details.
 */

#include "erun.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <efltk/Fl_File_Dialog.h>
#include <efltk/Fl_Locale.h>
#include <efltk/Fl_Config.h>
#include <efltk/Fl_Util.h>
#include <edeconf.h>

Fl_Window* windowRunDialog;

Fl_Input* inputRunDialog;

static void cb_inputRunDialog(Fl_Input*, void*) {
  char *cmd = (char*)inputRunDialog->value();
  run_resource(cmd);
  windowRunDialog->hide();
}

#include <efltk/Fl_Image.h>

#include <efltk/Fl_Images.h>
static const char *datas_run[] = {
  "32 32 516 2",
  "  	c None",
  ". 	c #C9EFF9",
  "+ 	c #BFDCE4",
  "@ 	c #C7ECF6",
  "# 	c #CAEBF4",
  "$ 	c #BAE6F3",
  "% 	c #97A9AE",
  "& 	c #ADE7F3",
  "* 	c #B9EFF7",
  "= 	c #B8F7FB",
  "- 	c #C3EFF7",
  "; 	c #B7EDFC",
  "> 	c #9AC8D8",
  ", 	c #A6E1F0",
  "' 	c #9FEFF7",
  ") 	c #8BEFF7",
  "! 	c #85EDF6",
  "~ 	c #93EBF5",
  "{ 	c #A4ECFA",
  "] 	c #8CD4E9",
  "^ 	c #8DD2E6",
  "/ 	c #9FC2CC",
  "( 	c #D0F3FA",
  "_ 	c #AEECF5",
  ": 	c #81E5F2",
  "< 	c #70E5F2",
  "[ 	c #62E3F1",
  "} 	c #5AE1EF",
  "| 	c #70E1F1",
  "1 	c #78D8ED",
  "2 	c #76DAF7",
  "3 	c #72AFC2",
  "4 	c #ADDBE8",
  "5 	c #EDFCFE",
  "6 	c #EEFBFE",
  "7 	c #C7F0F7",
  "8 	c #89DFEE",
  "9 	c #59DAEB",
  "0 	c #49D9EB",
  "a 	c #3CD6EA",
  "b 	c #3AD4E9",
  "c 	c #4BD1E7",
  "d 	c #5DD6F1",
  "e 	c #55C0DD",
  "f 	c #6CBFD7",
  "g 	c #9BD6E6",
  "h 	c #C7EDF8",
  "i 	c #F2FEFE",
  "j 	c #E7FBFE",
  "k 	c #E5FBFE",
  "l 	c #DDF8FC",
  "m 	c #ADE8F2",
  "n 	c #66D4E7",
  "o 	c #35CAE2",
  "p 	c #2ACBE4",
  "q 	c #22C8E3",
  "r 	c #1FC6E1",
  "s 	c #34C8E3",
  "t 	c #3FC2E0",
  "u 	c #47C0E2",
  "v 	c #5FA0B4",
  "w 	c #A1DEEF",
  "x 	c #E5F9FC",
  "y 	c #E7FBFD",
  "z 	c #E0F9FC",
  "A 	c #DAF7FC",
  "B 	c #D4F7FB",
  "C 	c #D4F8FC",
  "D 	c #C6F2F9",
  "E 	c #95DFEE",
  "F 	c #4BC8DE",
  "G 	c #1CBEDB",
  "H 	c #16BCDC",
  "I 	c #11BBDC",
  "J 	c #11B8DB",
  "K 	c #1EB7D9",
  "L 	c #32C2E8",
  "M 	c #3CB2D5",
  "N 	c #5FB0C9",
  "O 	c #95D0DB",
  "P 	c #BAE9F6",
  "Q 	c #ECFCFE",
  "R 	c #DAF8FC",
  "S 	c #D5F8FB",
  "T 	c #CEF6FB",
  "U 	c #C8F4FA",
  "V 	c #C2F2F9",
  "W 	c #BEF2FA",
  "X 	c #B2EEF6",
  "Y 	c #79D5E6",
  "Z 	c #33BAD6",
  "` 	c #0DAED0",
  " .	c #0AAFD5",
  "..	c #06ACD3",
  "+.	c #07ABD3",
  "@.	c #13ADD4",
  "#.	c #1EADD4",
  "$.	c #2FB1D7",
  "%.	c #5895A8",
  "&.	c #8FD3E5",
  "*.	c #D7F6FB",
  "=.	c #E4FBFE",
  "-.	c #CFF5FA",
  ";.	c #C0F2F9",
  ">.	c #B8F0F8",
  ",.	c #B0EEF7",
  "'.	c #A9EDF5",
  ").	c #A9EDF7",
  "!.	c #97E5F0",
  "~.	c #65CDE0",
  "{.	c #23ADCC",
  "].	c #05A2C9",
  "^.	c #03A2CD",
  "/.	c #02A1CC",
  "(.	c #019EC9",
  "_.	c #15A6CD",
  ":.	c #25B9E1",
  "<.	c #2FA2C5",
  "[.	c #5FC4E0",
  "}.	c #A1DFF0",
  "|.	c #E8FDFE",
  "1.	c #DCF9FC",
  "2.	c #D5F7FB",
  "3.	c #C8F3FA",
  "4.	c #BFF0F8",
  "5.	c #AFEEF6",
  "6.	c #A7EBF4",
  "7.	c #A1E9F3",
  "8.	c #98E6F1",
  "9.	c #93E5F1",
  "0.	c #8FE5F0",
  "a.	c #83DEEB",
  "b.	c #51C1D6",
  "c.	c #1AA5C4",
  "d.	c #0194BF",
  "e.	c #0095C2",
  "f.	c #3DBFDA",
  "g.	c #4CC5D9",
  "h.	c #0291BF",
  "i.	c #0C9BC8",
  "j.	c #7FC3D6",
  "k.	c #D4F9FD",
  "l.	c #DEF8FC",
  "m.	c #D6F7FC",
  "n.	c #D0F6FA",
  "o.	c #C7F2F9",
  "p.	c #B8F0F6",
  "q.	c #B0EEF6",
  "r.	c #A8EBF4",
  "s.	c #9FE8F1",
  "t.	c #93E3EE",
  "u.	c #82DDE8",
  "v.	c #72D5E2",
  "w.	c #6DD4E3",
  "x.	c #6DD7E6",
  "y.	c #73DAE8",
  "z.	c #65D1E1",
  "A.	c #3EB7CD",
  "B.	c #0F95B9",
  "C.	c #0A8DB1",
  "D.	c #1A96B7",
  "E.	c #007FAF",
  "F.	c #1D94BB",
  "G.	c #B4CDF6",
  "H.	c #B7CFF7",
  "I.	c #AEC9F6",
  "J.	c #A9C5F5",
  "K.	c #A3C1F5",
  "L.	c #9DBEF4",
  "M.	c #95B9F3",
  "N.	c #8FB4F2",
  "O.	c #87B0F2",
  "P.	c #81ACF1",
  "Q.	c #7AA7F0",
  "R.	c #73A2EF",
  "S.	c #6E9FED",
  "T.	c #689AE9",
  "U.	c #6497E6",
  "V.	c #6092E3",
  "W.	c #5C8FE0",
  "X.	c #5A8DDE",
  "Y.	c #5B8EE0",
  "Z.	c #346CBC",
  "`.	c #4BC1D0",
  " +	c #54CADB",
  ".+	c #57CDDE",
  "++	c #59D0E0",
  "@+	c #52C8D9",
  "#+	c #2DA8C1",
  "$+	c #0885AA",
  "%+	c #0078A5",
  "&+	c #3A90AA",
  "*+	c #AECBF6",
  "=+	c #A4D3FA",
  "-+	c #9CD0FA",
  ";+	c #96CBF9",
  ">+	c #8EC7F7",
  ",+	c #87C2F7",
  "'+	c #7EBCF6",
  ")+	c #75B7F5",
  "!+	c #6CB1F4",
  "~+	c #61A9F3",
  "{+	c #58A2ED",
  "]+	c #529CE8",
  "^+	c #4B95E2",
  "/+	c #448EDC",
  "(+	c #3D86D6",
  "_+	c #3881D2",
  ":+	c #3179CC",
  "<+	c #2D74C7",
  "[+	c #EDF5FD",
  "}+	c #7EAFF1",
  "|+	c #1758AB",
  "1+	c #34A3B1",
  "2+	c #48BCCC",
  "3+	c #4CC4D7",
  "4+	c #4BC5D8",
  "5+	c #4AC5D7",
  "6+	c #4FCADA",
  "7+	c #34AFC6",
  "8+	c #1E8FB5",
  "9+	c #A8C7F6",
  "0+	c #96CEFA",
  "a+	c #8EC9F9",
  "b+	c #87C5F8",
  "c+	c #7FC0F7",
  "d+	c #77BAF6",
  "e+	c #6DB4F5",
  "f+	c #63ADF4",
  "g+	c #5AA7F0",
  "h+	c #529FEA",
  "i+	c #4B98E4",
  "j+	c #4591DE",
  "k+	c #3F8BD9",
  "l+	c #3783D3",
  "m+	c #327DCE",
  "n+	c #2C76C8",
  "o+	c #2771C4",
  "p+	c #7CADF0",
  "q+	c #5189D5",
  "r+	c #1558AB",
  "s+	c #1E808C",
  "t+	c #39ACBB",
  "u+	c #45BCCD",
  "v+	c #45BFD1",
  "w+	c #42BED0",
  "x+	c #41BDCE",
  "y+	c #2CABC3",
  "z+	c #4E95AA",
  "A+	c #A4C2F5",
  "B+	c #A7C7F5",
  "C+	c #A1C4F4",
  "D+	c #9CC0F3",
  "E+	c #95BBF2",
  "F+	c #8BB5F1",
  "G+	c #82AFEF",
  "H+	c #77A8EE",
  "I+	c #6EA2EC",
  "J+	c #679BE6",
  "K+	c #5F95DF",
  "L+	c #558CD7",
  "M+	c #4F86D2",
  "N+	c #4880CC",
  "O+	c #4078C5",
  "P+	c #3972BE",
  "Q+	c #316BB8",
  "R+	c #2C65B3",
  "S+	c #255FAD",
  "T+	c #205BA9",
  "U+	c #154F9D",
  "V+	c #136B75",
  "W+	c #2E9EAD",
  "X+	c #3BB4C4",
  "Y+	c #3CB9CB",
  "Z+	c #38B6C9",
  "`+	c #2692AD",
  " @	c #C1D8FD",
  ".@	c #F4F9FF",
  "+@	c #F1F7FF",
  "@@	c #EEF5FE",
  "#@	c #EAF3FE",
  "$@	c #E7F1FE",
  "%@	c #E4F0FE",
  "&@	c #E0EDFE",
  "*@	c #DBEBFD",
  "=@	c #D5E7FD",
  "-@	c #CFE3FD",
  ";@	c #CCE1FC",
  ">@	c #C5DEFC",
  ",@	c #BFDAFB",
  "'@	c #B9D6FB",
  ")@	c #AED0FA",
  "!@	c #A6CBF9",
  "~@	c #A1C8F9",
  "{@	c #9AC3F7",
  "]@	c #98C3F8",
  "^@	c #588BDD",
  "/@	c #0F626C",
  "(@	c #2694A3",
  "_@	c #33ACBD",
  ":@	c #33B0C3",
  "<@	c #32B0C0",
  "[@	c #1D9AB6",
  "}@	c #3D8D9D",
  "|@	c #BCD5FD",
  "1@	c #F3F8FF",
  "2@	c #F0F6FE",
  "3@	c #ECF4FE",
  "4@	c #EAF2FE",
  "5@	c #E6F0FE",
  "6@	c #E1EEFE",
  "7@	c #DDEBFD",
  "8@	c #D7E8FD",
  "9@	c #D2E5FD",
  "0@	c #C8E0FC",
  "a@	c #C2DCFB",
  "b@	c #B3D3FA",
  "c@	c #A5CAF8",
  "d@	c #9FC6F8",
  "e@	c #9DC5F7",
  "f@	c #97C2F7",
  "g@	c #91BEF6",
  "h@	c #5689DB",
  "i@	c #0E6069",
  "j@	c #218E9D",
  "k@	c #2CA4B5",
  "l@	c #2CA8BA",
  "m@	c #26A2B7",
  "n@	c #1D90AD",
  "o@	c #B8D2FC",
  "p@	c #EBF3FE",
  "q@	c #E8F1FE",
  "r@	c #DBEAFD",
  "s@	c #D4E6FD",
  "t@	c #CBE1FC",
  "u@	c #C4DDFB",
  "v@	c #AACDF9",
  "w@	c #9FC6F7",
  "x@	c #99C3F6",
  "y@	c #95C0F6",
  "z@	c #91BDF6",
  "A@	c #8DBBF5",
  "B@	c #5286D7",
  "C@	c #0C5C65",
  "D@	c #1B8897",
  "E@	c #249BAD",
  "F@	c #249EB0",
  "G@	c #1A97B1",
  "H@	c #3F90A6",
  "I@	c #B2CFFC",
  "J@	c #EDF4FE",
  "K@	c #E7F0FE",
  "L@	c #E3EFFD",
  "M@	c #DEECFD",
  "N@	c #DAE9FD",
  "O@	c #CEE2FC",
  "P@	c #C5DDFB",
  "Q@	c #A9CDF8",
  "R@	c #9EC5F7",
  "S@	c #9CC4F7",
  "T@	c #9BC3F7",
  "U@	c #92BEF5",
  "V@	c #8CBAF5",
  "W@	c #86B6F4",
  "X@	c #4E83D4",
  "Y@	c #0A5761",
  "Z@	c #177F90",
  "`@	c #1C91A3",
  " #	c #1D96A8",
  ".#	c #1A88A7",
  "+#	c #AFCDFC",
  "@#	c #E9F2FE",
  "##	c #E0EDFD",
  "$#	c #DBE9FD",
  "%#	c #D1E4FC",
  "&#	c #AFCFF9",
  "*#	c #9DC4F7",
  "=#	c #98C2F6",
  "-#	c #95C0F5",
  ";#	c #91BDF5",
  ">#	c #8BB9F4",
  ",#	c #85B5F3",
  "'#	c #7EB1F2",
  ")#	c #4B80D1",
  "!#	c #08525D",
  "~#	c #127789",
  "{#	c #168798",
  "]#	c #0F86A1",
  "^#	c #3C8FA5",
  "/#	c #AACAFC",
  "(#	c #E2EEFD",
  "_#	c #D8E9FD",
  ":#	c #D3E5FC",
  "<#	c #CFE3FC",
  "[#	c #C0DAFB",
  "}#	c #A3C8F7",
  "|#	c #9EC5F6",
  "1#	c #9DC4F6",
  "2#	c #99C2F6",
  "3#	c #97C1F5",
  "4#	c #8AB8F4",
  "5#	c #84B4F3",
  "6#	c #76ABF1",
  "7#	c #467CCD",
  "8#	c #07535E",
  "9#	c #0F7281",
  "0#	c #0F7B90",
  "a#	c #0F85A4",
  "b#	c #A6C7FC",
  "c#	c #E2EEFE",
  "d#	c #D6E6FC",
  "e#	c #CCE1FB",
  "f#	c #A0C6F6",
  "g#	c #9AC3F6",
  "h#	c #96C0F5",
  "i#	c #92BDF4",
  "j#	c #8AB8F3",
  "k#	c #84B3F2",
  "l#	c #7DB0F1",
  "m#	c #75AAF0",
  "n#	c #6DA4EF",
  "o#	c #4177C8",
  "p#	c #075765",
  "q#	c #0B6A7B",
  "r#	c #09758E",
  "s#	c #3893AD",
  "t#	c #A2C4FC",
  "u#	c #E4EFFE",
  "v#	c #D5E5FC",
  "w#	c #CEE2FB",
  "x#	c #BCD7FA",
  "y#	c #98C0F5",
  "z#	c #93BDF4",
  "A#	c #8EBAF3",
  "B#	c #85B4F2",
  "C#	c #7DAFF1",
  "D#	c #76ABF0",
  "E#	c #6DA4EE",
  "F#	c #659EE8",
  "G#	c #3C72C3",
  "H#	c #044F61",
  "I#	c #076376",
  "J#	c #0D7998",
  "K#	c #9DC1FB",
  "L#	c #DEEBFD",
  "M#	c #D8E7FC",
  "N#	c #D3E4FC",
  "O#	c #BFD9FA",
  "P#	c #A7CAF7",
  "Q#	c #9FC5F6",
  "R#	c #9CC3F5",
  "S#	c #94BDF4",
  "T#	c #8EB9F3",
  "U#	c #7FAFF1",
  "V#	c #74A9EF",
  "W#	c #6BA2ED",
  "X#	c #659DE8",
  "Y#	c #5C96E1",
  "Z#	c #376DBE",
  "`#	c #335F69",
  " $	c #0F5F77",
  ".$	c #388DA1",
  "+$	c #9AC0FB",
  "@$	c #D5E6FC",
  "#$	c #CAE0FB",
  "$$	c #BAD5F9",
  "%$	c #AACCF7",
  "&$	c #A6C9F7",
  "*$	c #A4C8F6",
  "=$	c #99C1F5",
  "-$	c #92BCF3",
  ";$	c #88B6F2",
  ">$	c #80B0F1",
  ",$	c #77AAEF",
  "'$	c #659CE7",
  ")$	c #5C95E0",
  "!$	c #548DD9",
  "~$	c #3068B8",
  "{$	c #89B6F9",
  "]$	c #C5DDFA",
  "^$	c #BDD8F9",
  "/$	c #B4D2F9",
  "($	c #AFCFF8",
  "_$	c #ACCDF7",
  ":$	c #A9CBF7",
  "<$	c #A4C7F6",
  "[$	c #9EC3F5",
  "}$	c #8DB8F2",
  "|$	c #85B2F1",
  "1$	c #7AABF0",
  "2$	c #6EA3EE",
  "3$	c #5B93DF",
  "4$	c #538CD7",
  "5$	c #4B84D0",
  "6$	c #2B63B3",
  "7$	c #6095E6",
  "8$	c #6095E5",
  "9$	c #5E93E4",
  "0$	c #5C92E3",
  "a$	c #5C91E2",
  "b$	c #5A8FE0",
  "c$	c #598EDF",
  "d$	c #578CDD",
  "e$	c #558ADB",
  "f$	c #5388D9",
  "g$	c #4F84D5",
  "h$	c #4D82D3",
  "i$	c #4A7FD0",
  "j$	c #467CCC",
  "k$	c #4076C7",
  "l$	c #3D73C4",
  "m$	c #386EBF",
  "n$	c #3369BA",
  "o$	c #2D65B5",
  "p$	c #2961B1",
  "q$	c #225AA7",
  "                                                                ",
  "                        . +                                     ",
  "                        @ # $ %                                 ",
  "                      & * = - ; >                               ",
  "                      , ' ) ! ~ { ] ^                           ",
  "                    / ( _ : < [ } | 1 2 3                       ",
  "                    4 5 6 7 8 9 0 a b c d e f                   ",
  "                  g h i j k l m n o p q r s t u v               ",
  "                  w x y z A B C D E F G H I J K L M N           ",
  "                O P Q z R S T U V W X Y Z `  ...+.@.#.$.%.      ",
  "                &.*.=.R B -.U ;.>.,.'.).!.~.{.].^./.(._.:.<.[.  ",
  "                }.|.1.2.-.3.4.>.5.6.7.8.9.0.a.b.c.d.e.f.g.h.i.  ",
  "              j.k.l.m.n.o.4.p.q.r.s.t.u.v.w.x.y.z.A.B.C.D.E.F.  ",
  "  G.H.G.I.J.K.L.M.N.O.P.Q.R.S.T.U.V.W.X.Y.Z.`. +.+++@+#+$+%+&+  ",
  "  *+=+-+;+>+,+'+)+!+~+{+]+^+/+(+_+:+<+[+}+|+1+2+3+4+5+6+7+8+    ",
  "  9+-+0+a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z+    ",
  "  A+B+C+D+E+F+G+H+I+J+K+L+M+N+O+P+Q+R+S+T+U+V+W+X+Y+Z+Z+`+      ",
  "   @.@+@@@#@$@%@&@*@=@-@;@>@,@'@)@!@~@{@]@^@/@(@_@:@<@[@}@      ",
  "  |@1@2@3@4@5@6@7@8@9@-@0@a@b@c@d@e@{@f@g@h@i@j@k@l@m@n@        ",
  "  o@1@@@p@q@%@6@r@s@9@t@u@v@w@w@e@x@y@z@A@B@C@D@E@F@G@H@        ",
  "  I@2@J@p@K@L@M@N@s@O@P@Q@R@R@S@T@y@U@V@W@X@Y@Z@`@ #.#          ",
  "  +#+@J@@#5@##$#=@%#t@&#S@R@*#=#-#;#>#,#'#)#!#~#{#]#^#          ",
  "  /#2@p@K@(#M@_#:#<#[#}#|#1#2#3#;#4#5#'#6#7#8#9#0#a#            ",
  "  b#@@p@K@c#7@d#%#e#&#f#1#g#h#i#j#k#l#m#n#o#p#q#r#s#            ",
  "  t#J@@#u###N@v#w#x#}#f#1#y#z#A#B#C#D#E#F#G#H#I#J#              ",
  "  K#J@q@(#L#M#N#O#P#}#Q#R#S#T#B#U#V#W#X#Y#Z#`# $.$              ",
  "  +$p@5@M@@$#$$$%$&$*$Q#=$-$;$>$,$W#'$)$!$~$                    ",
  "  {$%#e#]$^$/$($_$:$<$[$S#}$|$1$2$'$3$4$5$6$                    ",
  "  7$8$9$0$a$b$c$d$e$f$g$h$i$j$k$l$m$n$o$p$q$                    ",
  "                                                                ",
  "                                                                ",
  "                                                                "};

static void cb_OK(Fl_Button*, void*) {
  char *cmd = (char*)inputRunDialog->value();
  run_resource(cmd);
  windowRunDialog->hide();
}

static void cb_Cancel(Fl_Button*, void*) {
  windowRunDialog->hide();
}

static void cb_Browse(Fl_Button*, void*) {
  char *file_types = _("Executables (*.*), *, All files (*.*), *");
  char *fileName = fl_select_file(inputRunDialog->value(), file_types, _("File selection..."));          
  if (fileName) 
  { 
    inputRunDialog->value(fileName);
  }
;}

int main (int argc, char **argv) {

  Fl_Window* w;
  fl_init_locale_support("erun", PREFIX"/share/locale");
   {Fl_Window* o = windowRunDialog = new Fl_Window(350, 160, _("Open..."));
    w = o;
    o->when(FL_WHEN_ENTER_KEY);
     {Fl_Input* o = inputRunDialog = new Fl_Input(60, 77, 200, 23, _("Open:"));
      o->callback((Fl_Callback*)cb_inputRunDialog);
      o->align(132);
      o->when(FL_WHEN_ENTER_KEY);
    }
     {Fl_Box* o = new Fl_Box(5, 5, 55, 70);
      o->image(Fl_Image::read_xpm(0, (const char**)datas_run));
      o->align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
    }
     {Fl_Box* o = new Fl_Box(60, 5, 285, 70, _("Type the location you want to open or the name of the program you want to run\
. (Possible prefixes are: http:, ftp:, gg:, av:, leo:)"));
      o->align(132|FL_ALIGN_INSIDE);
    }
     {Fl_Button* o = new Fl_Button(180, 127, 80, 25, _("&OK"));
      o->callback((Fl_Callback*)cb_OK);
    }
     {Fl_Button* o = new Fl_Button(265, 127, 80, 25, _("&Cancel"));
      o->callback((Fl_Callback*)cb_Cancel);
    }
     {Fl_Button* o = new Fl_Button(265, 77, 80, 25, _("&Browse..."));
      o->callback((Fl_Callback*)cb_Browse);
    }
    o->x(Fl::info().w/2 - (o->w()/2));
    o->y( (Fl::info().h/2) - (o->h()/2));
    o->end();
  }
  w->show(argc, argv);
  return  Fl::run();
}

void run_resource(char *cmd) {
  char pRun[256];
          char browser[256];
  
  	Fl_Config pGlobalConfig(fl_find_config_file("ede.conf", 0));
          pGlobalConfig.get("Web", "Browser", browser, 0, sizeof(browser));
          if(pGlobalConfig.error() && !browser) {
              strncpy(browser, "netscape", sizeof(browser));
          }
  
          char *location = strdup(cmd);
          char *prefix = strstr(location, ":");
          if(prefix) // it is internet resource
          {
              *prefix = '\0';
              if (!strcasecmp(location, "http") || !strcasecmp(location, "ftp") || !strcasecmp(location, "file"))
              {	snprintf(pRun, sizeof(pRun)-1, "%s %s &", browser, cmd);
              }
  	    else if (!strcasecmp(location, "gg"))
  	    {	snprintf(pRun, sizeof(pRun)-1, "%s http://www.google.com/search?q=\"%s\" &", browser, ++prefix);
  	    }
  	    else if (!strcasecmp(location, "leo"))
  	    {	snprintf(pRun, sizeof(pRun)-1, "%s http://dict.leo.org/?search=\"%s\" &", browser, ++prefix);
  	    }
  	    else if (!strcasecmp(location, "av"))
  	    {	snprintf(pRun, sizeof(pRun)-1, "%s http://www.altavista.com/sites/search/web?q=\"%s\" &", browser, ++prefix);
  	    }
  	    else  {
                  snprintf(pRun, sizeof(pRun)-1, "%s %s &", browser, cmd);
  	    }
  	}
          else // local executable - parse the standard specification parameters to the executable if any exists in the *.desktop file.
          {
              snprintf(pRun, sizeof(pRun)-1, "%s &", cmd);
  	}
  	delete [] location; 
          fl_start_child_process(pRun);
}
