//--- strncpy的實作範例 ---//
char* strncpy(char* s1, const char* s2,size_t n) 
{
	char* p = s1;
	while (n) {
		n--;
		if (!(*s1++ = *s2++)) break;
	}
	while (n--)
		*s1++ = '\0';
	return p;
}
