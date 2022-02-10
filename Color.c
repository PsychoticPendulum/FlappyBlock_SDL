#include "Color.h"

#define ANSI_RED    	"\x1b[31m"
#define ANSI_YELLOW  	"\x1b[33m"
#define ANSI_GREEN   	"\x1b[32m"
#define ANSI_CYAN    	"\x1b[36m"
#define ANSI_BLUE    	"\x1b[34m"
#define ANSI_MAGENTA 	"\x1b[35m"
#define ANSI_WHITE	 	"\x1b[39m"
#define ANSI_LIGHT_GREY	"\x1b[38m"
#define ANSI_DARK_GREY	"\x1b[39m"
#define ANSI_BLACK		"\x1b[30m"
#define ANSI_RESET   	"\x1b[0m"

struct Colors Init_Colors() {
	struct Colors colors;

	printf("Initializing Colors ...\n");

	// LIGHT_GREY
	colors.LIGHT_GREY.r = 0x40;
	colors.LIGHT_GREY.g = 0x40;
	colors.LIGHT_GREY.b = 0x40;
	colors.LIGHT_GREY.a = 0xff;
	
	// DARK_GREY
	colors.DARK_GREY.r = 0x10;
	colors.DARK_GREY.g = 0x10;
	colors.DARK_GREY.b = 0x10;
	colors.DARK_GREY.a = 0xff;

	// DARK_GREEN
	colors.DARK_GREEN.r = 0x0;
	colors.DARK_GREEN.g = 0x23;
	colors.DARK_GREEN.b = 0x0;
	colors.DARK_GREEN.a = 0xff;

	// WHITE
	colors.WHITE.r = 0xff;
	colors.WHITE.g = 0xff;
	colors.WHITE.b = 0xff;
	colors.WHITE.a = 0xff;
	printf(ANSI_WHITE "  -> WHITE\n" ANSI_RESET);
	
	// BLACK
	colors.BLACK.r = 0x0;
	colors.BLACK.g = 0x0;
	colors.BLACK.b = 0x0;
	colors.BLACK.a = 0xff;
	printf(ANSI_BLACK "  -> BLACK\n" ANSI_RESET);

	// RED
	colors.RED.r = 0xff;
	colors.RED.g = 0x0;
	colors.RED.b = 0x0;
	colors.RED.a = 0xff;
	printf(ANSI_RED "  -> RED\n" ANSI_RESET);

	// YELLOW
	colors.YELLOW.r = 0xff;
	colors.YELLOW.g = 0xff;
	colors.YELLOW.b = 0x0;
	colors.YELLOW.a = 0xff;
	printf(ANSI_YELLOW "  -> YELLOW\n" ANSI_RESET);
	
	// GREEN
	colors.GREEN.r = 0x0;
	colors.GREEN.g = 0xff;
	colors.GREEN.b = 0x0;
	colors.GREEN.a = 0xff;
	printf(ANSI_GREEN "  -> GREEN\n" ANSI_RESET);
	
	// CYAN
	colors.CYAN.r = 0x0;
	colors.CYAN.g = 0xff;
	colors.CYAN.b = 0xff;
	colors.CYAN.a = 0xff;
	printf(ANSI_CYAN "  -> CYAN\n" ANSI_RESET);
	
	// BLUE
	colors.BLUE.r = 0x0;
	colors.BLUE.g = 0x0;
	colors.BLUE.b = 0xff;
	colors.BLUE.a = 0xff;
	printf(ANSI_BLUE "  -> BLUE\n" ANSI_RESET);
	
	// MAGENTA
	colors.MAGENTA.r = 0xff;
	colors.MAGENTA.g = 0x0;
	colors.MAGENTA.b = 0xff;
	colors.MAGENTA.a = 0xff;
	printf(ANSI_MAGENTA "  -> MAGENTA\n" ANSI_RESET);

	return colors;
}
