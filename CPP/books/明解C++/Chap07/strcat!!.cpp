//--- strcat的實作範例 ---//
char* strcat(char* s1, const char* s2)
{
	char* p = s1;

	while (*s1) s1++;
	while (*s1++ = *s2++)
		;
	return p;
}
