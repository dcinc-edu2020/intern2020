# 開発環境

## ビルド用PCへ接続し、プログラムや設計書を編集する
1. スタートメニューを開き、「リモートデスクトップ接続」と検索して開く。  
  ![リモートデスクトップ接続](img/remote.png)
1. チームごとに、以下コンピュータに対して接続する。  
    |チーム|コンピューター|
    |-|-|
    |1|20.48.93.210|
    |2|20.48.93.171|
    |3|20.194.232.49|
1. 以下ユーザー名とパスワードでログインする。  
    |チーム|ユーザー名|パスワード|
    |-|-|-|
    |1|intern1\user1|user1|
    |2|intern2\user2|user2|
    |3|intern3\user3|user3|
* ここからはチームメンバに画面共有して進めましょう。
1. デスクトップにある「インターン」のリンクを開く。  
    |格納ファイルフォルダ名|内容|
    |-|-|
    |Z:\Internship_program|マイクロマウス用プログラム|
    |Z:\設計書\MicroMouse.iproj|マイクロマウス用プログラムの設計書|
    |Z:\マイクロマウス開発手順書.pdf|プログラムのビルド手順書|
1.「マイクロマウス開発手順書.pdf」を開く
1. 手順書を参考に、p7まで実施できることを確認し、プログラム開発に入る。
* (参考)PCには以下ツールが入っています。
  * マイクロマウス用コンパイラ(CS+)・・・マイクロマウス用プログラムのコンパイラ
  * 次世代設計ツール NextDesign (デンソークリエイト製ツール！)・・・設計書のエディタ

## ビルド用PC以外からプログラムや設計書を参照する(読み取り専用)
* 設計書
  * https://dcinc-edu2020.github.io/intern2020/doc/design/index.html

* ベースコード
  * https://github.com/dcinc-edu2020/intern2020/tree/master/program

* ベースコード(ブラウザ上でIDEっぽく見る)
  1. 以下URLにアクセス  
    http://xxx
  1. 「Join the Live Share session from the browser (preview)」をクリック  
    ※VisualStudio+LiveShareがインストールしてある人はそちらで開いてもOK  
    ![Join](img/live_share_join.png)
  1. 画面右下に出る「Continue as anonymous」をクリック  
    ![Continue as anonymous](img/continue_anonymous.png)
  1. 適宜ユーザ名(Guset UserのままでもOK)を入れてEnterキー  
    ![Username](img/user_name.png)
