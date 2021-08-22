/*

 _   _      _                      _         _    _ _   _____ _          
| \ | | ___| |___      _____  _ __| | __    / \  | | | |_   _| |__   ___ 
|  \| |/ _ \ __\ \ /\ / / _ \| '__| |/ /   / _ \ | | |   | | | '_ \ / _ \
| |\  |  __/ |_ \ V  V / (_) | |  |   <   / ___ \| | |   | | | | | |  __/
|_| \_|\___|\__| \_/\_/ \___/|_|  |_|\_\ /_/   \_\_|_|   |_| |_| |_|\___|
                                                                         
 _____ _     _                 
|_   _| |__ (_)_ __   __ _ ___ 
  | | | '_ \| | '_ \ / _` / __|
  | | | | | | | | | | (_| \__ \
  |_| |_| |_|_|_| |_|\__, |___/
                     |___/     

+ A simple ROP challenge with a focus on reversing
*/

#include <stdio.h>
#include <stdlib.h>

void print_banner(void);


void 
print_banner() 
{
    printf("\n");
    printf(" _   _    _  _____ _____  \n");
    printf("| \\ | |  / \\|_   _|_   _| \n");
    printf("|  \\| | / _ \\ | |   | |   \n");
    printf("| |\\  |/ ___ \\| |   | |   \n");
    printf("|_| \\_/_/   \\_\\_|   |_|   \n\n");
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n\n");

    printf(":::::::::::: [NetworkAllTheThings (NATT) | Now with more things] :::::::::::: \n\n");
}


void
menu()
{
    printf("(1) Network a coffee grinder\n");
    printf("(2) Network a kettle\n");
    printf("(3) Network a microwave\n");
    printf("(4) Network a toaster\n");
    printf("(5) Network a blender\n");
    printf("(6) Network a defuser\n");
    printf("(7) Network a washing machine running MIPS\n");
    printf("(8) Network a clock\n");
    printf("(9) Network a massarging recliner\n");
    printf("(10) Network a network\n");

    printf("\n");
}


/*
Vulnerable function

+ One of the devices will expose
  a buffer overflow vulnerability 
*/
void
network_device()
{

}


void
select_device()
{
    int device;
    printf("Enter your device (1-10): ");
    scanf("%d", &device);
    getchar(); // clear buffer

    switch (device) {
        case 1:
            break;
        default:
            printf("Somehow we don't support that device \n");
            exit(0);
            break;
    }
}







int main(int argc, char const *argv[])
{
    print_banner();
    menu();
    select_device();

    return 0;
}
