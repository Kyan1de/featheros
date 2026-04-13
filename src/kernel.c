
typedef struct {
	int x;
	int y;
} cursor;

// doesnt work
void printstr(const char* str) {
	static cursor cur = {0};
	char* current = str;
	while (*current) {
		*(char*)(0xb8000 + 2 * cur.x) = *current;
		cur.x++;
		current++;
	}
	return;
}

void main() {
	printstr("Hello from kernel!");
	return;
}
