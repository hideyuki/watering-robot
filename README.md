# 水やってロボット
- 諸事情で、「全自動水やりロボット」から「”水やって“と言ってくれるロボット」に変更となりました。
- 人が水をやらないといけない。
- ロボットにとってはヒトもシステムの一部なのです。


## 3D CAD
- 湿度センサをむき出しにしていると怖いのでケースを作りました。
- 3d-cad ディレクトリに Autodesk Inventor 2014 形式(ipt) と STL 形式が入っています。

## Arduino
- 湿度センサのアナログ値をシリアルでRaspberryPiに送ります。
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

