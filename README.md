Name
====

Overview

## Description


光の反射についてのメモ

ofLightで扱われる光には、次の４種類があり、
ディフェーズ(Diffuse)
アンビエント(Ambient)
エミッション(Emissive)
スペキュラ(Specular)

specularは中でも鏡のような反応を示す。
これによって、鏡に映った光を見せるなどといった効果が可能である。
しかし、鏡-光、鏡-カメラの中心点をそれぞれ結ぶ線は
本来であれば鏡の垂線と一致するはずであるが、

鏡に反射した光がカメラにどのように映るかは、理論通りの挙動を示さない。
鏡に反射された光の仮想的な位置に向かってカメラを向けた場合は、
カメラの中心に光が確認できるが、
カメラを別の方向に向けた場合、光は移動してしまう、
これは、カメラレンダリングの際に、光がどのように映るかを、
鏡-光 鏡-カメラの位置　の角度ではなく、
鏡-光 カメラの向く方向　の角度で決定しているからである。



## Demo

## VS. 

## Requirement

## Usage

## Install

## Contribution

## Licence

[MIT](https://github.com/tcnksm/tool/blob/master/LICENCE)

## Author

masaru mizuochi
