#include "mystdio.h"

void
my_panic_for_any_reason(char *str)
{
	my_str("ERROR: ");
	my_str(str);
	my_str("\n");
}

void
my_panic(char *str, char *mode)
{
	my_str("ERROR: ");
	my_str(str);
	my_str(" failed using '");
	my_str(mode);
	my_str("' mode.\n");
}

int
main()
{
	char *buff;
	fpos_t fpos;
	t_my_file *fp;

	/* Testing "r" mode */
	buff = my_strdup("Hello, World!\n");
	if ((fp = my_fopen("test.txt", "r")) == NULL)
		my_panic("fopen", "r");
	if (my_fputc('A', fp) != EOF)
		my_panic("fputc", "r");
	if (my_fputs(buff, fp) != EOF)
		my_panic("fputs", "r");
	(void)my_fseek(fp, 0, SEEK_SET);
	if (my_fgetc(fp) == EOF)
		my_panic("fgetc", "r");
	if (my_fseek(fp, 0, SEEK_SET) == -1)
		my_panic("fseek", "r");
	if (my_fgets(buff, 1, fp) == NULL)
		my_panic("fgets", "r");
	(void)my_fseek(fp, 0, SEEK_END);
	if (my_ftell(fp) != fp->taille)
		my_panic("ftell", "r");
	my_rewind(fp);
	if (fp->pos != 0)
		my_panic("rewind", "r");
	fpos = 5;
	(void)my_fsetpos(fp, &fpos);
	if (my_ftell(fp) != fpos)
		my_panic("fsetpos", "r");
	fpos = 0;
	(void)my_fgetpos(fp, &fpos);
	if (my_ftell(fp) != fpos)
		my_panic("fgetpos", "r");
	(void)my_fseek(fp, 0, SEEK_SET);
	free(buff);
	buff = my_strdup("No more world.\n");
	if (my_fwrite(buff, 1, 1, fp) != 0)
		my_panic("fwrite", "r");
	if (my_fread(buff, 1, 1, fp) == 0)
		my_panic("fread", "r");
	if (my_fflush(fp) != EOF)
		my_panic("fflush", "r");
	if (my_fclose(fp) != 0)
		my_panic("fclose", "r");
	free(buff);


	/* Testing "r+" mode */
	buff = my_strdup("Hello, World!\n");
	if ((fp = my_fopen("test.txt", "r+")) == NULL)
		my_panic("fopen", "r+");
	if (my_fputc('A', fp) == EOF)
		my_panic("fputc", "r+");
	if (my_fputs(buff, fp) == EOF)
		my_panic("fputs", "r+");
	(void)my_fseek(fp, 0, SEEK_SET);
	if (my_fgetc(fp) == EOF)
		my_panic("fgetc", "r+");
	if (my_fseek(fp, 0, SEEK_SET) == -1)
		my_panic("fseek", "r+");
	if (my_fgets(buff, 1, fp) == NULL)
		my_panic("fgets", "r+");
	(void)my_fseek(fp, 0, SEEK_END);
	if (my_ftell(fp) != fp->taille)
		my_panic("ftell", "r+");
	my_rewind(fp);
	if (fp->pos != 0)
		my_panic("rewind", "r+");
	fpos = 5;
	(void)my_fsetpos(fp, &fpos);
	if (my_ftell(fp) != fpos)
		my_panic("fsetpos", "r+");
	fpos = 0;
	(void)my_fgetpos(fp, &fpos);
	if (my_ftell(fp) != fpos)
		my_panic("fgetpos", "r+");
	(void)my_fseek(fp, 0, SEEK_SET);
	free(buff);
	buff = my_strdup("No more world.\n");
	if (my_fwrite(buff, 1, 1, fp) == 0)
		my_panic("fwrite", "r+");
	if (my_fread(buff, 1, 1, fp) == 0)
		my_panic("fread", "r+");
	if (my_fflush(fp) == EOF)
		my_panic("fflush", "r+");
	if (my_fclose(fp) != 0)
		my_panic("fclose", "r+");
	free(buff);


	/* Testing "w" mode */
	buff = my_strdup("Hello, World!\n");
	if ((fp = my_fopen("test.txt", "w")) == NULL)
		my_panic("fopen", "w");
	if (my_fputc('A', fp) == EOF)
		my_panic("fputc", "w");
	if (my_fputs(buff, fp) == EOF)
		my_panic("fputs", "w");
	(void)my_fseek(fp, 0, SEEK_SET);
	if (my_fgetc(fp) != EOF)
		my_panic("fgetc", "w");
	if (my_fseek(fp, 0, SEEK_SET) == -1)
		my_panic("fseek", "w");
	if (my_fgets(buff, 1, fp) != NULL)
		my_panic("fgets", "w");
	(void)my_fseek(fp, 0, SEEK_END);
	if (my_ftell(fp) != fp->taille)
		my_panic("ftell", "w");
	my_rewind(fp);
	if (fp->pos != 0)
		my_panic("rewind", "w");
	fpos = 5;
	(void)my_fsetpos(fp, &fpos);
	if (my_ftell(fp) != fpos)
		my_panic("fsetpos", "w");
	fpos = 0;
	(void)my_fgetpos(fp, &fpos);
	if (my_ftell(fp) != fpos)
		my_panic("fgetpos", "w");
	(void)my_fseek(fp, 0, SEEK_SET);
	free(buff);
	buff = my_strdup("No more world.\n");
	if (my_fwrite(buff, 1, my_strlen(buff), fp) == 0)
		my_panic("fwrite", "w");
	if (my_fread(buff, 1, 1, fp) != 0)
		my_panic("fread", "w");
	if (my_fflush(fp) == EOF)
		my_panic("fflush", "w");
	if (my_fclose(fp) != 0)
		my_panic("fclose", "w");
	free(buff);


	/* Testing "w+" mode */
	buff = my_strdup("Hello, World!\n");
	if ((fp = my_fopen("test.txt", "w+")) == NULL)
		my_panic("fopen", "w+");
	if (my_fputc('A', fp) == EOF)
		my_panic("fputc", "w+");
	if (my_fputs(buff, fp) == EOF)
		my_panic("fputs", "w+");
	(void)my_fseek(fp, 0, SEEK_SET);
	if (my_fgetc(fp) == EOF)
		my_panic("fgetc", "w+");
	if (my_fseek(fp, 0, SEEK_SET) == -1)
		my_panic("fseek", "w+");
	if (my_fgets(buff, 1, fp) == NULL)
		my_panic("fgets", "w+");
	(void)my_fseek(fp, 0, SEEK_END);
	if (my_ftell(fp) != fp->taille)
		my_panic("ftell", "w+");
	my_rewind(fp);
	if (fp->pos != 0)
		my_panic("rewind", "w+");
	fpos = 5;
	(void)my_fsetpos(fp, &fpos);
	if (my_ftell(fp) != fpos)
		my_panic("fsetpos", "w+");
	fpos = 0;
	(void)my_fgetpos(fp, &fpos);
	if (my_ftell(fp) != fpos)
		my_panic("fgetpos", "w+");
	(void)my_fseek(fp, 0, SEEK_SET);
	free(buff);
	buff = my_strdup("No more world.\n");
	if (my_fwrite(buff, 1, my_strlen(buff), fp) == 0)
		my_panic("fwrite", "w+");
	if (my_fread(buff, 1, 1, fp) == 0)
		my_panic("fread", "w+");
	if (my_fflush(fp) == EOF)
		my_panic("fflush", "w+");
	if (my_fclose(fp) != 0)
		my_panic("fclose", "w+");
	free(buff);


	/* Testing "a" mode */
	buff = my_strdup("Hello, World!\n");
	if ((fp = my_fopen("test.txt", "a")) == NULL)
		my_panic("fopen", "a");
	if (my_fputc('A', fp) == EOF)
		my_panic("fputc", "a");
	if (my_fputs(buff, fp) == EOF)
		my_panic("fputs", "a");
	(void)my_fseek(fp, 0, SEEK_SET);
	if (my_fgetc(fp) != EOF)
		my_panic("fgetc", "a");
	if (my_fseek(fp, 0, SEEK_SET) == -1)
		my_panic("fseek", "a");
	if (my_fgets(buff, 4, fp) != NULL)
		my_panic("fgets", "a");
	(void)my_fseek(fp, 0, SEEK_END);
	if (my_ftell(fp) != fp->taille)
		my_panic("ftell", "a");
	my_rewind(fp);
	if (fp->pos != 0)
		my_panic("rewind", "a");
	fpos = 5;
	(void)my_fsetpos(fp, &fpos);
	if (my_ftell(fp) != fpos)
		my_panic("fsetpos", "a");
	fpos = 0;
	(void)my_fgetpos(fp, &fpos);
	if (my_ftell(fp) != fpos)
		my_panic("fgetpos", "a");
	(void)my_fseek(fp, 0, SEEK_SET);
	free(buff);
	buff = my_strdup("No more world.\n");
	if (my_fwrite(buff, 1, my_strlen(buff), fp) == 0)
		my_panic("fwrite", "a");
	if (my_fread(buff, 1, 1, fp) != 0)
		my_panic("fread", "a");
	/* Additional test for append */
	if (my_ftell(fp) != fp->taille)
		my_panic("Failed to return pointer to end of file when writing", "a");
	if (my_fflush(fp) == EOF)
		my_panic("fflush", "a");
	if (my_fclose(fp) != 0)
		my_panic("fclose", "a");
	free(buff);


	/* Testing "a+" mode */
	buff = my_strdup("Hello, World!\n");
	if ((fp = my_fopen("test.txt", "a")) == NULL)
		my_panic("fopen", "a");
	if (my_fputc('A', fp) == EOF)
		my_panic("fputc", "a");
	if (my_fputs(buff, fp) == EOF)
		my_panic("fputs", "a");
	(void)my_fseek(fp, 0, SEEK_SET);
	if (my_fgetc(fp) != EOF)
		my_panic("fgetc", "a");
	if (my_fseek(fp, 0, SEEK_SET) == -1)
		my_panic("fseek", "a");
	if (my_fgets(buff, 4, fp) != NULL)
		my_panic("fgets", "a");
	(void)my_fseek(fp, 0, SEEK_END);
	if (my_ftell(fp) != fp->taille)
		my_panic("ftell", "a");
	my_rewind(fp);
	if (fp->pos != 0)
		my_panic("rewind", "a");
	fpos = 5;
	(void)my_fsetpos(fp, &fpos);
	if (my_ftell(fp) != fpos)
		my_panic("fsetpos", "a");
	fpos = 0;
	(void)my_fgetpos(fp, &fpos);
	if (my_ftell(fp) != fpos)
		my_panic("fgetpos", "a");
	(void)my_fseek(fp, 0, SEEK_SET);
	free(buff);
	buff = my_strdup("No more world.\n");
	if (my_fwrite(buff, 1, my_strlen(buff), fp) == 0)
		my_panic("fwrite", "a");
	if (my_fread(buff, 1, 1, fp) != 0)
		my_panic("fread", "a");
	/* Additional test for append */
	if (my_ftell(fp) != fp->taille)
		my_panic("Failed to return pointer to end of file when writing", "a+");
	if (my_fflush(fp) == EOF)
		my_panic("fflush", "a");
	if (my_fclose(fp) != 0)
		my_panic("fclose", "a");
	free(buff);


	/* Let's break shit */
	if (my_fopen("test.t", "r") != NULL)
		my_panic_for_any_reason("Actually opened non-existent file.\n");
	if (my_fopen("test.txt", "+r") != NULL)
		my_panic_for_any_reason("Using '+r' actually went through.\n");
	if (my_fopen("test.txt", "+br") != NULL)
		my_panic_for_any_reason("Using '+br' actually went through.\n");
	if (my_fopen("test.txt", "+rb") != NULL)
		my_panic_for_any_reason("Using '+rb' actually went through.\n");

	return (0);
}
