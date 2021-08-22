#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Argument struct:

    - Example argument foramt:
        -arg, --argument

    @arg_count:
        + The number of arguments
          the argument expects.
    @quick_tack:
        + argument short form
    @full_tack:
        + argument long form
    @help
        + argument help info
*/
struct arg {
    int arg_count;
    char * quick_tack;
    char * full_tack;
    char * help;
};


/* parse arguments into struct */
struct arg new_arg() {

    struct arg new_argument;

    int arg_count;
    char short_form[6];
    char long_form[15];
    char help[42];

    char quick_tack[10] = "-";
    char full_tack[15] = "--";


    printf("Enter expected argument no: ");
    scanf("%d", &arg_count);
    getchar();

    if (arg_count <= 0 || arg_count > 3) {
        printf("Invalid argument count.\n");
        exit(1);
    }

    printf("Enter argument short form: ");
    fgets(short_form, 6, stdin);
    printf("Enter argument long form: ");
    fgets(long_form, 15, stdin);
    printf("Enter argument help info: ");
    fgets(help, 42, stdin);

    short_form[strlen(short_form) - 1] = '\0';
    long_form[strlen(long_form) - 1] = '\0';
    help[strlen(help) - 1] = '\0';  

    strcat(quick_tack, short_form);
    strcat(full_tack, long_form);

    new_argument.arg_count = arg_count;
    new_argument.quick_tack = quick_tack;
    new_argument.full_tack = full_tack;
    new_argument.help = help;
    
    printf("\nGenerated new argument:\n\n");
    printf("    %s, %s, [%d]        %s", new_argument.quick_tack, 
                                    new_argument.full_tack, 
                                    new_argument.arg_count, 
                                    new_argument.help
    );
    printf("\n");


    return new_argument;
}

int 
main(int argc, char const *argv[])
{
    /* parse arguments */
    struct arg argument = new_arg();

    return 0;
}
