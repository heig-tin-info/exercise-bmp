# Fichiers binaires

Cet exercice permet de se familiariser avec les fichiers binaires. Le fichier `lena16.bmp` est une image en couleur suivant le format [BMP](https://en.wikipedia.org/wiki/BMP_file_format).

## Premier aperçu

Si vous cherchez à voir le contenu de ce fichier par exemple avec le programme `less` permettant de visualiser un fichier. Il vous sera informé que le fichier est du type binaire et qu'interpreter son contenu comme du texte intelligible ne sera probablement pas possible. Néanmoins, nous continuons par principe avec `y` pour *yes*.

```console
$ less lena16.bmp
"lena16.bmp" may be a binary file.  See it anyway?
```

Le résultat n'est pas glorieux:

```text
BMx^@^B^@^@^@^@^@v^@^@^@(^@^@^@^@^B^@^@^@^B^@^@^A^@^D^@^@^
^@^@^@^@<FF><FF><FF>^@^^^V&^@Y:G^@<92>cf^@<BE><99><8E>^@<C
^@Nn<C5>^@6P<A1>^@1B^?^@bl<96>^@"+Y^@<FF><FF><FF>^@ """"""
<DE><2#"^B^@"2 #^B>###2.3""4BU2"3^B24D #3#$TC"U3 """23"2""
<BA><BA><BA><BA><BB><AA><BA><AA><AB><AA><AA><AB><AA><AB><A
<AA><AA><AA><AA><AA><AA><AA><8A><A8><A8><AA><88><A8><8A><A
<88><A8><88><A8><8A><88><A8><88><88><88><89><88><88><98>wx
<CE><CC><CC><<C3><CC><DC><DD>۪<AA><AA><BA><BA><BB><AB><AB><
<EE>#<EE><C3><C3><CC><C3><C3><CE><EC><CC><CD><DD><DD><DD>M
w<9D>ͺ<AA><88><88><87><87>xw<87>wwxy<AE><C3>"""^B^B"2^@#"3
42"4<EE>C<EE><EE><CE><CE><CC>̼<BB><BB><BB><BB><BB><AA><BA><
<BA><AA><AA><AA><AA><AA><AA><AA><AA><AA><AA><A8><AA><AA><A
<8A><8A><AA><8A><A8><A8><A8><A8><A8><A8><A8><8A><88><88><A
<88>x<88>w<87><98>wwwwwgwfggfffff^Vaaaff<9D><D4>L<<<<<CC><
<AA><AA><AA><AA><AB><BB><CC><CC><CC><EC><EE><EE><E3><E3><E
<DE><E2>"""^B^B""<EE><E3><CC><CB>˻  """""=VfffffW]<CB>ڪ<88
#""2">2>3""33EB"2^C24D #335D"#E3 "^B">3#"""42>D<C4>2"<EE><
<AA><AA><BA><AB><AA><BA><BA><AA><AA><AB><AA><AB><AA><AA><A
<AA><AA><AA><AA><AA><8A><A8><AA><A8><8A><8A><8A><8A><A8><A
<88><A8><8A><88><88><88><88><88><88><88><88><88><97>y<87><
<CE><CE><EC><<CD><<DC><DB>۪<AB><AA><BA><BB><BA><BA><BA><AA>
<EE><EE>3<C3><C3><C3><<EC><E3><CC>=<DD>ݝ<DD><DD><DC>3<EE><
<88><87><87><87>w<87><87>wwx<88><BD><<E2>"2^B^B^B2"#"2###<
```

Pour quitter `less`, il faut utiliser la touche `q`, c'est une convention utilisée depuis longtemps dans les environnements POSIX. Pour naviguer dans le fichier vous pouvez utiliser les fleches haut, bas ou leur équivalent sur le clavier `j` et `k`.

Sur ce contenu abscons, on peut tout de même identifier les deux premiers caractères du fichier `BM` qui correspondent à la signature du fichier (voir *Bitmap file header* sur la page wikipedia).

## Aperçu hexadécimal

Pour mieux décoder le contenu du fichier il est préférable d'utiliser un outil capable d'afficher le contenu hexadécimal du fichier. Le programme `hexdump` est certainement le plus adapté.

```console
$ hexdump -n100 -C lena16.bmp
00000000  42 4d 78 00 02 00 00 00  00 00 76 00 00 00 28 00  |BMx.......v...(.|
00000010  00 00 00 02 00 00 00 02  00 00 01 00 04 00 00 00  |................|
00000020  00 00 02 00 02 00 12 0b  00 00 12 0b 00 00 00 00  |................|
00000030  00 00 00 00 00 00 00 00  00 00 ff ff ff 00 1e 16  |................|
00000040  26 00 59 3a 47 00 92 63  66 00 be 99 8e 00 c7 de  |&.Y:G..cf.......|
00000050  e1 00 93 b8 d9 00 69 95  dc 00 7a 91 b9 00 4e 6e  |......i...z...Nn|
00000060  c5 00 36 50                                       |..6P|
00000064
```

À quoi servent les options `-C` et `-n100` ?

Est-ce que l'option `-s` peut vous être utile à quelque chose ?

Quelle est la différence entre la commande ci-dessus et celle-ci:

```console
$ hexdump -C lena16.bmp | head -n6
```

## Décodage d'information

À partir de `hexdump` et de la spécification des fichiers BMP, extraire les informations suivantes:

- Type de fichier
- Taille de l'image en octets
- Adresse de début de l'image
- La hauteur de l'image
- La largeur de l'image
- Le nombre de bits par pixels
- La résolution horizontale et verticale

Quelle est la différence avec `stat lena16.bmp | grep -Po 'Size:\s\K\d+'` ?

## Correction:

La signature vaut `BM`, `0x42, 0x4D` pour le format WIndows 3.1x, 95, NT...

La taille du fichier est stockée en entier sur 4 bytes `78` `00` `02` `00` en *little endian*, on a d'abord le plus petit byte. La taille vaut donc `0x20078`, soit:

```console
$ printf "%d\n" 0x20078
131192
```

L'offet du début de l'image est:

```console
$ hexdump lena16.bmp -n4 -s10
000000a 0076 0000
```

Donc 118