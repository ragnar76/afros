Aniplayer V2.23 Juin 2013:
--------------------------
- Am‚lioration lecture des fichiers MPEG1/2, la d‚compression du son 
est trait‚ par un thread sous MiNT et MagiC.
- Ajout gestion LCD de Eiffel 1.10 via la librairie partag‚e LCD.SLB 
(config minimale MiNT 1.15.3 ou MagiC 6 ou MetaDOS 2.74). Ce SLB ne 
peut pas ˆtre utilis‚ en mˆme temps par plusieurs programmes.
- Ajout gestion des touches multim‚dia de l'interface PS/2 Eiffel via 
E_TEMP.PRG et le cookie "Eiff" (PLAY/PAUSE, STOP, PREVIOUS TRACK, NEXT 
TRACK, VOLUME DOWN et VOLUME UP).
- Gestion variable d'environnement HELPVIEWER.
- Appels sous-menu via la fonction menu_attach de l'AES 4.0.
- Ajout bouton Record dans la Playlist pour la conversion de fichiers.
- Plus de caractŠres sp‚ciaux HTML avec les ID3. A la sauvegarde, il 
existe aussi une conversion des caractŠres avec accents en HTML.
- Mode plein ‚cran sur Radeon utilisant VIDIX (CT60/CTPCI).
- R‚‚criture MP3 pour le Coldfire V4E utilisant l'instruction MAC 
(Firebee).

Notes:  - S.V.P. lisez les r‚pertoires JPEG, VORBIS, VORBIS_ENC ou
------  AVCODEC pour plus d'informations sur chaque librairie.
        - OPENDIVX.SLB est enlev‚ de l'archive car AVCODEC.SLB peut 
        decoder du divx, si vous pr‚f‚rez utiliser OPENDIVX.SLB vous 
        devez enlever AVCODEC.SLB. Vous pouvez trouver OPENDIVX.SLB 
        dans cette archive:
        http://perso.wanadoo.fr/didierm/files/anipl219.zip

Si votre machine est trop lente pour le DivX, utilisez les CT60/CTPCI 
avec une Radeon !!!
http://www.czuba-tech.com/

Si vous voulez cr‚er un CD-Audio avec du mpeg, vous devez essayer CD-Writer
2.2 (ou plus) avec Aniplayer :
http://www.cyberus.ca/~anodyne/

 
Si vous avez une CENTurbo II et vous voulez enlever le patch DSP_IRQ.PRG
de votre dossier AUTO, S.V.P. lisez ANIPLAY.HYP Questions/r‚ponses.



Pour toutes questions e-mail: aniplay@wanadoo.fr

Web: http://aniplay.atari.org

                  