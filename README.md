# 水やりロボット 改め、「水やって！」というロボット #brhack
- Jun. 14, 2914: Beatrobo ハードウェアハッカソン で作ったものです。
   - [http://beatrobo.doorkeeper.jp/events/12214](http://beatrobo.doorkeeper.jp/events/12214)
   - [https://www.facebook.com/hashtag/brhack](https://www.facebook.com/hashtag/brhack)
- 私の作るものは「全自動水やりロボット」から「”水やって“と言ってくれるロボット」に変更となりました！

- いいわけ
   - 人が水をやらないといけない。
   - ロボットにとってはヒトもシステムの一部なのです。
   - つまりは、ロボットがヒトを使って水やりを達成しております。


## 3D CAD
- 湿度センサをむき出しにしていると怖いのでケースを作りました。
- メインパーツと蓋パーツの2部品です。
- `3d-cad` ディレクトリに Autodesk Inventor 2014 形式(ipt) と STL 形式(単位: mm) が入っています。
- Sculpteo にもデータをアップロードしています: [メインパーツ](http://www.sculpteo.com/en/design/moisture-sensor-case-part-0/epgLNvjr), [蓋パーツ](http://www.sculpteo.com/en/design/moisture-sensor-case-part-1-2/ZrL73rzd)
   - そのままオンラインで注文できます。

## Arduino
- 利用しているボード: [SainSmart UNO R3 ATmega328-AU Development Board Compatible With Arduino UNO R3](http://www.sainsmart.com/featured-products/sainsmart-uno-r3-atmega328-au-development-board-compatible-with-arduino-uno-r3.html)
   - 普通のArduinoとは違い 3.3V zでの動作が可能。RaspberryPiと電圧変換なく接続できるようになります。 
   - [amazonから購入](http://www.amazon.co.jp/%E3%82%B5%E3%82%A4%E3%83%B3%E3%82%B9%E3%83%9E%E3%83%BC%E3%83%88%EF%BC%88SainSmart%EF%BC%89UNO-R3-ATmega328P%E6%90%AD%E8%BC%89%EF%BC%81-UNO-Duemilanove/dp/B00BPISRWE/ref=sr_1_1?ie=UTF8&qid=1402799424&sr=8-1&keywords=SainSmart+UNO+R3)できます。￥1,990 (2014年6月15日現在) 
   - マニュアルは[こちら](http://www.sainsmart.com/zen/documents/20-011-937/SainSmart-UNO-R3.pdf)
- シリアル経由で送られてくるコマンドにより、湿度センサ・温度センサのアナログ値をシリアルでraspberryPiに送ります
- コマンド一覧
   - m: Moisture。湿度センサのアナログ値を返す
   - t: Temperature。温度センサのアナログ値を返す
- 湿度センサは [http://akizukidenshi.com/catalog/g/gM-07047/](http://akizukidenshi.com/catalog/g/gM-07047/)
- シリアルの通信速度は 57600 bps
- screenでシリアル通信するコマンド

```
$ screen /dev/tty.usbmodem1411 57600
```
   - screenの終了は [Ctrl+a, k]

- 湿度センサのレンジ 参照元: [http://www.dfrobot.com/wiki/index.php?title=Moisture_Sensor_(SKU:SEN0114)](http://www.dfrobot.com/wiki/index.php?title=Moisture_Sensor_(SKU:SEN0114))
   - 0 ~300 : dry soil
   - 300~700 : humid soil
   - 700~950 : in water

## RaspberryPi (Model A)
- Arduinoから温湿度のアナログ値を取得したらhubotのHTTP APIに投げる
- Raspbian with 4GB SD Card
- 無線LANでネットワークに接続
   - USBタイプの無線LANドングル [GW-USNANO2A](http://www.amazon.co.jp/%E3%80%90Amazon-co-jp%E9%99%90%E5%AE%9A%E3%80%91PLANEX-%E7%84%A1%E7%B7%9ALAN%E5%AD%90%E6%A9%9F-USB%E3%82%A2%E3%83%80%E3%83%97%E3%82%BF%E3%83%BC%E5%9E%8B-150Mbps-GW-USNANO2A/dp/B00ESA34GA/ref=sr_1_2?ie=UTF8&qid=1402773295&sr=8-2&keywords=%E7%84%A1%E7%B7%9Alan+usb) を利用
   - 無線LANのつなげるためのコマンドは以下
   
```
# vi /etc/network/interfaces
iface wlan0 inet dhcp
wpa-conf /etc/wpa_supplicant/wpa_supplicant.conf
```

```
# wpa_passphrase ESSID PASSWORD >> /etc/wpa_supplicant/wpa_supplicant.conf
```

```
# ifdown wlan0
# ifup wlan0
```

- IPを知らなくても外部からSSHできるように avahi-daemon をインストール

```
# apt-get update
# apt-get install avahi-daemon
```

- ホスト名が最初は `raspberrypi` なので、`watering` に変更しておく

```
# vi /etc/hostname
watering
# vi /etc/hosts
127.0.1.1       watering
```

- そうすると、外部から以下のコマンドでsshできる

```
hide@mac$ ssh pi@watering.local
```

	