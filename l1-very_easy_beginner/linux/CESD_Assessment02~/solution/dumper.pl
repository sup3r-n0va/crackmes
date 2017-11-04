#!/usr/bin/perl

#######################################################################
#                shellcode extractor for objdump dumps                #
#######################################################################
#  use like:                                                          #
#          objdump -d yourcompiledshellcode > dump.txt                #
#          perl dumper.pl dump.txt                                    #
#								      #
# have fun ;) 							      #
#						  author: digitalbyte #
#######################################################################

open(datei,@ARGV[0]);
@inhalt=<datei>;
close(datei);
foreach(@inhalt) {
 if ($_=~/^ /) {
 $_=substr("$_",9,15);
 $kette=$kette.$_;
  }
 }
$kette=~s/\s//g; 
 for ($e = 0; $e <= length($kette); $e++) {
 @hexkette[$e]= substr($kette,$e,1);
 }
for($i = 0; $i <= $#hexkette; $i++) {
  if ($i % 2) {
   $ergebnis=$ergebnis.@hexkette[$i]; } 
  else {
   $ergebnis=$ergebnis.").chr(0x".@hexkette[$i];}
 }
$ergebnis=substr($ergebnis,1,length($ergebnis)-7);
print chr(0x0a)."Perl-shellcode: ".chr(0x0a).chr(0x0a).$ergebnis.chr(0x0a).chr(0x0a);
