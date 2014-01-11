//--- strlenªº¹ê§@½d¨Ò¢Ð ---//
size_t strlen(const char* s)
{
	size_t len = 0;

	for ( ; s[len]; len++)
		;
	return len;
}
