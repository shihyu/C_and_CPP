//--- strlenªº¹ê§@½d¨Ò¢Ñ ---//
size_t strlen(const char* s)
{
	size_t len = 0;

	while (*s++)
		len++;
	return len;
}
