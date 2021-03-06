/* radare2 - Copyleft 2011-2014 - pancake */

#include <r_util.h>
#include <r_socket.h>

int main(int argc, char **argv) {
	char *file;
	RRunProfile *p;
	int i, ret;
	if (argc==1 || !strcmp (argv[1], "-h")) {
		eprintf ("Usage: rarun2 [-v] [script.rr2] [directive ..]\n");
		printf ("%s", r_run_help ());
		return 1;
	}
	if (!strcmp (argv[1], "-v")) {
		printf ("rarun2 "R2_VERSION"\n");
		return 0;
	}
	file = argv[1];
	if (*file && !strchr (file, '=')) {
		char *data = r_file_slurp (file, NULL);
		if (!data) {
			eprintf ("Cannot open %s\n", file);
			return 1;
		}
		p = r_run_new (data);
		free (data);
	} else {
		p = r_run_new (NULL);
		for (i = *file?1:2; i<argc; i++)
			r_run_parseline (p, argv[i]);
	}
	ret = r_run_start (p);
	r_run_free (p);
	return ret;
}
