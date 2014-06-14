# 水やってロボット
- 諸事情で、「全自動水やりロボット」から「”水やって“と言ってくれるロボット」に変更となりました。
- 人が水をやらないといけない。
- ロボットにとってはヒトもシステムの一部なのです。


## 3D CAD
- 湿度センサをむき出しにしていると怖いのでケースを作りました。
- メインパーツと蓋パーツの2部品です。
- `3d-cad` ディレクトリに Autodesk Inventor 2014 形式(ipt) と STL 形式(単位: mm) が入っています。
- Sculpteo にもデータをアップロードしています: [メインパーツ](http://www.sculpteo.com/en/design/moisture-sensor-case-part-0/epgLNvjr), [蓋パーツ](http://www.sculpteo.com/en/design/moisture-sensor-case-part-1-2/ZrL73rzd)
   - そのままオンラインで注文できます。

## Arduino UNO
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

# RaspberryPi (Model A)
- Arduinoから温湿度のアナログ値を取得したらhubotのHTTP APIに投げる
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
$ ssh pi@watering.local
```

