/*

brainmelt interpriter
Version 1.0.0 Pre-Alpha

命令一覧：
```
@:現在のアドレスの値を出力する
$:現在のアドレスに標準入力を1Byteずつ入力する
+:メモリアドレスの値を1増やす
-:メモリアドレスの値を1減らす
*:アドレスの値を1回左にシフトする
/:アドレスの値を1回右にシフトする
?:アドレスの値を一個前のアドレスの値で割ったあまりにする
>:アドレス位置を1増やす
<:アドレス位置を1減らす
#:無条件ジャンプ
[:0に等しかったら対応する`]`のあとまで移動
]:対応する`[`のあとまで移動
^:今のアドレスの値を一個前のアドレスの値とANDした結果にする
%:今のアドレスの値を一個前のアドレスの値とORした結果にする
!:今のアドレスの値をNOTする
=:プログラムの終了を表す
```

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int chr;

int *add = 0;

int list[] = {};

FILE *file;

void help()
{
    
    printf("brainmelt HELP\n");
    printf("usage:\n");
    printf("    bi [input.bms]\n");
    printf("\nbrainmelt interpriter version 1.0.0 Pre-Alpha\n");

}

int main(int argc,char* argv[])
{
    
    printf("bi 1.0.0PA\nargc: %d\nargv[1]: %s\n",argc, argv[1]);

    if (argc == 1)
    {

        help();
        return 0;

    }

    file = fopen(argv[1], "r");

    if (file == NULL)
    {
        
        printf("failed open file.\n");
        return 1;

    }

    while(1)
    {
        printf("start\n");
        
        if (strcmp(fgetc(file), "@") == 0)
        {

            printf("at\n");
            putchar(*add);
        
        } else if (strcmp(fgetc(file), "$") == 0)
        {

            printf("$\n");
            *add=getchar();

        } else if (strcmp(fgetc(file), "+") == 0)
        {

            (*add)++;

        } else if (strcmp(fgetc(file), "-") == 0)
        {

            (*add)--;

        } else if (strcmp(fgetc(file), "*") == 0)
        {

            *add = (*add) * 2;

        } else if (strcmp(fgetc(file), "/") == 0)
        {

            *add = (*add) / 2;

        } else if (strcmp(fgetc(file), "?") == 0)
        {

            *add = *add % *(add - 1);

        } else if (strcmp(fgetc(file), ">") == 0)
        {

            add++;

        } else if (strcmp(fgetc(file), "<") == 0)
        {

            add--;

        } else if (chr == '#')
        {

            printf("#\n");
            add = *add;

        } else if (chr == '[')
        {

            printf("[\n");

        } else if (chr == ']')
        {

            printf("]\n");

        } else if (chr == '^')
        {

            printf("^\n");

        } else if (chr == '%')
        {

            printf("%%\n");

        } else if (chr == '!')
        {

            printf("!\n");

        } else if (chr == '=')
        {

            printf("end\n");
            return 0;

        }

    }

    fclose(file);

    return 0;

}