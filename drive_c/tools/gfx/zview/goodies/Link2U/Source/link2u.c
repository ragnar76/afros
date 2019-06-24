/*

===============================================================================
	(c) 02.05.1998 by Daniel Augsburger
===============================================================================

	Daniel Augsburger                       http://www.jumpgates.com/skydiver
	Jasminweg 39                                       skydiver@jumpgates.com
	8050 ZÅrich
	SCHWEIZ

===============================================================================

	Beschreibung:

		Setzt einen link vom 'usr'-verzeichnis von gcc auf u:\usr und
		entfehrnt den Link u:\a.


		W I C H T I G

		Diese Programm ist nur fÅr die Verwendung unter MagiC vorgesehen!
		(Am besten in den 'start'-Ordner damit.)

===============================================================================
Datum					Beschreibung												Version
-------------------------------------------------------------------------------
02.05.1998			Erstellung													 0.1
03.05.1998			Suche nach config-file									 0.11
03.05.1998			Alert mit Fehlermaldung									 0.12
03.05.1998			Erkennt alle Keywords									 0.13
03.05.1998			Abarbeitung von 'link2u.cnf' komplett				 0.14
04.05.1998			Keine Fehlermeldung, wenn link bereits
						oder zu lîschendes File nicht existiert.			 0.141
31.05.1998			FÅr SymLink wird nicht mehr getestet, ob
						Source-File existiert									 0.142
23.05.1998			Fehlermeldungen mit Nr. der fehlerhaften Zeile	 0.15
23.05.1998			Fsfirst durch Fxattr ersetzt							 0.151
23.05.1998			FÅr SymLink wird getestet, ob Source existiert	 0.152
20.07.2001			Fehler in process_file() korrigiert: kein
						Absturz mehr, falls $HOME nicht existiert			 0.153
-------------------------------------------------------------------------------
===============================================================================

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <boolean.h>
//#include <mycdefs.h>

#include <osbind.h>
#include <mintbind.h>
#include <aesbind.h>

#include "link2u.h"

extern short _global[];

int ap_id;


/*
	Sets for each argument (separated by SPACE) a pointer to a string
	containing thisargument.
	NOTE: this function destroys the content of line.
*/
void get_args(char **args, char *line)
{
	int i = 0;	//char counter
	int a = 0;	//argument counter

	while (line[i] != '\0')
	{
		args[a++] = &line[i];
		while ((line[i] != '\0') && (line[i] != SPACE))
		{
			i++;
		}
		if (line[i] != '\0')
			line[i++] = '\0';
	}
}


int parse_file(FILE *file, int *error_line)
{
	char ch;
	char line[MAX_LINE_LENGTH];
	int i;
	BOOLEAN eol = FALSE;

	char *args[3];

	char drive_u[] = "u:\\";
	char delpath[16];

/*
	struct XATTR
	{
		UWORD mode;
		LONG index;
		UWORD dev;
		UWORD reserved1;
		UWORD nlink;
		UWORD uid;
		UWORD gid;
		LONG size;
		LONG blksize;
		LONG nblocks;
		WORD mtime;
		WORD mdate;
		WORD atime;
		WORD adate;
		WORD ctime;
		WORD cdate;
		WORD attr;
		WORD reserved2;
		LONG reserved3;
		LONG reserved4;
	} xattr;
*/
	struct XATTR
	{
		unsigned short mode;
		long index;
		unsigned short dev;
		unsigned short reserved1;
		unsigned short nlink;
		unsigned short uid;
		unsigned short gid;
		long size;
		long blksize;
		long nblocks;
		short mtime;
		short mdate;
		short atime;
		short adate;
		short ctime;
		short cdate;
		short attr;
		short reserved2;
		long reserved3;
		long reserved4;
	} xattr;


	*error_line = 0;

	ch = fgetc(file);
	while (!feof(file))
	{

	/* read next line */

		(*error_line)++;

		i = 0;
		eol = FALSE;
		while (!feof(file) && !eol)
		{
			switch (ch)
			{
				case LF :
					eol = TRUE;
					break;
				case CR :
					eol = TRUE;
					break;
				default:
					eol = FALSE;
					line[i++] = ch;
			}
			ch = fgetc(file);
		}
		line[i] = '\0';

	/* parse current line */

//		printf("%s\n", line);

		/* comment line */
		if (strncmp(line, KEY_COMMENT, strlen(KEY_COMMENT)) == 0)
		{
//			printf(">%s\n", KEY_COMMENT);
		}

		/* create symbolic link */
		else if (strncmp(line, KEY_SYMLINK, strlen(KEY_SYMLINK)) == 0)
		{
//			printf(">%s\n", KEY_SYMLINK);
			args[0] = args[1] = args[2] = NULL;
			get_args(args, line);
			if ((args[0] != NULL) && (args[1] != NULL) && (args[2] != NULL))
			{
//				printf("&&%s\n", args[0]);
//				printf("&&%s\n", args[1]);
//				printf("&&%s\n", args[2]);
//				if (Fsfirst(args[1], 0x10 | 0x20) == 0)
				if (Fxattr(0, args[1], &xattr) == 0)
				{
//					if (Fsymlink(args[1], args[2]) != 0)
//						return (ERROR_COULDNT_CREATE_LINK);
					Fsymlink(args[1], args[2]);
				}
				else
					return(ERROR_FILE_NOT_FOUND);
		}
			else
				return(ERROR_IN_FILE);
		}

		/* delete drive link on u */
		else if (strncmp(line, KEY_DELETE_ON_U, strlen(KEY_DELETE_ON_U)) == 0)
		{
//			printf(">%s\n", KEY_DELETE_ON_U);
			args[0] = args[1] = NULL;
			get_args(args, line);
			if ((args[0] != NULL) && (args[1] != NULL) && (strlen(args[1]) == 1))
			{
				strcpy(delpath, drive_u);
				strcat(delpath, args[1]);
//				printf("&&%s\n", delpath);
//				if (Fdelete(delpath) != 0)
//					return (ERROR_DELETING_FILE);
				Fdelete(delpath);
			}
			else
				return (ERROR_IN_FILE);
		}

		/* empty line */
		else if (line[0] == '\0')
		{
//			printf(">\n");
		}
		else
		{
			return(ERROR_IN_FILE);
		}


	}


	return (0);		// no error has occured
}


int process_file(int *error_line)
{
	FILE *cnf;

	char *env_value;
//	char **env_result = &env_value;
	char env_home[] = "HOME=";

	char filename[256];
	int len;

	int error;


//	shel_envrn(env_result, env_home);
	shel_envrn(&env_value, env_home);

	if (env_value != NULL)				// if $HOME exists
	{
		strcpy(filename, env_value);
		len = strlen(filename);
		if ((filename[len - 1] != '\\') && (filename[len - 1] != '/'))
		{
			strcat(filename, "\\");
		}
		strcat(filename, CNF_FILE);
//		printf("filename=\"%s\"\r\n", filename);
		if((cnf = fopen(filename, "r")) == NULL)			//	suche cnf file in HOME directory
		{
			strcpy(filename, CNF_FILE);
//			printf("filename=\"%s\"\r\n", filename);
			if ((cnf = fopen(filename, "r")) == NULL)		// suche cnf file im aktuellen directory
			{
				return(ERROR_CNF_NOT_FOUND);
			}
		}
	}
	else										// look in current directory
	{
		strcpy(filename, CNF_FILE);
//		printf("filename=\"%s\"\r\n", filename);
		if ((cnf = fopen(filename, "r")) == NULL)		// suche cnf file im aktuellen directory
		{
			return(ERROR_CNF_NOT_FOUND);
		}
	}


	error = parse_file(cnf, error_line);


	fclose(cnf);

	return (error);
}

void show_alert(char *s1, char *s2, int line_no)
{
	char message[256];
	const int digits = 3;
	char line[digits + 1];
	int factor, val, dig;
	int digcounter;
	int i;

	line[0] = '\0';

	factor = 1;
	for (i = 0; i < digits - 1; factor *= 10, i++);

	val = 0;
	digcounter = 0;
	for (i = 0; i < digits; i++)
	{
		val *= 10;
		dig = line_no / factor;		//get next digit
		val += dig;
		line_no -= factor * dig;	//remove left most digit from line number
		factor /= 10;
		if (dig > 0 || val > 0)
		{
			line[digcounter++] = dig + '0';
			line[digcounter] = '\0';
		}
	}

	strcpy(message, s1);
	strcat(message, line);
	strcat(message, s2);

	form_alert(1, message);
}

int main(int argc, char *argv[])
{
	char alert_cnf_not_found[] = "[1][Couldn't find \"link2u.cnf\". ][Abort]";
	char alert_error_in_file1[] = "[1][\"link2u.cnf\" line ";
	char alert_error_in_file2[] = ": |unknown command.][Abort]";
	char alert_file_not_found1[] = "[1][\"link2u.cnf\" line ";
	char alert_file_not_found2[] = ": |file not found. ][Abort]";
	char alert_couldnt_create_link1[] = "[1][\"link2u.cnf\" line ";
	char alert_couldnt_create_link2[] = ": |couldn't create symbolic link.|Perhaps because source file |doesn't exist or link already |exists. ][Abort]";
	char alert_deleting_file1[] = "[1][\"link2u.cnf\" line ";
	char alert_deleting_file2[] = ": |couldn't delete file. |Perhaps because specified |file doesn't exist. ][Abort]";

	int error;
	int error_line;

	Pdomain(1);		// Wechsel in die MiNT-Domain

	ap_id = appl_init();


	if ((error = process_file(&error_line)) != 0)
	{
		switch (error)
		{
			case ERROR_CNF_NOT_FOUND :
				form_alert(1, alert_cnf_not_found);
				break;
			case ERROR_FILE_NOT_FOUND :
				show_alert(alert_file_not_found1, alert_file_not_found2, error_line);
				break;
			case ERROR_COULDNT_CREATE_LINK :
				show_alert(alert_couldnt_create_link1, alert_couldnt_create_link2, error_line);
				break;
			case ERROR_DELETING_FILE :
				show_alert(alert_deleting_file1, alert_deleting_file2, error_line);
				break;
			default:
				show_alert(alert_error_in_file1, alert_error_in_file2, error_line);
		}
		exit(EXIT_FAILURE);
	}


	appl_exit();
	exit(EXIT_SUCCESS);

	return 0;
}
