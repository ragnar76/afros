void get_args(char **args, char *line);
int parse_file(FILE *file, int *error_line);
int process_file(int *error_line);
void show_alert(char *s1, char *s2, int line_no);
int main(int argc, char *argv[]);

#define CNF_FILE "link2u.cnf"
#define MAX_LINE_LENGTH 256

#define ERROR_CNF_NOT_FOUND -1
#define ERROR_IN_FILE -2
#define ERROR_FILE_NOT_FOUND -3
#define ERROR_COULDNT_CREATE_LINK -4
#define ERROR_DELETING_FILE -5

#define KEY_COMMENT "#"
#define KEY_SYMLINK "sln"
#define KEY_DELETE_ON_U "delu"

#define LF 0xa
#define CR 0xd
#define SPACE 0x20
