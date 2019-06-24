
/* SYNCHRO ANIPLAYER */
/* MEQUIGNON Didier December 1997 */
/* May 2000 version 1.03 */
/* Example with messages VA_START, AV_SENDKEY, and 'AP' */
/* Synchro with another APP or MIDI control */

#include <cpx.h>
#include <string.h>
#include <vdi.h>
#include <tos.h>

#define ID_CPX (long)'SANI'
#define ITEMPS 100L	/* mS */
#define VA_START 0x4711
#define AV_SENDKEY 0x4710
#define STOP 0
#define PLAY 1
#define PAUSE 2
#define FF 3
#define REW 4

#define MIDI_SONG_POS_POINT 0xf2
#define MIDI_TIMING_CLOCK 0xf8
#define MIDI_START 0xfa
#define MIDI_CONTINUE 0xfb
#define MIDI_STOP 0xfc

typedef struct
{
	long ident;
	union
	{
		long l;
		int i[2];
		char c[4];
	} v;
} COOKIE;

typedef struct
{
	char name[10];
	char play[4];
	char pause[4];
	char stop[4];
	char ff[4];
	char rew[4];
	char cmde[25];
	char cmde_app[25];
	char tempo_midi[3];
} KEYS_PRG;

typedef struct
{
	short width;
	short height;
	short planes;
	short frames_second;
	long total_frames;
	long id_picture_compression;	/* cvid for example */
	short quality;	/* B0: mono(0)/stereo(1)  B1: 8 bits(0)/16 bits(1) */
	unsigned short frequency_file;
	unsigned short frequency_machine;
	long total_samples;
	long id_sound_compression;		/* ima4 for example */
	short version_player;			/* version of Aniplayer */
	long count_seconds;
	long num_frame;
	short play;
	short reserve[11];
} INFO_ANIM;

/* prototypes */

int CDECL cpx_call(GRECT *work);
void CDECL cpx_draw(GRECT *clip);
void CDECL cpx_wmove(GRECT *work);
void CDECL cpx_timer(int *event);
void CDECL cpx_key(int kstate,int key,int *event);
void CDECL cpx_button(MRETS *mrets,int nclicks,int *event);
int CDECL cpx_hook(int event,int *msg,MRETS *mrets,int *key,int *nclicks);
void CDECL cpx_close(int flag);
OBJECT *adr_tree(int no_arbre);
CPXNODE *get_header(long id);
void change_objc(int objc,int state,GRECT *clip);
void aff_objc(int objc,GRECT *clip);
void move_cursor(void);
void wait_end_clic(void);
unsigned long code_key(int status);
unsigned int code_scan_code(char key);
int send_message_app(int type,int key,char *path);
int send_message_start(char *path);
int send_message_key(int key);
int send_message_info(int mode,long val);
void eject(void);
void stop(void);
void play(void);
void pause(void);
void rew(void);
void ff(void);
void conv_digit(char *string,int val);
void conv_hexa(char *string,int val);
unsigned long get_hexa(char *string);

/* global variables in the 1st position of DATA segment */

KEYS_PRG config={"GEMJING","","","","","","+g+l-p+s-v-k","-r2 -d2 ",120};

/* global variables */

int vdi_handle,work_in[11]={1,1,1,1,1,1,1,1,1,1,2},work_out[57];
int errno;
 
/* global variables */

XCPB *Xcpb;
GRECT *Work;
CPXNODE *head;
CPXINFO	cpxinfo={cpx_call,cpx_draw,cpx_wmove,cpx_timer,cpx_key,cpx_button,0,0,cpx_hook,cpx_close};
int id_app=0,send_info,count_send,ed_objc,new_objc,ed_pos,new_pos,load,first,start,status,old_status=-1;
long seconds;
int message[8];
char path_ani[80],path_app[80],name_ani[12],name_app[12];

/* ressource */

#define MENUBOX 0
#define MENUCMDE 2
#define MENUTEMPOMIDI 3
#define MENUAPNAME 4
#define MENUPLAY 5
#define MENUPAUSE 6
#define MENUSTOP 7
#define MENUFF 8
#define MENUREW 9
#define MENUCMDEAP 10
#define MENUINFO 11
#define MENUBEJECT 14
#define MENUBSTOP 16
#define MENUBPLAY 18
#define MENUBPAUSE 20
#define MENUBREW 22
#define MENUBFF 24
#define MENUBSAUVE 26
#define MENUBANNULE 27

char *rs_strings[] = {
	"SYNCHRO ANIPLAYER v1.03a","","",
	"abcdefghijklmnopqrstuvwx","Opt : ________________________","XXXXXXXXXXXXXXXXXXXXXXXX",
	"cba","Tempo MIDI: ___","999",
	"        ","With: ________","XXXXXXXX",
	"ABCD","Play : ____","XFFF",
	"EFGH","Pause : ____","XFFF",
	"IJKL","Stop : ____","XFFF",
	"HGEF","FF: ____","XFFF",
	"MKJI","REW: ____","XFFF",
	"MNOPQRSTUVWXYZ0123426789","Opt : ________________________","XXXXXXXXXXXXXXXXXXXXXXXX",
	"  MN SEC   ALL MN SEC","","",
	" :     :","","",
	"Save",
	"Cancel" };

long rs_frstr[] = {0};

BITBLK rs_bitblk[] = {
	(int *)0L,2,16,0,0,1,
	(int *)1L,2,16,0,0,1,
	(int *)2L,2,16,0,0,1,
	(int *)3L,2,16,0,0,1,
	(int *)4L,2,16,0,0,1,
	(int *)5L,2,16,0,0,1 };
	
long rs_frimg[] = {0};
ICONBLK rs_iconblk[] = {0};

TEDINFO rs_tedinfo[] = {
	(char *)0L,(char *)1L,(char *)2L,IBM,0,2,0x1180,0,0,32,1,
	(char *)3L,(char *)4L,(char *)5L,IBM,0,0,0x1180,0,0,25,31,
	(char *)6L,(char *)7L,(char *)8L,IBM,0,0,0x1180,0,0,4,16,
	(char *)9L,(char *)10L,(char *)11L,IBM,0,0,0x1180,0,0,9,15,
	(char *)12L,(char *)13L,(char *)14L,IBM,0,0,0x1180,0,0,5,12,
	(char *)15L,(char *)16L,(char *)17L,IBM,0,0,0x1180,0,0,5,13,
	(char *)18L,(char *)19L,(char *)20L,IBM,0,0,0x1180,0,0,5,12,
	(char *)21L,(char *)22L,(char *)23L,IBM,0,0,0x1180,0,0,5,9,
	(char *)24L,(char *)25L,(char *)26L,IBM,0,0,0x1180,0,0,5,10,
	(char *)27L,(char *)28L,(char *)29L,IBM,0,0,0x1180,0,0,25,31,
	(char *)30L,(char *)31L,(char *)32L,SMALL,0,0,0x1600,0,0,22,1,
	(char *)33L,(char *)34L,(char *)35L,IBM,0,0,0x1500,0,0,17,1 };

OBJECT rs_object[] = {
	-1,1,27,G_BOX,FL3DBAK,NORMAL,0x1100L,0,0,32,11,
	2,-1,-1,G_TEXT,FL3DBAK,SELECTED,0L,0,0,32,1,
	3,-1,-1,G_FTEXT,EDITABLE|FL3DBAK,NORMAL,1L,1,1,30,1,
	4,-1,-1,G_FTEXT,EDITABLE|FL3DBAK,NORMAL,2L,1,2,15,1,
	5,-1,-1,G_FTEXT,EDITABLE|FL3DBAK,NORMAL,3L,17,2,14,1,
	6,-1,-1,G_FTEXT,EDITABLE|FL3DBAK,NORMAL,4L,1,3,12,1,
	7,-1,-1,G_FTEXT,EDITABLE|FL3DBAK,NORMAL,5L,13,3,13,1,
	8,-1,-1,G_FTEXT,EDITABLE|FL3DBAK,NORMAL,6L,1,4,12,1,
	9,-1,-1,G_FTEXT,EDITABLE|FL3DBAK,NORMAL,7L,13,4,9,1,
	10,-1,-1,G_FTEXT,EDITABLE|FL3DBAK,NORMAL,8L,22,4,10,1,
	11,-1,-1,G_FTEXT,EDITABLE|FL3DBAK,NORMAL,9L,1,5,30,1,
	14,12,13,G_BOX,NONE,NORMAL,0xff10f1L,3,6,17,2,
	13,-1,-1,G_TEXT,FL3DBAK,NORMAL,10L,0,0,17,1,
	11,-1,-1,G_TEXT,NONE,NORMAL,11L,0,1,17,1,										/* infos */
	16,15,15,G_BOX,TOUCHEXIT|FL3DIND|FL3DBAK,NORMAL,0xff1100L,3,9,2,1,				/* eject */
	14,-1,-1,G_IMAGE,TOUCHEXIT,NORMAL,0L,0,0,2,1,
	18,17,17,G_BOX,TOUCHEXIT|FL3DIND|FL3DBAK,SELECTED,0xff1100L,6,9,2,1,			/* stop */
	16,-1,-1,G_IMAGE,TOUCHEXIT,NORMAL,1L,0,0,2,1,
	20,19,19,G_BOX,TOUCHEXIT|FL3DIND|FL3DBAK,NORMAL,0xff1100L,9,9,2,1,				/* play */
	18,-1,-1,G_IMAGE,TOUCHEXIT,NORMAL,2L,0,0,2,1,
	22,21,21,G_BOX,TOUCHEXIT|FL3DIND|FL3DBAK,NORMAL,0xff1100L,12,9,2,1,				/* pause */
	20,-1,-1,G_IMAGE,TOUCHEXIT,NORMAL,3L,0,0,2,1,
	24,23,23,G_BOX,TOUCHEXIT|FL3DIND|FL3DBAK,NORMAL,0xff1100L,15,9,2,1,				/* << */
	22,-1,-1,G_IMAGE,TOUCHEXIT,NORMAL,4L,0,0,2,1,
	26,25,25,G_BOX,TOUCHEXIT|FL3DIND|FL3DBAK,NORMAL,0xff1100L,18,9,2,1,				/* >> */
	24,-1,-1,G_IMAGE,TOUCHEXIT,NORMAL,5L,0,0,2,1,
	27,-1,-1,G_BUTTON,SELECTABLE|EXIT|FL3DIND|FL3DBAK,NORMAL,36L,23,7,6,1,			/* Save */
	0,-1,-1,G_BUTTON,SELECTABLE|EXIT|LASTOB|FL3DIND|FL3DBAK,NORMAL,37L,23,9,6,1 };	/* Cancel */

long rs_trindex[] = {0};
struct foobar {
	int dummy;
	int *image;
	} rs_imdope[] = {0};

unsigned int image_eject[]={
	0x0000,0x0000,0x0000,0x0180,0x03c0,0x07e0,0x0ff0,0x1ff8,
	0x3ffc,0x0000,0x0000,0x3ffc,0x3ffc,0x0000,0x0000,0x0000 };

unsigned int image_stop[]={
	0x0000,0x0000,0x0000,0x0000,0x1ff8,0x1ff8,0x1ff8,0x1ff8,
	0x1ff8,0x1ff8,0x1ff8,0x1ff8,0x0000,0x0000,0x0000,0x0000 };

unsigned int image_play[]={
	0x0000,0x0000,0x0000,0x2000,0x3c00,0x3f80,0x3ff0,0x3ffe,
	0x3ffe,0x3ff0,0x3f80,0x3c00,0x2000,0x0000,0x0000,0x0000 };

unsigned int image_pause[]={
	0x0000,0x0000,0x0000,0x1e78,0x1e78,0x1e78,0x1e78,0x1e78,
	0x1e78,0x1e78,0x1e78,0x1e78,0x1e78,0x0000,0x0000,0x0000 };

unsigned int image_rew[]={
	0x0000,0x0000,0x0000,0x0204,0x060c,0x0e1c,0x1e3c,0x3e7c,
	0x3e7c,0x1e3c,0x0e1c,0x060c,0x0204,0x0000,0x0000,0x0000 };

unsigned int image_ff[]={
	0x0000,0x0000,0x0000,0x2040,0x3060,0x3870,0x3c78,0x3e7c,
	0x3e7c,0x3c78,0x3870,0x3060,0x2040,0x0000,0x0000,0x0000 };

#define NUM_STRINGS 38	/* nb of strings */
#define NUM_FRSTR 0		/* strings form_alert */
#define NUM_IMAGES 0
#define NUM_BB 6		/* nb of BITBLK */
#define NUM_FRIMG 0
#define NUM_IB 0		/* nb of ICONBLK */
#define NUM_TI 12		/* nb of TEDINFO */
#define NUM_OBS 28		/* nb of objects */
#define NUM_TREE 1		/* nb of tree */ 

#define TREE1 0

CPXINFO* CDECL cpx_init(XCPB *xcpb)

{
	Xcpb=xcpb;
	return(&cpxinfo);
}

int CDECL cpx_call(GRECT *work)

{
	KEYS_PRG *header;
	OBJECT *dma_tree;
	TEDINFO *t_edinfo;
	BITBLK *b_itblk;
	register char *p;
	if(!(Xcpb->SkipRshFix))
	{
		(*Xcpb->rsh_fix)(NUM_OBS,NUM_FRSTR,NUM_FRIMG,NUM_TREE,rs_object,rs_tedinfo,rs_strings,rs_iconblk,rs_bitblk,rs_frstr,rs_frimg,rs_trindex,rs_imdope);
		rs_object[MENUINFO].ob_y+=4;
		b_itblk=rs_object[MENUBEJECT+1].ob_spec.bitblk;
		b_itblk->bi_pdata=(int *)image_eject;
		b_itblk=rs_object[MENUBSTOP+1].ob_spec.bitblk;
		b_itblk->bi_pdata=(int *)image_stop;
		b_itblk=rs_object[MENUBPLAY+1].ob_spec.bitblk;
		b_itblk->bi_pdata=(int *)image_play;
		b_itblk=rs_object[MENUBPAUSE+1].ob_spec.bitblk;
		b_itblk->bi_pdata=(int *)image_pause;
		b_itblk=rs_object[MENUBREW+1].ob_spec.bitblk;
		b_itblk->bi_pdata=(int *)image_rew;
		b_itblk=rs_object[MENUBFF+1].ob_spec.bitblk;
		b_itblk->bi_pdata=(int *)image_ff;
	}
	if((id_app=appl_find("XCONTROL"))<0
	 && (id_app=appl_find("ZCONTROL"))<0
	 && (id_app=appl_find("COPS    "))<0
	 && (id_app=appl_find("FREEDOM2"))<0)
		return(0);
	if((vdi_handle=Xcpb->handle)>0)
	{
		v_opnvwk(work_in,&vdi_handle,work_out);
		if(vdi_handle<=0 || (head=get_header(ID_CPX))==0)
			return(0);
	}
	else
		return(0);
	if(work_out[13]<16)	/* nb colors */
	{
		t_edinfo=(TEDINFO *)rs_object[MENUINFO+1].ob_spec.tedinfo;
		t_edinfo->te_color=0x1000;
		t_edinfo=(TEDINFO *)rs_object[MENUINFO+2].ob_spec.tedinfo;
		t_edinfo->te_color=0x1000;
	}
	rs_object[MENUBOX].ob_x=work->g_x;
	rs_object[MENUBOX].ob_y=work->g_y;
	rs_object[MENUBOX].ob_width=work->g_w;
	rs_object[MENUBOX].ob_height=work->g_h;
	header=(KEYS_PRG *)head->cpxhead.buffer;
	if(*header->name==0)	/* buffer of header is always to 0 with ZCONTROL */
		*header=config;  
	t_edinfo=(TEDINFO *)rs_object[MENUCMDE].ob_spec.tedinfo;
  	strcpy(t_edinfo->te_ptext,header->cmde);
	t_edinfo=(TEDINFO *)rs_object[MENUAPNAME].ob_spec.tedinfo;
  	strcpy(t_edinfo->te_ptext,header->name);
	t_edinfo=(TEDINFO *)rs_object[MENUPLAY].ob_spec.tedinfo;
	memcpy(t_edinfo->te_ptext,header->play,4);
	t_edinfo=(TEDINFO *)rs_object[MENUPAUSE].ob_spec.tedinfo;
	memcpy(t_edinfo->te_ptext,header->pause,4);
	t_edinfo=(TEDINFO *)rs_object[MENUSTOP].ob_spec.tedinfo;
	memcpy(t_edinfo->te_ptext,header->stop,4);	
	t_edinfo=(TEDINFO *)rs_object[MENUFF].ob_spec.tedinfo;
	memcpy(t_edinfo->te_ptext,header->ff,4);
	t_edinfo=(TEDINFO *)rs_object[MENUREW].ob_spec.tedinfo;
	memcpy(t_edinfo->te_ptext,header->rew,4);
	t_edinfo=(TEDINFO *)rs_object[MENUCMDEAP].ob_spec.tedinfo;
  	strcpy(t_edinfo->te_ptext,header->cmde_app);
	if(!header->tempo_midi[0])
	{
		header->tempo_midi[0]='1'; header->tempo_midi[1]='2'; header->tempo_midi[2]='0';
	}
  	t_edinfo=(TEDINFO *)rs_object[MENUTEMPOMIDI].ob_spec.tedinfo;
	memcpy(t_edinfo->te_ptext,header->tempo_midi,3);
	ed_pos=ed_objc=0;
	cpx_draw(work);
	ed_objc=MENUAPNAME;
	status=STOP;
	seconds=0;
	count_send=send_info=load=first=start=0;
	objc_edit(rs_object,ed_objc,0,&ed_pos,ED_INIT);
	new_objc=ed_objc;
	new_pos=ed_pos;
	Work=work;
	(*Xcpb->Set_Evnt_Mask)(MU_KEYBD|MU_BUTTON|MU_TIMER,0L,0L,ITEMPS);
	return(1);					/* CPX isn't finished */
}

void CDECL cpx_draw(GRECT *clip)

{
	aff_objc(0,clip);
}

void CDECL cpx_wmove(GRECT *work)

{
	rs_object[MENUBOX].ob_x=work->g_x;
	rs_object[MENUBOX].ob_y=work->g_y;
	rs_object[MENUBOX].ob_width=work->g_w;
	rs_object[MENUBOX].ob_height=work->g_h;
}

int CDECL cpx_hook(int event,int *msg,MRETS *mrets,int *key,int *nclicks)

{
	INFO_ANIM *info; 
	register char *p;
	register long total_time;
	register TEDINFO *t_edinfo;
	if(mrets && key && nclicks);
	if(send_info && (event & MU_MESAG) && msg[0]=='AP')
	{
		info=*((INFO_ANIM **)(&msg[3]));
		if(info->play)
			status=PLAY;
		else
			status=PAUSE;
		if(!info->id_picture_compression
		 && !info->id_sound_compression)
			status=STOP;
		if(start && status==PLAY)
		{
			send_message_app(VA_START,0,path_app);
			start=0;
		}
		t_edinfo=(TEDINFO *)rs_object[MENUINFO+2].ob_spec.tedinfo;
		p=t_edinfo->te_ptext;
		if(status==STOP)
		{
			conv_digit(&p[1],0);
			conv_digit(&p[4],0);
			conv_digit(&p[11],0);
			conv_digit(&p[14],0);		
			seconds=0;
		}
		else
		{		
			seconds=info->count_seconds;
			if(info->id_sound_compression && info->frequency_file)
				total_time=info->total_samples/info->frequency_file;
			else			
				total_time=info->total_frames/info->frames_second;
			conv_digit(&p[1],(int)(info->count_seconds/60L));
			conv_digit(&p[4],(int)(info->count_seconds%60L));
			conv_digit(&p[11],(int)(total_time/60L));
			conv_digit(&p[14],(int)(total_time%60L));
		}
		aff_objc(MENUINFO,Work);
		if(status!=old_status)
		{
			switch(status)
			{
			case PLAY:
				change_objc(MENUBSTOP,NORMAL,Work);
				change_objc(MENUBPLAY,SELECTED,Work);
				change_objc(MENUBPAUSE,NORMAL,Work);
				break;
			case PAUSE:
				change_objc(MENUBSTOP,NORMAL,Work);
				change_objc(MENUBPLAY,NORMAL,Work);
				change_objc(MENUBPAUSE,SELECTED,Work);
				break;				
			default:
				change_objc(MENUBSTOP,SELECTED,Work);
				change_objc(MENUBPLAY,NORMAL,Work);
				change_objc(MENUBPAUSE,NORMAL,Work);
			}
		}
		old_status=status;
		send_info=0;
		count_send=0;	
	}
	return(0);
}

void CDECL cpx_timer(int *event)

{
	static long pos=0;
	static int count_timer=10,clock_sec=48;
	register int tempo_midi;
	register TEDINFO *t_edinfo;
	if(*event);
	count_timer++;
	if(count_timer>9)
	{
		count_timer=0;
		if(!send_info || count_send<5)
		{
			if(send_message_info(0,0L))
			{
				send_info=1;
				count_send++;
			}
			else
				count_send=0;
		}
		t_edinfo=(TEDINFO *)rs_object[MENUTEMPOMIDI].ob_spec.tedinfo;
		tempo_midi=120;
		if(t_edinfo->te_ptext[0]!=0)
		{
			tempo_midi=t_edinfo->te_ptext[0] & 0xf;
			if(t_edinfo->te_ptext[1]!=0)
			{
				tempo_midi*=10;
				tempo_midi+=(t_edinfo->te_ptext[1] & 0xf);
				if(t_edinfo->te_ptext[2]!=0)
				{
					tempo_midi*=10;
					tempo_midi+=(t_edinfo->te_ptext[2] & 0xf);
				}
			}
		}
		clock_sec=(tempo_midi*48)/120;
	}
	while(Bconstat(3))						/* MIDI IN */
	{
		switch((int)Bconin(3))
		{
		case MIDI_START:
			play();
			if(seconds && send_message_info(1,0))
				seconds=pos=0;				/* movie to 0 seconds */
			break;
		case MIDI_CONTINUE:
			play();
			break;
		case MIDI_STOP:
			pause();	
			break;
		case MIDI_TIMING_CLOCK:
			pos++;
			break;
		case MIDI_SONG_POS_POINT:
			pos=(long)(Bconin(3)+(Bconin(3)<<7))*6L;
			seconds=pos/(long)clock_sec;
			send_message_info(1,seconds);	/* seek movie */
			break;
		}
	}
}

void CDECL cpx_key(int kstate,int key,int *event)

{
	register int i,dial;
	register TEDINFO *t_edinfo;
	if(kstate);
	if(*event);
	dial=form_keybd(rs_object,ed_objc,ed_objc,key,&new_objc,&key);
	if(!key && dial)
	{
		if(new_objc)
		{
			t_edinfo=(TEDINFO *)rs_object[new_objc].ob_spec.tedinfo;
			for(i=0;t_edinfo->te_ptext[i];i++);
			new_pos=i;				/* cursor in end of zone edited */
		}
	}
	else
	{
		if(rs_object[ed_objc].ob_flags & EDITABLE)
		{
			switch(key & 0xff00)
			{
			case 0x7300:			/* ctrl + left */
				new_objc=ed_objc;	/* same zone */
				new_pos=0;			/* cursor at left */
				key=0;
				break;
			case 0x7400:			/* ctrl + right */
				new_objc=ed_objc;	/* same zone */
				key=0;
				t_edinfo=(TEDINFO *)rs_object[new_objc].ob_spec.tedinfo;
				for(i=0;t_edinfo->te_ptext[i];i++);
				new_pos=i;			/* cursor in end of zone */
			}
		}
	}
	if(key>0)
	{
		objc_edit(rs_object,ed_objc,key,&ed_pos,ED_CHAR);	/* text edited in usual zone */
		new_objc=ed_objc;
		new_pos=ed_pos;
	}
	if(dial)						/* if 0 => new_objc contains object EXIT */
		move_cursor();
	else
	{
		change_objc(new_objc,NORMAL,Work);
		*event=1;					/* end */
		cpx_close(0);
	}	
}

void CDECL cpx_button(MRETS *mrets,int nclicks,int *event)

{
	KEYS_PRG *header;
	GRECT menu;
	register TEDINFO *t_edinfo;
	register int i,j,ret,objc_clic,pos_clic;
	int x,y,m,k,xoff,yoff,attrib[10];
	if((objc_clic=objc_find(rs_object,0,2,mrets->x,mrets->y))>=0)
	{
		if(form_button(rs_object,objc_clic,nclicks,&new_objc))
		{
			if(new_objc>0)
			{
				objc_offset(rs_object,objc_clic,&xoff,&yoff);
				t_edinfo=(TEDINFO *)rs_object[objc_clic].ob_spec.tedinfo;
				vqt_attributes(vdi_handle,attrib);
				/* attrib[8] = largeur du cadre des caractŠres */
				for(i=0;t_edinfo->te_ptmplt[i];i++);	/* size of mask string */
				if((pos_clic=rs_object[objc_clic].ob_width-i*attrib[8])>=0)
				{
					switch(t_edinfo->te_just)
					{
					case TE_RIGHT: 			/* justified to right */
						pos_clic=mrets->x-xoff-pos_clic;
						break;
					case TE_CNTR:			/* centred */
						pos_clic=mrets->x-xoff-pos_clic/2;
						break;
					case TE_LEFT:			/* justified to left */
					default:
						pos_clic=mrets->x-xoff;
					}
				}
				else
					pos_clic=mrets->x-xoff;
				new_pos=-1;
				pos_clic/=attrib[8];		/* position character checked */
				j=-1;
				do
				{
					if(t_edinfo->te_ptmplt[++j]=='_')
						new_pos++;
				}
				while(j<i && j<pos_clic);	/* end if cursor on end of string or position character checked */
				if(j>=i)
					new_pos=-1;						/* cursor in end of string */
				else
				{
					j--;
					while(t_edinfo->te_ptmplt[++j]!='_' && j<i);
					if(j>=i)
						new_pos=-1;					/* cursor in end of string */
				}
				for(i=0;t_edinfo->te_ptext[i];i++);	/* size of string text */
				if(new_pos<0 || i<new_pos)
					new_pos=i;
			}
			move_cursor();
		}
		else
		{
			switch(objc_clic)
			{
			case MENUBEJECT:
			case MENUBEJECT+1:
				eject();
				break;
			case MENUBSTOP:
			case MENUBSTOP+1:
				stop();
				break;
			case MENUBPLAY:
			case MENUBPLAY+1:
				play();
				break;
			case MENUBPAUSE:
			case MENUBPAUSE+1:
				pause();
				break;
			case MENUBREW:
			case MENUBREW+1:
				rew();
				break;
			case MENUBFF:
			case MENUBFF+1:
				ff();
				break;
			case MENUBSAUVE:
				change_objc(MENUBSAUVE,NORMAL,Work);
				if((*Xcpb->XGen_Alert)(SAVE_DEFAULTS))
				{
					header=(KEYS_PRG *)head->cpxhead.buffer;
					t_edinfo=(TEDINFO *)rs_object[MENUCMDE].ob_spec.tedinfo;
  					strcpy(header->cmde,t_edinfo->te_ptext);
					t_edinfo=(TEDINFO *)rs_object[MENUAPNAME].ob_spec.tedinfo;
  					strcpy(header->name,t_edinfo->te_ptext);
					t_edinfo=(TEDINFO *)rs_object[MENUPLAY].ob_spec.tedinfo;
  					memcpy(header->play,t_edinfo->te_ptext,4);
					t_edinfo=(TEDINFO *)rs_object[MENUPAUSE].ob_spec.tedinfo;
  					memcpy(header->pause,t_edinfo->te_ptext,4);
					t_edinfo=(TEDINFO *)rs_object[MENUSTOP].ob_spec.tedinfo;
  					memcpy(header->stop,t_edinfo->te_ptext,4);
					t_edinfo=(TEDINFO *)rs_object[MENUFF].ob_spec.tedinfo;
  					memcpy(header->ff,t_edinfo->te_ptext,4);
					t_edinfo=(TEDINFO *)rs_object[MENUREW].ob_spec.tedinfo;
  					memcpy(header->rew,t_edinfo->te_ptext,4);
					t_edinfo=(TEDINFO *)rs_object[MENUCMDEAP].ob_spec.tedinfo;
  					strcpy(header->cmde_app,t_edinfo->te_ptext);				
					t_edinfo=(TEDINFO *)rs_object[MENUTEMPOMIDI].ob_spec.tedinfo;
  					memcpy(header->tempo_midi,t_edinfo->te_ptext,3);				
					if(((*Xcpb->Save_Header)(head))==0)
						(*Xcpb->XGen_Alert)(FILE_ERR);
					config=*header;
					if(((*Xcpb->CPX_Save)((void *)&config,sizeof(KEYS_PRG)))==0)
						(*Xcpb->XGen_Alert)(FILE_ERR);
				}
				break;
			case MENUBANNULE:
				change_objc(MENUBANNULE,NORMAL,Work);
				*event=1;	/* end */
				cpx_close(0);
			}
		}
	}
}

void CDECL cpx_close(int flag)

{
	int x,y,m,k;
	if(flag);
	objc_edit(rs_object,ed_objc,0,&ed_pos,ED_END);
	v_clsvwk(vdi_handle);
}

OBJECT *adr_tree(int no_arbre)

{
	register int i,arbre;
	if(!no_arbre)
		return(rs_object);
	for(i=arbre=0;i<NUM_OBS;i++)
	{
		if(rs_object[i].ob_flags & LASTOB)
		{
			arbre++;
			if(arbre==no_arbre)
				return(&rs_object[i+1]);
		}
	}
	return(0L);
}

CPXNODE *get_header(long id)

{
	register CPXNODE *p;
	p=(CPXNODE *)(*Xcpb->Get_Head_Node)();	/* header for first CPX */
	do
	{
		if(p->cpxhead.cpx_id==id)
			return(p);
	}
	while(p->vacant && (p=p->next)!=0);		/* no more headers */
	return(0L);
}

void change_objc(int objc,int state,GRECT *clip)

{
	rs_object[objc].ob_state=state;
	aff_objc(objc,clip);
}

void aff_objc(int objc,GRECT *clip)

{
	register GRECT *rect;
	register int curseur=0;
	wind_update(BEG_UPDATE);
	if(objc==MENUBOX)
	{
		objc_edit(rs_object,ed_objc,0,&ed_pos,ED_END);		/* hide cursor */
		curseur=1;
	}
	rect=(GRECT *)(*Xcpb->GetFirstRect)(clip);
	while(rect)
	{
		objc_draw(rs_object,objc,2,PTRS(rect));
		rect=(GRECT *)(*Xcpb->GetNextRect)();
	}
	if(curseur)
		objc_edit(rs_object,ed_objc,0,&ed_pos,ED_END);		/* showm cursor */
	wind_update(END_UPDATE);
}

void move_cursor(void)

{
	if(new_objc>0 && (ed_objc!=new_objc || ed_pos!=new_pos))
	{
		objc_edit(rs_object,ed_objc,0,&ed_pos,ED_END);		/* hide cursor */
		ed_pos=new_pos;
		objc_edit(rs_object,new_objc,0,&ed_pos,ED_CHAR);	/* new position of cursor */
		objc_edit(rs_object,new_objc,0,&ed_pos,ED_END);		/* showm cursor */
		ed_objc=new_objc;									/* new zone edited */
		ed_pos=new_pos;										/* new position cursor */
	}
}

void wait_end_clic(void)

{
	int x,y,m,k;
	do
		graf_mkstate(&x,&y,&m,&k);
	while(m);
}

unsigned long code_key(int status)

{
	register TEDINFO *t_edinfo;
	switch(status)
	{
	case PLAY:
		t_edinfo=(TEDINFO *)rs_object[MENUPLAY].ob_spec.tedinfo;
		break;
	case PAUSE:
		t_edinfo=(TEDINFO *)rs_object[MENUPAUSE].ob_spec.tedinfo;
		break;
	case FF:
		t_edinfo=(TEDINFO *)rs_object[MENUFF].ob_spec.tedinfo;
		break;
	case REW:
		t_edinfo=(TEDINFO *)rs_object[MENUREW].ob_spec.tedinfo;
		break;
	default:
		t_edinfo=(TEDINFO *)rs_object[MENUSTOP].ob_spec.tedinfo;
	}
	switch(strlen(t_edinfo->te_ptext))
	{
	case 0:
		return(0);
	case 1:
		return(code_scan_code(t_edinfo->te_ptext[0]));
	default:	
		return(get_hexa(t_edinfo->te_ptext));
	}
}

unsigned int code_scan_code(char key)

{
	KEYTAB *tab;
	register unsigned int i;
	tab=Keytbl((void *)-1,(void *)-1,(void *)-1);
	for(i=0;i<128;i++)
	{
		if(tab->shift[i]==key)
			break;
		if(tab->unshift[i]==key)
			break;
		if(tab->capslock[i]==key)
			break;
	}
	i<<=8;		/* scan-code */
	return(i | (unsigned int)key);
}

int send_message_app(int type,int key,char *path)

{
	static char buf[128];
	register int id;
	register TEDINFO *t_edinfo;	
	t_edinfo=(TEDINFO *)rs_object[MENUAPNAME].ob_spec.tedinfo;
	if((key || path) && (id=appl_find(t_edinfo->te_ptext))>0)
	{
		message[0]=type;
		message[1]=id_app;
		message[2]=0;
		if(path==0)
		{
			message[3]=0;
			message[4]=key;
		}
		else
		{
			t_edinfo=(TEDINFO *)rs_object[MENUCMDEAP].ob_spec.tedinfo;
			strcpy(buf,t_edinfo->te_ptext);	
			strcat(buf,path);			
			*((char **)(&message[3]))=buf;
		}
		message[5]=message[6]=message[7]=0;
		appl_write(id,16,message);
		return(1);
	}
	return(0);
}

int send_message_start(char *path)

{
	static char buf[128];
	register int id;
	register TEDINFO *t_edinfo;	
	if((id=appl_find("ANIPLAY "))>=0)
	{
		t_edinfo=(TEDINFO *)rs_object[MENUCMDE].ob_spec.tedinfo;
		strcpy(buf,t_edinfo->te_ptext);	
		strcat(buf,path);		
		message[0]=VA_START;
		message[1]=id_app;
		message[2]=0;
		*((char **)(&message[3]))=buf;
		message[5]=message[6]=message[7]=0;
		appl_write(id,16,message);
		return(1);
	}
	form_alert(1,"[2][No communication|with ANIPLAY][Cancel]");
	return(0);
}

int send_message_key(int key)

{
	register int id;
	if((id=appl_find("ANIPLAY "))>=0)
	{
		message[0]=AV_SENDKEY;
		message[1]=id_app;
		message[2]=message[3]=0;
		message[4]=key;
		message[5]=message[6]=message[7]=0;
		appl_write(id,16,message);
		return(1);
	}
	return(0);
}

int send_message_info(int mode,long val)

{
	register int id;
	if((id=appl_find("ANIPLAY "))>=0)
	{
		message[0]='AP';
		message[1]=id_app;
		message[3]=mode;
		*((char **)(&message[4]))=(char *)val;		
		message[2]=message[6]=message[7]=0;
		appl_write(id,16,message);
		return(1);
	}
	return(0);
}

void eject(void)

{
	int ret;
	register int car;
	register TEDINFO *t_edinfo;	
	change_objc(MENUBEJECT,SELECTED,Work);
	t_edinfo=(TEDINFO *)rs_object[MENUCMDE].ob_spec.tedinfo;
	if(!(t_edinfo->te_ptext[0]=='+' && t_edinfo->te_ptext[1]=='n'))
	{
		send_message_key(0x6100);	/* UNDO */
		evnt_timer(100,0);
	}
	path_ani[0]=Dgetdrv()+'A';path_ani[1]=':';Dgetpath(path_ani+2,Dgetdrv()+1);
	strcat(path_ani,"\\");strcat(path_ani,"*.*");
	strcpy(path_app,path_ani);
	fsel_exinput(path_ani,name_ani,&ret,"Video for Aniplayer");
    if(path_ani[0]>='A' && path_ani[0]<='Z')
	{
		car=strlen(path_ani)-1;	
		while(path_ani[car]!='\\')
			path_ani[car--]=0;
		Dsetdrv(path_ani[0]-'A');Dsetpath(path_ani+2);
		strcat(path_ani,name_ani);
	}
	if(ret)
	{
		ret=0;
		t_edinfo=(TEDINFO *)rs_object[MENUAPNAME].ob_spec.tedinfo;
		if(appl_find(t_edinfo->te_ptext)>0)
		{
			fsel_exinput(path_app,name_app,&ret,"File for Application");
		    if(path_app[0]>='A' && path_app[0]<='Z')
			{
				car=strlen(path_app)-1;	
				while(path_app[car]!='\\')
					path_app[car--]=0;
				Dsetdrv(path_app[0]-'A');Dsetpath(path_app+2);
				strcat(path_app,name_app);
			}
		}
		if(ret)
		{
			if(send_message_start(path_ani)
			 && send_message_info(0,0L))
			{
				change_objc(MENUBSTOP,NORMAL,Work);
				change_objc(MENUBPLAY,SELECTED,Work);
				change_objc(MENUBPAUSE,NORMAL,Work);
				send_info=1;
				count_send++;
				start=1;
				status=old_status=PLAY;
			}
		}
		else
		{
			if(send_message_start(path_ani)
			 && send_message_key('.'))
			{
				change_objc(MENUBSTOP,NORMAL,Work);
				change_objc(MENUBPLAY,NORMAL,Work);
				change_objc(MENUBPAUSE,SELECTED,Work);
				*path_app=0;
				evnt_timer(100,0);
				if(send_message_key('.'))	/* display first picture and pause */
					send_message_app(AV_SENDKEY,(int)code_key(PAUSE),0);
				status=old_status=PAUSE;
			}
		}
		load=first=1;
	}
	else
	{
		change_objc(MENUBSTOP,SELECTED,Work);
		change_objc(MENUBPLAY,NORMAL,Work);
		change_objc(MENUBPAUSE,NORMAL,Work);	
		status=old_status=STOP;
		load=0;
	}
	change_objc(MENUBEJECT,NORMAL,Work);
}

void stop(void)

{
	if(send_message_key(0x6100)) 	/* UNDO */
	{
		change_objc(MENUBSTOP,SELECTED,Work);
		change_objc(MENUBPLAY,NORMAL,Work);
		change_objc(MENUBPAUSE,NORMAL,Work);
		send_message_app(AV_SENDKEY,(int)code_key(STOP),0);
		status=old_status=STOP;	
	}
	wait_end_clic();
}

void play(void)

{
	if(load && status==STOP)
	{
		if(send_message_start(path_ani))
		{
			change_objc(MENUBSTOP,NORMAL,Work);
			change_objc(MENUBPLAY,SELECTED,Work);
			change_objc(MENUBPAUSE,NORMAL,Work);
			seconds=0;
			if(*path_app && send_message_info(0,0L))
			{
				send_info=1;
				count_send++;
				start=1;
			}
			status=old_status=PLAY;
		}
	}
	else
	{
		if(send_message_key('P'))
		{
			change_objc(MENUBSTOP,NORMAL,Work);
			change_objc(MENUBPLAY,SELECTED,Work);
			change_objc(MENUBPAUSE,NORMAL,Work);
			if(first && send_message_key(0x4b34))	/* SHIFT +   (-10S) */	
			{
				first=0;
				seconds=0;
			}
			send_message_app(AV_SENDKEY,(int)code_key(PLAY),0);
			status=old_status=PLAY;
		}
	}
	wait_end_clic();
}

void pause(void)

{
	if(send_message_key(' '))
	{
		change_objc(MENUBSTOP,NORMAL,Work);
		change_objc(MENUBPLAY,NORMAL,Work);
		change_objc(MENUBPAUSE,SELECTED,Work);
		status=old_status=PAUSE;	
		send_message_app(AV_SENDKEY,(int)code_key(PAUSE),0);
	}
	wait_end_clic();
}

void rew(void)

{
	change_objc(MENUBREW,SELECTED,Work);
	if(send_message_info(1,seconds-10))	/* or send_message_key(0x4b34)  SHIFT +   (-10S) */
		send_message_app(AV_SENDKEY,(int)code_key(REW),0);
	wait_end_clic();	
	change_objc(MENUBREW,NORMAL,Work);

}

void ff(void)

{
	change_objc(MENUBFF,SELECTED,Work);
	if(send_message_info(1,seconds+11))	/* or send_message_key(0x4d36)  SHIFT +   (+10S) */
		send_message_app(AV_SENDKEY,(int)code_key(FF),0);
	wait_end_clic();
	change_objc(MENUBFF,NORMAL,Work);
}

void conv_digit(char *string,int val)

{
	if(val>99)
		string[0]=string[1]='?';
	else
	{
		string[0]=(char)(val/10+16);
		string[1]=(char)(val%10+16);
	}
}

unsigned long get_hexa(char *string)

{
	register char *p;
	register int err,i,j;
	register long val;
	p=string;
	j=strlen(string);
	for(err=i=0;i<j && p[i];i++)
	{
		if(!((p[i]>='0' && p[i]<='9') || (p[i]>='A' && p[i]<='F')))
			err=1;
	}
	if(err || (i & 1) || i<2)
		return(0);
	else
	{
		val=0;
		for(i=0;i<j;i++)
		{
			val<<=4;
			if(p[i]>='0' && p[i]<='9')
				val |= (p[i] & 0xf);
			else
				val |= (p[i]-'A'+10);
		}
	}
	return(val);
}
