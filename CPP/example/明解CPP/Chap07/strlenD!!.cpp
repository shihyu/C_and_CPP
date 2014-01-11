//--- strlen的實作範例Ｄ ---//
size_t strlen(const char* s)
{
	const char* p = s;

	while (*s)
		s++;
	return s - p;
}
