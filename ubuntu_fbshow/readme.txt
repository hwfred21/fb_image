steps to run on ubuntu
vbox add 1

1��ubuntu ��װfbset
sudo apt-get install fbset

�鿴��Ϣ��
fbset -s
mode "800x600"
    geometry 800 600 800 600 32
    timings 0 0 0 0 0 0 0
    accel true
    rgba 8/16,8/8,8/0,0/0
endmode

��֪��
b[0-7]
g[8-15]
r[16-23]

2��gcc fb_show.c

./a.out test1.fb

3,��ʾͼƬ�������л�������PC���棿
ctrl+alt+f7 �л���
