/*-
 * Trevor Miranda
 * CS392
 */
#include "my.h"

int main()
{
	char s1[] = "AHACKERNAMED4CHAN", s2[] = "THEFAPPENING", s3[] = "RACECAR", s4[] = "", *s5 = NULL;

	/* my_str() */
	my_str("\nTesting my_str...\n");
	my_str("-->");
	my_str("");
	my_str("<-- (empty string)\n");

	my_str("-->");
	my_str(NULL);
	my_str("<-- (NULL = empty string)\n");

	/* my_char() */
	my_str("\nTesting my_char...\n");

	my_str("-->");
	my_char('a');
	my_str("<-- (a)\n");

	my_str("-->");
	my_char(0);
	my_str("<-- (NULL)\n");
	
	my_str("-->");
	my_char(-100);
	my_str("<-- (unknown character symbol)\n");

	/* my_int() */
	my_str("\nTesting my_int...\n");

	my_str("-->");
	my_int(234);
	my_str("<-- (234)\n");

	my_str("-->");
	my_int(-234);
	my_str("<-- (-234)\n");

	my_str("-->");
	my_int(0);
	my_str("<-- (0)\n");

	my_str("-->");
	my_int(~0U >> 1);
	my_str("<-- (INT_MAX)\n");

	my_str("-->");
	my_int((~0U >> 1) + 1);
	my_str("<-- (INT_MIN)\n");

	my_str("-->");
	my_int(152000);
	my_str("<-- (152000)\n");

	/* my_alpha() */
	my_str("\nTesting my_alpha...\n");

	my_str("-->");
	my_alpha();
	my_str("<-- (AaBb...Zz)\n");

	/* my_digits() */
	my_str("\nTesting my_digits...\n");

	my_str("-->");
	my_digits();
	my_str("<-- (0123...9)\n");

	/* my_num_base() */
	my_str("\nTesting my_num_base...\n");

	my_str("-->");
	my_num_base(123, "0123456789");
	my_str("<-- (123)\n");

	my_str("-->");
	my_num_base(-123, "0123456789");
	my_str("<-- (-123)\n");

	my_str("-->");
	my_num_base(9, "01");
	my_str("<-- (1001)\n");

	my_str("-->");
	my_num_base(7, "!?#");
	my_str("<-- (#?)\n");

	my_str("-->");
	my_num_base(-7, "!?#");
	my_str("<-- (-#?)\n");

	my_str("-->");
	my_num_base(3, "!");
	my_str("<-- (!!!)\n");

	my_str("-->");
	my_num_base(-3, "!");
	my_str("<-- (-!!!)\n");
	
	my_str("-->");
	my_num_base(~0U >> 1, "0123456789");
	my_str("<-- (INT_MIN)\n");
	
	my_str("-->");
	my_num_base((~0U >> 1) + 1, "0123456789");
	my_str("<-- (INT_MAX)\n");

	my_str("-->");
	my_num_base(0, "!");
	my_str("<-- (nothing)\n");

	my_str("vvvvvvvvvvvvvvv\n");
	my_num_base(5, "");
	my_str("--------------- (Base not valid)\n");

	my_str("vvvvvvvvvvvvvvv\n");
	my_num_base(-5, "");
	my_str("--------------- (Base not valid)\n");

	my_str("vvvvvvvvvvvvvvv\n");
	my_num_base(5, NULL);
	my_str("--------------- (Base not valid)\n");

	my_str("vvvvvvvvvvvvvvvv\n");
	my_num_base(-5, NULL);
	my_str("--------------- (Base not valid)\n");

	/* my_revstr() */
	my_str("\nTesting my_revstr...\n");

	/* Even-length string */
	my_str("-->");
	my_int(my_revstr(s1));
	my_str("; ");
	my_str(s1);
	my_str("<--- (17; NAHC4DEMANREKCAHA)\n");

	/* Odd-length string */
	my_str("-->");
	my_int(my_revstr(s2));
	my_str("; ");
	my_str(s2);
	my_str("<-- (12; GNINEPPAFEHT)\n");

	/* Palindrome string */
	my_str("-->");
	my_int(my_revstr(s3));
	my_str("; ");
	my_str(s3);
	my_str("<-- (7; RACECAR)\n");
	
	/* Empty string */
	my_str("-->");
	my_int(my_revstr(s4));
	my_str("; ");
	my_str(s4);
	my_str("<-- (0; [empty])\n");
	
	/* NULL string */
	my_str("-->");
	my_int(my_revstr(s5));
	my_str("; ");
	my_str(s5);
	my_str("<-- (-1; [empty])\n");

	/* my_strlen() */
	my_str("\nTesting my_strlen...\n");

	my_str("-->");
	my_int(my_strlen("Hello, World!"));
	my_str("<-- (13)\n");

	my_str("-->");
	my_int(my_strlen(""));
	my_str("<-- (0)\n");

	my_str("-->");
	my_int(my_strlen(NULL));
	my_str("<-- (-1)\n");

	/* my_strpos() */
	my_str("\nTesting my_strpos...\n");

	my_str("-->");
	my_int(my_strpos("Have you met my waifu?", 'u'));
	my_str("<-- (7)\n");

	my_str("-->");
	my_int(my_strpos("", 'a'));
	my_str("<-- (-1)\n");

	my_str("-->");
	my_int(my_strpos(NULL, 'a'));
	my_str("<-- (-1)\n");

	my_str("-->");
	my_int(my_strpos("Test", '\0'));
	my_str("<-- (-1)\n");

	/* my_strrpos() */
	my_str("\nTesting my_strrpos...\n");

	my_str("-->");
	my_int(my_strrpos("Have you met my waifu?", 'u'));
	my_str("<-- (20)\n");

	my_str("-->");
	my_int(my_strrpos("", 'a'));
	my_str("<-- (-1)\n");

	my_str("-->");
	my_int(my_strrpos(NULL, 'a'));
	my_str("<-- (-1)\n");

	my_str("-->");
	my_int(my_strrpos("Test", '\0'));
	my_str("<-- (-1)\n");
	
	return (0);
}
