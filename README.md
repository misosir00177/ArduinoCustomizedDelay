# ArduinoCustomizedDelay
## [EN-US]English Section
This project is aimed to be alternative of delay() function in Arduino by using millis() function and some condition.

keyword: arduino, delay ,millis(), millisec, millisecond

Sample Usage file can be downloaded here ![Static Badge](https://img.shields.io/badge/SampleUsage-v4.10.16.0-yellow?link=https%3A%2F%2Fgithub.com%2Fmisosir00177%2FArduinoCustomizedDelay%2Freleases%2Ftag%2Fv4.10.16.0)

Here is Template of Customized Delay Function for Quickly Copy Paste Using.  
```cpp
unsigned int savedAt = 0;
unsigned int previousMillis;

//Main delay function
bool waitForMillis(int dur) {
  if (savedAt == 0) {
    savedAt = millis();
  } else if (savedAt != 0) {
    previousMillis = millis();
    if (previousMillis - savedAt >= dur) {
      savedAt = 0;
      return true;
    } else {
      return false;
    }
  }
}
```

Here is Flowchart for this Template:

## [JA-JP]日本語説明区域
### 日本語でこの関数のロジックと性質を解説します。  
該当関数の使用をLoop()内での繰り返し実行を予定しています。  
繰り返しの呼び出しで時間が経過したか否かをチェックして、チェック結果を返してくれます(return: true/false)。  
図解は以下の通りです：  
<p align="center">
<img src="https://github.com/user-attachments/assets/b8259b47-d87a-4af7-9b2b-8048747be26d" width=50% height=50%>
</p>  

### 初期化と記録
初めて実行された場合、はじめて時間の計測を開始します。  
この計測開始時点のシステムの現在実行時間を内部(SavedAt変数に相当)に保存し、固定します。  

### 時間の経過チェックと返信
繰り返し呼び出すため、二回目以降の初めてではない呼び出しの場合、もう一度システムの現在実行の時間を取得し、内部に一時保存します(previous変数に相当)。  
この一時保存のデータ(previous変数に相当)は二回目以降の呼び出しごとに更新されるので、一回目の固定データとの時間差がだんだん開けていきます。  
ここで、事前に指定した「待ちたい秒数(ms)」とこの時間差を比較し、もし「待ちたい秒数(ms)」と相当する、もしくは「待ちたい秒数(ms)」より時間差が大きくなった時点で、このファンクションの機能は終了です(つまり待機完了)。  
待ちたい秒数以上たったら、「時間が経過した(true)」という旨のメッセージを呼び出し元に返信し、すべてを初期状態にリセットして、次回の呼び出しに備えます。  
この間、もし時間差が「待ちたい秒数(ms)」以下だった場合、呼び出し元には「まだです(false)」と返します。  

### 性質上の使用条件

性質上、このファンクションを使う場合、呼び出し元はこのファンクションの返信を記録して、条件でフィルタリングして対応を行う必要があります。
例えば、「まだです(false)」の場合forループのカウントを一時停滞される；「時間が経過した(true)」と返信が来た場合、forループのカウントを続行するなど(この例はLEDフェードで使用できます。)
