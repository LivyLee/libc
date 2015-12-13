#include <stdio.h>
#include <stddef.h>
#include <stdarg.h>
#include <format.h>
#include <stdbool.h>
int vsnprintf(char *str, size_t size, const char *formatting, va_list args) {
	int count;
	struct format_buffer buffer;
	if (!size) {
		return 0;
	}
	buffer.start = str;
	buffer.end = str + size - 1;
	count = format(put_string, &buffer, formatting, args);
	*buffer.start = '\0';
	return count;
}

int snprintf(char *str, size_t size, const char *formatting, ...) {
	va_list args;
	int count;
	va_start(args, formatting);
	count = vsnprintf(str, size, formatting, args);
	va_end(args);
	return count;
}

int vsprintf(char *str, const char *formatting, va_list args) {
	int count;
	struct format_buffer buffer;

	buffer.start = str;
	buffer.end = 0;
	count = format(put_string, &buffer, formatting, args);
	*buffer.start = '\0';
	return count;
}

int sprintf(char *str, const char *formatting, ...) {
	va_list args;
	int count;
	va_start(args, formatting);
	count = vsprintf(str, formatting, args);
	va_end(args);
	return count;
}

static bool put_string(char c, void *data) {
	struct format_buffer *buffer = data;
	if (buffer->start != buffer->end) {
		*buffer->start++ = c;
	}
	return true;
}
