# sdl贪吃蛇

## 简介
最初这是我在 2021/8/29写的，其实就是一个简单到不能在简单的贪吃蛇

~~也是我第一个用c写超过300行代码的项目(bushi)~~

现在被我翻出来重写，当时用的是 csfml (sfml 的c语言绑定)，重写改时换用 sdl ，

忘记当初写这个的目的了，应是在学校里跟同学，聊到的时候突然聊到这个话题来着

隐约记得网上找过一些代码复制下来，很惭愧，没有留下出处，已经不知道来源了

所以其实也不算完全是我写的

现在这次重写中蛇的蛇体从原来的数组
改成了列表(linked list)参考了 c prime plus 第六版573页的代码，~~然后这个指针我修了一整天~~ 

感觉又有了当初的干劲 ~~虽然写的像屎一样~~

## 参考
c prime plus --Stephen Prata

sdl 的教程
https://www.willusher.io/pages/sdl2/

SDL实现限制帧速
http://www.caotama.com/2147054.html

SDL 开发实战（四）： SDL 事件处理
https://www.likecs.com/show-305723847.html

SDL 开发实战（三）：使用 SDL 绘制基本图形
https://www.cnblogs.com/renhui/p/10460512.html

不一定是原作者发表，仅为个人浏览过

最后感谢当初我复制的那个源作者

以及所有互联网上的无私创作者们