#include <stdio.h>
#include <stdarg.h>

#define NUMBER -666.7
#define CHAR 'k'
#define STRING "wzk"
#define FORMAT "The greatest person is: %s %010.6ld byebye!"

int PrintChar(char *, char, int, int);
int PrintString(char *, char *, int, int);
int PrintNum(char *, unsigned long, int, int, int, int, char, int);

void output(char* buf, int length) {
    for (int i = 0; i < length; i++) {
        printf("%c",*buf);
        buf++;
    }
}

int main(){
    char *fmt = FORMAT;
    char c;
    char *s;
    long int num;
    int longFlag;
    int negFlag;
    int width=0;
    int prec=0;
    int ladjust;
    char padc;
    char buf[50];
    int length;
    int bufcount=0;

    for (;*fmt != '\0';) {
        /* Part1: your code here */
        for (;;fmt++){
            /* scan for the next '%' */
            /* flush the string found so far */
            /* check "are we hitting the end?" */
            if (*fmt == '%'){
                for (int i = 0; i < bufcount; i++) {
                    printf("%c",buf[i]);
                }
                bufcount=0;
                fmt++;
                break;
            } else if (*fmt == '\0') {
                for (int i = 0; i < bufcount; i++) {
                    printf("%c",buf[i]);
                }
                break;
            } else {
                buf[bufcount++] = *fmt;

            }
        }
        /* we found a '%' */
        /* check for long */
        if (*fmt == '-') {
            ladjust = 1;
            fmt++;
        } else
            ladjust = 0;
        if (*fmt == '0') {
            padc = '0';
            fmt++;
        } else {
            padc = ' ';
        }
        while (*fmt >= '0' && *fmt <= '9') {
            width = 10*width + *fmt - '0';
            fmt++;
        }
        if (*fmt == '.') {
            fmt++;
            while (*fmt >= '0' && *fmt <= '9') {
                prec = 10*prec + *fmt - '0';
                fmt++;
            }
        }
        if (*fmt == 'l') {
            longFlag=1;
            fmt++;
        } else
            longFlag=0;
        /* check for other prefixes */

        /* check format flag */

        negFlag = 0;
        switch (*fmt) {
            case 'b':
                if (longFlag) {
                    num = NUMBER;
                } else {
                    num = NUMBER;
                }
                length = PrintNum(buf, num, 2, 0, width, ladjust, padc, 0);
                output(buf,length);
                break;

            case 'd':
            case 'D':
                if (longFlag) {
                    num = NUMBER;
                } else {
                    num = NUMBER;
                }
                if (num < 0) {
                    negFlag=1;
                    num = -num;
                }
                length = PrintNum(buf, num, 10, negFlag, width, ladjust, padc, 0);
                output(buf,length);
                /*  Part2:
                        your code here.
                        Refer to other part (case 'b',case 'o' etc.) and func PrintNum to complete this part.
                        Think the difference between case 'd' and others. (hint: negFlag).
                */
                break;

            case 'o':
            case 'O':
                if (longFlag) {
                    num = NUMBER;
                } else {
                    num = NUMBER;
                }
                length = PrintNum(buf, num, 8, 0, width, ladjust, padc, 0);
                output(buf,length);
                break;

            case 'u':
            case 'U':
                if (longFlag) {
                    num = NUMBER;
                } else {
                    num = NUMBER;
                }
                length = PrintNum(buf, num, 10, 0, width, ladjust, padc, 0);
                output(buf,length);
                break;

            case 'x':
                if (longFlag) {
                    num = NUMBER;
                } else {
                    num = NUMBER;
                }
                length = PrintNum(buf, num, 16, 0, width, ladjust, padc, 0);
                output(buf,length);
                break;

            case 'X':
                if (longFlag) {
                    num = NUMBER;
                } else {
                    num = NUMBER;
                }
                length = PrintNum(buf, num, 16, 0, width, ladjust, padc, 1);
                output(buf,length);
                break;

            case 'c':
                c = CHAR;
                length = PrintChar(buf, c, width, ladjust);
                output(buf,length);
                break;

            case 's':
                s = STRING;
                length = PrintString(buf, s, width, ladjust);
                output(buf,length);
                break;

            case '\0':
                fmt --;
                break;

            default:
                /* output this char as it is */
                output(buf,length);
        }       /* switch (*fmt) */

        fmt ++;
    }
    printf("\nlongFlag: %d\n",longFlag);
    printf("negFlag: %d\n",negFlag);
    printf("width: %d\n",width);
    printf("prec: %d\n",prec);
    printf("ladjust: %d\n",ladjust);
    printf("padc: '%c'\n",padc);
}



/* --------------- local help functions --------------------- */
int PrintChar(char * buf, char c, int length, int ladjust)
{
    int i;

    if (length < 1) length = 1;
    if (ladjust) {
        *buf = c;
        for (i=1; i< length; i++) buf[i] = ' ';
    } else {
        for (i=0; i< length-1; i++) buf[i] = ' ';
        buf[length - 1] = c;
    }
    return length;
}

int PrintString(char * buf, char* s, int length, int ladjust)
{
    int i;
    int len=0;
    char* s1 = s;
    while (*s1++) len++;
    if (length < len) length = len;

    if (ladjust) {
        for (i=0; i< len; i++) buf[i] = s[i];
        for (i=len; i< length; i++) buf[i] = ' ';
    } else {
        for (i=0; i< length-len; i++) buf[i] = ' ';
        for (i=length-len; i < length; i++) buf[i] = s[i-length+len];
    }
    return length;
}

int PrintNum(char * buf, unsigned long u, int base, int negFlag,
             int length, int ladjust, char padc, int upcase)
{
    /* algorithm :
     *  1. prints the number from left to right in reverse form.
     *  2. fill the remaining spaces with padc if length is longer than
     *     the actual length
     *     TRICKY : if left adjusted, no "0" padding.
     *              if negtive, insert  "0" padding between "0" and number.
     *  3. if (!ladjust) we reverse the whole string including paddings
     *  4. otherwise we only reverse the actual string representing the num.
     */

    int actualLength =0;
    char *p = buf;
    int i;

    do {
        int tmp = u %base;
        if (tmp <= 9) {
            *p++ = '0' + tmp;
        } else if (upcase) {
            *p++ = 'A' + tmp - 10;
        } else {
            *p++ = 'a' + tmp - 10;
        }
        u /= base;
    } while (u != 0);

    if (negFlag) {
        *p++ = '-';
    }

    /* figure out actual length and adjust the maximum length */
    actualLength = p - buf;
    if (length < actualLength) length = actualLength;

    /* add padding */
    if (ladjust) {
        padc = ' ';
    }
    if (negFlag && !ladjust && (padc == '0')) {
        for (i = actualLength-1; i< length-1; i++) buf[i] = padc;
        buf[length -1] = '-';
    } else {
        for (i = actualLength; i< length; i++) buf[i] = padc;
    }


    /* prepare to reverse the string */
    {
        int begin = 0;
        int end;
        if (ladjust) {
            end = actualLength - 1;
        } else {
            end = length -1;
        }

        while (end > begin) {
            char tmp = buf[begin];
            buf[begin] = buf[end];
            buf[end] = tmp;
            begin ++;
            end --;
        }
    }

    /* adjust the string pointer */
    return length;
}