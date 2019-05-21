steps to run on ubuntu
vbox add 1

1，ubuntu 安装fbset
sudo apt-get install fbset

查看信息：
fbset -s
mode "800x600"
    geometry 800 600 800 600 32
    timings 0 0 0 0 0 0 0
    accel true
    rgba 8/16,8/8,8/0,0/0
endmode

可知：
b[0-7]
g[8-15]
r[16-23]

2，gcc fb_show.c

./a.out test1.fb

3,显示图片，怎样切换正常的PC桌面？
ctrl+alt+f7 切回来
