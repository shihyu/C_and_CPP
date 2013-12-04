//--- strlen的實作範例Ｃ ---//
size_t strlen(const char* s)
{
	size_t len = 0;

	while (*s++)
		len++;
	return len;
}
