# brainmelt 仕様書
## 概要
brainmeltは、brainf*ckをベースに開発した難解プログラミング言語です。

命令数が二倍になっています。

## 命令一覧
- `@`:現在のアドレスの値を出力する
- `$`:現在のアドレスに標準入力を1Byteずつ入力する
- `+`:メモリアドレスの値を1増やす
- `-`:メモリアドレスの値を1減らす
- `*`:アドレスの値を1回左にシフトする
- `/`:アドレスの値を1回右にシフトする
- `?`:アドレスの値を一個前のアドレスの値で割ったあまりにする
- `>`:アドレス位置を1増やす
- `<`:アドレス位置を1減らす
- `#`:無条件ジャンプ
- `[`:0に等しかったら対応する`]`のあとまで移動
- `]`:対応する`[`のあとまで移動
- `^`:今のアドレスの値を一個前のアドレスの値とANDした結果にする
- `%`:今のアドレスの値を一個前のアドレスの値とORした結果にする
- `!`:今のアドレスの値をNOTする
- `=`:プログラムの終了を表す
