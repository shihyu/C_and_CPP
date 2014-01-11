//--- strlenªº¹ê§@½d¨Ò¢Ï ---//
size_t strlen(const char* s)
{
	size_t len = 0;

	while (s[len])
		len++;
	return len;
}
