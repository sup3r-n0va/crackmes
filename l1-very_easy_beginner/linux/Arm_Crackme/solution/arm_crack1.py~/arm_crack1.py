#!/usr/bin/env python
# -*- coding: utf-8 -*-
# solution for Crackmes.de
# arm_crack1 by blankwall
# Published: 09. Jun, 2014
# Difficulty: 1 - Very easy, for newbies
# Platform: Unix/linux etc.
# Language: C/C++

string = "`TU_KU_KRXMS"
flag = ""

for i in string:
    flag += chr(ord(i)+20)

print flag
