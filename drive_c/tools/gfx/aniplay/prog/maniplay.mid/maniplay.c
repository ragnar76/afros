/* Module MANIPLAY for HORLOGEP in no freezing mode */
/* Start ANIPLAYER in PRG or ACC mode */

#include <aes.h>
#include <tos.h>
#include <portab.h>
#include <string.h>

#include "midnight.h"	/* ACC_str + MOD_str + defines for Module + ACC */

#define Ms MOD_struct

#define VA_START 0x4711
#define AV_SENDKEY 0x4710

extern MOD_str	MOD_struct;

Value Values[3]=
{
	T_TITEL,0,0,"V1.0, MEQUIGNON Didier December 1997",
	T_TITEL,0,0,"Path Aniplayer (.INF): xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
	T_TITEL|T_END,0,0,"Options & Video: 01234567890123456789012345678901234567890123456789012345678901234567890123456789"
};

Value *Value_s = Values;

ULONG MOD_main(int Mode,ACC_str *As)

{
	static char buffer[256];
	static char *cmde;
	static int fin,id,id_app,wi_id;
	static message[8];
	register int i,handle;
	register char *p1,*p2;
	int x,y,w,h;
	
	switch(Mode)
	{	
	case M_INIT:
		MOD_struct.U.b=0x003f;
		fin=0;
		p1=Value_s[1].Name;
		for(i=0;*p1 && *p1!=':';i++,p1++);
		p1+=2;
		*p1=0;
		p2=Value_s[2].Name;
		for(i=0;*p2 && *p2!=':';i++,p2++);
		p2+=2;
		*p2=0;
		strcpy(&MOD_struct.MyName[strlen(MOD_struct.MyName)-3],"INF");
		handle=Fopen(MOD_struct.MyName,0);			/* open INF file */
		if(handle<0)
			return(0);
		if(Fread(handle,255,buffer)<=0)
		{
			Fclose(handle);
			return(0);
		}
		Fclose(handle);
		for(i=0;buffer[i] && i<256;i++)
		{
			if(buffer[i]==13 || buffer[i]==10)
				buffer[i]=0;
		}
		cmde=buffer;
		for(i=0;*cmde!=' ' && i<256;i++,cmde++);
		if(i>=256)
			return(0);
		*cmde++=0;
		for(i=0;buffer[i] && i<80;*p1++=buffer[i++]);
		*p1=0;
		for(i=0;cmde[i] && i<80;*p2++=cmde[i++]);
		*p2=0;
		id_app=appl_find(0);
		break;
	case M_SWITCH:
		break;
	case M_DO_IT:
		if((id=appl_find("ANIPLAY "))<=0)			/* search Aniplayer */
		{
			if((wi_id=wind_find(1,1))!=0)			/* window for module */
				wind_get(wi_id,WF_CURRXYWH,&x,&y,&w,&h);
			shel_write(1,1,100,buffer,"");			/* if PRG start */
			EVNT_ask(1000);
			if(wi_id && w >= As->w && h >= As->h)
			{
				x=i=0;
				while(x!=wi_id && i<5)				/* window in TOP */
				{									/* after start PRG */
					EVNT_ask(1000);
					wind_set(wi_id,WF_TOP,0,0,0,0);
					wind_get(wi_id,WF_TOP,&x,&y,&w,&h);
					i++;							/* time-out ! */
				}	
			}
		}
		if((id=appl_find("ANIPLAY "))>0)
		{
			message[0]=VA_START;					/* cmde line and file in INF */
			message[1]=id_app;
			message[2]=0;
			*((char **)(&message[3]))=cmde;
			message[5]=message[6]=message[7]=0;
			appl_write(id,16,message);
		}
		else
		{
			form_alert(1,"[2][No communication|with ANIPLAY][Cancel]");
			return(0);
		}
		do
		{
			fin=EVNT_ask(10);						/* tempo in mS */
		}
		while(!fin);
		if((id=appl_find("ANIPLAY "))>0)
		{
			message[0]=AV_SENDKEY;
			message[1]=id_app;
			message[4]=0x1b;						/* ESC for end */
			message[2]=message[3]=message[5]=message[6]=message[7]=0;
			appl_write(id,16,message);
		}
		break;
	case M_EXIT:
		break;
	}
	return(1);
}
