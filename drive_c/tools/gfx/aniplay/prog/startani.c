
/* PROGRAMME DE DEMONSTRATION LANCEMENT ANIPLAYER AVEC CONTROLE              */
/* 16, 256 COULEURS, OU TRUE COLOR OBLIGATOIRE SANS CHANGEMENT DE RESOLUTION */

/* DEMO PROGRAMM FOR START ANIPLAYER WITH CONTROL                            */
/* 16, 256 COLORS, OR TRUE COLOR IS REQUIRED WITHOUT CHANGE VIDEO DISPLAY    */

/* MEQUIGNON Didier - September 2000 */

#include <stdio.h>
#include <string.h>
#include <tos.h>
#include <aes.h>

int event(void);

int ap_id,picture=0,pause=0,single_step=0;
short ctrl[3];

struct infos
{
	short width;
	short height;
	short planes;
	short frames_second;
	long total_frames;
	long id_picture_compression;	/* cvid for example */
	short quality;					/* B0: mono(0)/stereo(1)  B1: 8 bits(0)/16 bits(1) */
	unsigned short frequency_file;
	unsigned short frequency_machine;
	long total_samples;
	long id_sound_compression;		/* ima4 for example */
	short version_player;			/* version of Aniplayer */
	long count_seconds;				/* no used with +z option */
	long num_frame;					/* no used with +z option */				
    short play;						/* no used with +z option */
    short reserve[11];				/* no used with +z option */
};

static struct infos infos;

void main()

{
	int i,ret,x,y,w,h;
	static char cmde[256],path_info[80],path[80],name[12];
	static char select[]="*.*";
	static struct infos infos;
	ap_id=appl_init();
	path[0]=Dgetdrv()+'A';path[1]=':';Dgetpath(path+2,Dgetdrv()+1);
	strcat(path,"\\");strcat(path,select);
	fsel_input(path,name,&ret);
	if(ret)											/* OK */
	{
		i=strlen(path)-1;	
		while(path[i]!='\\')
			path[i--]=0;
		strcat(path,name);							/* path with name */
		strcpy(path_info,path);
		
		/* returns informations about movie */

		sprintf(cmde," -e +z%ld",(long)&infos.width);	
		strcat(cmde,path_info);						/* command ligne with path */
		cmde[0]=strlen(cmde);						/* pascal format !         */
		Pexec(0,"ANIPLAY.PRG",cmde,"");				/* get infos */

		/* test movie */

		wind_get(0,WF_WORKXYWH,&x,&y,&w,&h);		/* desktop */
		if(infos.id_picture_compression				/* 0 if unknown picture */
		 && infos.id_sound_compression				/* 0 if unknown sound   */
		 && infos.width <= w						/* size picture */
		 && infos.height <= h)
		{
			wind_update(BEG_UPDATE);
			wind_update(BEG_MCTRL);					/* control keyboard for EVNT_MULTI */
			x=(x+((w-infos.width)/2)+15) & 0xfff0;	/* 16 pixels alignement */
			y=y+((h-infos.height)/2);				/* X,Y center           */
			
			/* options & adress command line for start movie */

			sprintf(cmde," +x%d +y%d +d -e -i +m +p +q +r +s +a%ld +j%ld",x,y,(long)event,(long)ctrl);
			/* +annnnnnnnnn: adress for control program (10 numbers max)          */
			/* +bnnnnn: force number of planes for screen (5 numbers max)         */ 
			/* +d: with dsp (-d: without dsp)                                     */
			/* +e: display errors (-e: without, default +e)                       */
			/* +hnnnnn: force height of screen (5 numbers max)                    */
			/* +i: loop (-i: without)                                             */
			/* +jnnnnnnnnnn: adress extension for control program (10 numbers max)*/
			/* +m: with pictures (-m: sound only)                                 */
			/* +p: with sound (-p: shut-off sound)                                */
			/* +q: with quality (-q: without quality)                             */
			/* +r: resample sound (-r: without)                                   */
			/* +s: pass pictures (-s: all pictures)                               */
			/* +wnnnnn: force width of screen (5 numbers max)                     */
			/* +xnnnnn, +ynnnnn: movie position (5 numbers max, default center)   */
			/* +znnnnnnnnnn: adress informations about movie (10 numbers max)     */
			strcat(cmde,path);						/* command ligne with path  */
			cmde[0]=strlen(cmde);					/* pascal format !          */
			ctrl[0]=0;
			*((void **)(&ctrl[1]))=(void *)&infos;	/* get infos */
			Pexec(0,"ANIPLAY.PRG",cmde,"");			/* start player */ 
			/* FRANCAIS: Vous pouvez aussi inclure ANIPLAY.PRG si vous le relogez */
			/* ENGLISH: You can also include ANIPLAY.PRG if you relocate it       */  

			wind_update(END_MCTRL);
			form_dial(FMD_FINISH,x,y,infos.width,infos.height,x,y,infos.width,infos.height);
			wind_update(END_UPDATE);				/* redraw */
		}			
	}
	appl_exit();
}

int event(void)

{
	int ret,mmx,mmy,mmb,mmk,key,mb;
	/* FRANCAIS: Attention, les options sont dans la ligne de commande !                      */
	/*           En 16 couleurs, le tramage est fait avec les 8 premiŠres couleurs systŠme    */
	/*           En 256 couleurs, les premiŠres couleurs ne sont pas modifi‚s si possible     */ 
	/*           Le curseur de la souris est effac‚ en dehors de ces lignes                   */
	/*           L'‚cran est sauv‚ au lancement et restaur‚ … la fin sauf en affichage X,Y    */ 
	/*           Cet exemple utilise le GEM mais vous pouvez utiliser le GEMDOS ou (X)BIOS !  */
	/*           Le player utilise seulement le GEMDOS, XBIOS et LINEA pour le curseur souris */
	/*           Attention, vous devez optimiser ces lignes pour un affichage rapide !        */
	/* ENGLISH: Warning, options are in command ligne !                                       */
	/*          In 16 colors, dithering is made with 8 first system colors                    */
	/*          In 256 colors, the player don't modify the first colors if is possible        */
	/*          The mouse is hidden out of this lines                                         */
	/*          The screen is saved at start and restored at end except in X,Y display        */
	/*          This example uses the GEM but you can uses GEMDOS or (X)BIOS !                */
	/*          The player uses only GEMDOS, XBIOS, and LINEA for hide mouse curso            */
	/*          Warning, you must optimize this lines for fast display !                      */ 
	ret=evnt_multi(MU_TIMER+MU_KEYBD,0,0,0,0,0,0,0,0,0,0,0,0,0,0L,0,0,&mmx,&mmy,&mmb,&mmk,&key,&mb);
	if(ret & MU_KEYBD)
	{
		if(key==0x4b34			/* SHIFT +   (-10S) */
		 || key==0x4d36)		/* SHIFT +   (+10S) */
		{
			picture=0;
			return(key);		/* control key (H:scan-code L:code ASCII) */
		}
		switch(key & 0xff)		/* code ASCII    */
		{
		case 0x1b:				/* ESC: stop     */
			return(key);		/* control key (H:scan-code L:code ASCII) */
		case ' ':				/* pause/play    */
			pause++; pause&=1;
			if(!pause)
				single_step=0;
			return(key);		/* control key (H:scan-code L:code ASCII) */
		case '.':				/* single step   */
			single_step=pause=1;
			picture++;
			return(key);		/* control key (H:scan-code L:code ASCII) */
		}
	}
	if(ctrl[0]==0 && ctrl[1]==0 && ctrl[2]==0)	/* work is finished ? */
	{
		printf("\r%ld S Picture: %ld    ",infos.count_seconds,infos.num_frame);
		ctrl[0]=0;
		*((void **)(&ctrl[1]))=(void *)&infos;
	}
	if(!pause && !single_step)
		picture++;
	return(0);					/* continue  */
}
