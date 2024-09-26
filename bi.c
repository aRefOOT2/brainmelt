/*

brainmelt interpriter
Version 1.0.1

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

#define MEMORY_SIZE 30000

int memory[MEMORY_SIZE] = {0};
int *ptr = memory; // 現在のメモリポインタ
FILE *file;

void help() 
{

    printf("brainmelt HELP\n");
    printf("usage:\n");
    printf("bi [input.bms]\n");
    printf("\nbrainmelt interpriter version 1.0.1\n");

}

int main(int argc, char* argv[])
{

    if (argc < 2)
    {
    
        help();
        return 0;
    
    }

    file = fopen(argv[1], "r");
    if (!file)
    {
    
        printf("failed open file.\n");
        return 1;
    
    }

    int chr;
    while ((chr = fgetc(file)) != EOF)
    {
    
        switch (chr)
        {
        
            case '@':
                putchar(*ptr);
                break;
            case '$':
                *ptr = getchar();
                break;
            case '+':
                (*ptr)++;
                break;
            case '-':
                (*ptr)--;
                break;
            case '*':
                *ptr <<= 1; // 左シフト
                break;
            case '/':
                *ptr >>= 1; // 右シフト
                break;
            case '?':
                *ptr = *ptr % *(ptr - 1);
                break;
            case '>':
                ptr++;
                if (ptr >= memory + MEMORY_SIZE) ptr = memory; // メモリ範囲のラップ
                break;
            case '<':
                ptr--;
                if (ptr < memory) ptr = memory + MEMORY_SIZE - 1; // メモリ範囲のラップ
                break;
            case '#':
                // 無条件ジャンプ処理
                ptr = memory + *ptr;
                break;
            case '[':
                if (*ptr == 0)
                {
                
                    // 対応する']'までスキップ
                    int loop = 1;
                    while (loop > 0)
                    {
                    
                        chr = fgetc(file);
                        if (chr == '[') loop++;
                        else if (chr == ']') loop--;
                    
                    }
                
                }
                break;
            case ']':
                if (*ptr != 0)
                {
                
                    // 対応する'['まで戻る
                    int loop = 1;
                    while (loop > 0)
                    {
                    
                        fseek(file, -2, SEEK_CUR); // 1文字戻る
                        chr = fgetc(file);
                        if (chr == ']') loop++;
                        else if (chr == '[') loop--;
                    
                    }
                
                }
                break;
            case '^':
                *ptr = *ptr & *(ptr - 1);
                break;
            case '%':
                *ptr = *ptr | *(ptr - 1);
                break;
            case '!':
                *ptr = ~(*ptr);
                break;
            case '=':
                fclose(file);
                return 0;
        
        }

    }

    fclose(file);
    return 0;

}
