#include <stdio.h>
#include <stdlib.h>



void print_menu(void);
void print_start(void);
void print_version_data(void);
char get_cmd(void);
void parse_cmd(char cmd);

#define MAX_PORT 65535


void
print_startup(void)
{
    printf("             ________________________________________________   \n");
    printf("            /                                                \\  \n");
    printf("           |    _________________________________________     | \n");
    printf("           |   |                                         |    | \n");
    printf("           |   |  > hacktheplanet                        |    | \n");
    printf("           |   |  > press any key to pwn ...             |    | \n");
    printf("           |   |  > _ |                                  |    | \n");
    printf("           |   |                                         |    | \n");
    printf("           |   |                                         |    | \n");    
    printf("           |   |                                         |    | \n");
    printf("           |   |                                         |    | \n");
    printf("           |   |                                         |    | \n");
    printf("           |   |                                         |    | \n");
    printf("           |   |                                         |    | \n");
    printf("           |   |                                         |    | \n");
    printf("           |   |_________________________________________|    | \n");
    printf("           |                                                  | \n");
    printf("            \\_________________________________________________/ \n");
    printf("                   \\___________________________________/        \n");
    printf("                ___________________________________________     \n");
    printf("             _-'    .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.  --- `-_  \n");
    printf("          _-'.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.  .-.-.`-_ \n");
    printf("       _-'.-.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-`__`. .-.-.-.`-_ \n");
    printf("    _-'.-.-.-.-. .-----.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-----. .-.-.-.-.`-_ \n");
    printf(" _-'.-.-.-.-.-. .---.-. .-------------------------. .-.---. .---.-.-.-.`-_ \n");
    printf(":-------------------------------------------------------------------------: \n");
    printf("`---._.-------------------------------------------------------------._.---' \n");
    printf("\n\n\n");
}




struct Service {
    int16_t port_no;
    char *service_name;
};

char service_name[0x400] = "NEW_SERVICEaaaabaaacaaadaaaeaaafaaagaaahaaaiaaajaaakaaalaaamaaanaaaoaaapaaaqaaaraaasaaataaauaaavaaawaaaxaaayaaazaabbaabcaabdaabeaabfaabgaabhaabiaabjaabkaablaabmaabnaaboaabpaabqaabraabsaabtaabuaabvaabwaabxaabyaabzaacbaaccaacdaaceaacfaacgaachaaciaacjaackaaclaacmaacnaac";

struct Service services[MAX_PORT] = {
    {0, "NA"},
    {1, "NA"},
    {2, "NA"},
    {3, "NA"},
    {4, "NA"},
    {5, "NA"},
    {6, "NA"},
    {7, "NA"},
    {8, "NA"},
    {9, "NA"},
    {10, "NA"},
    {11, "NA"},
    {12, "NA"},
    {13, "NA"},
    {14, "NA"},
    {15, "NA"},
    {16, "NA"},
    {17, "NA"},
    {18, "NA"},
    {19, "NA"},
    {20, "FTP"},
    {21, "FTP"},
    {22, "SSH" },
    {23, "TELNET" },
    {24, "SMTP" },
    {25, "SMTP" },
    {26, "NA"},
    {27, "NA"},
    {28, "NA"},
    {29, "NA"},
    {30, "NA"},
    {31, "NA"},
    {32, "NA"},
    {33, "NA"},
    {34, "NA"},
    {35, "NA"},
    {36, "NA"},
    {37, "NA"},
    {38, "NA"},
    {39, "NA"},
    {40, "NA"},
    {41, "NA"},
    {42, "NA"},
    {43, "NA"},
    {44, "NA"},
    {45, "NA"},
    {46, "NA"},
    {47, "NA"},
    {48, "NA"},
    {49, "NA"},
    {50, "NA"},
    {51, "NA"},
    {52, "NA"},
    {53, "DNS"},
    {54, "NA"},
    {55, "NA"},
    {56, "NA"},
    {57, "NA"},
    {58, "NA"},
    {59, "NA"},
    {60, "NA"},
    {61, "NA"},
    {62, "NA"},
    {63, "NA"},
    {64, "NA"},
    {65, "NA"},
    {66, "NA"},
    {67, "NA"},
    {68, "NA"},
    {69, "FTFP"},
    {70, "NA"},
    {71, "NA"},
    {72, "DNS"},
    {73, "NA"},
    {74, "NA"},
    {75, "NA"},
    {76, "NA"},
    {77, "NA"},
    {78, "NA"},
    {79, "NA"},
    { 80, "HTTP" },
    
    // bordem overtook me
    { 443, "HTTPS" },
    { 8080, "HTTP_8080" },
    { 3306, "MYSQL" },
};



void
do_service_lookup(int16_t port_no)
{
    struct Service service = services[port_no];
    printf("Service: %s\n", service.service_name);
}


void
pop_shell(void)
{
    int port;
    char host[20];

    printf("> Spooling up network runner ... \n");
    printf("> Starting config manager ... \n\n");

    printf("Enter R_PORT: ");
    scanf("%d", &port);
    getchar();  // skipnewline



    // scuffed port check
    if (port > 65535 || port < 0) {
        printf("Thats not a valid port!\n");
        exit(1);
    }

    port = (int16_t) port;

    printf("Enter R_HOST: ");
    fgets(host, 16, stdin);

    printf("\n:::::::::::::::: [CONFIG] :::::::::::::::: \n");
    printf("  R_PORT: %hd\n", port);
    printf("  R_HOST: %s\n", host);

    // do sth bad with the port
    printf("Performing service lookup based on port number ...\n");
    do_service_lookup(port);
}



void
print_version_data()
{
    printf(":::::::::::::::: [Bitkill3r V1.0] ::::::::::::::::\n\n");

    printf("Release         -> 0x42 \n");
    printf("Build           -> 0x6447 \n");
    printf("Compiled with   -> libc-2.33.so\n");
    
    printf("\n\n");
}


char
get_cmd()
{
    int size;
    int count = 0x10;

    for (int i = 0; i < count; i++)
        size = i;

    char cmd_buf[size];

    printf(">_ ");
    fgets(cmd_buf, count, stdin);

    return cmd_buf[0];
}


void
parse_cmd(char cmd)
{
    switch (cmd) {
        case 'h':
            print_menu();
            break;
        case 'v':
            print_version_data();
            break;
        case 'q':
            printf("\n> Happy hunting, and remember fu*ck windows\n");
            exit(0);
            break;
        case 's':
            pop_shell();
            break;
        default:
            printf("> Command not recognised\n");
            print_menu();
            break;

    }
}


void
print_menu(void)
{
    printf(">-> Welcome hacker <-<\n\n");

    printf("(h) Print this menu\n");
    printf("(v) Print version data\n");
    printf("(s) Pop a shell\n");
    printf("(q) Quit\n");

    printf("\n\n");
}



int main(void)
{
    char cmd;
    print_startup();
    print_menu();

    while (1) {     
        cmd = get_cmd();
        parse_cmd(cmd);
        printf("\n");
    }

    return 0;
}


/*

+ ROP challenge featuring sweaty skid
+ We just pulled this 'malwear' off the kids 
   github, he hardly knows python so this should be
   a beezee 
+ See if you can find a flaw in it

+ compile

`gcc -fno-stack-protector -no-pie -z norelro -m32 -g skid.c -o skid`
*/