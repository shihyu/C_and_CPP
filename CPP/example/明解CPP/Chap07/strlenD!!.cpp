//--- strlenªº¹ê§@½d¨Ò¢Ò ---//
size_t strlen(const char* s)
{
	const char* p = s;

	while (*s)
		s++;
	return s - p;
}
