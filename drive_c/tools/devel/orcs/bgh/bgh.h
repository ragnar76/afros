#ifndef _BGH_H_
#define _BGH_H_

#ifdef __cplusplus
extern "C" {
#endif

#define BGHI_COOKIE 0x42474849 /* 'BGHI' */

typedef struct
{
	WORD	Version;
	char*	Info;
	ULONG	(*Load)(const char* Name, WORD Mode);
	void	(*Free)(ULONG BGH_Handle);
	char*	(*GetHelpString)(ULONG BGH_Handle, WORD Section, WORD Guppe, WORD Index);
}BGH_Cookie;



#ifdef __cplusplus
}
#endif


#endif  /* _BGH_H_ */
