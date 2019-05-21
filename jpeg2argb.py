#!/usr/bin/env python2
import struct
from PIL import Image

TYPE_ARGB = 1
TYPE_ABGR = 2
TYPE_BGRA = 3 #ubuntu
TYPE_RGBA = 4


re_w=800
re_h=600
pic_file = r'test.jpg'
color_type = TYPE_BGRA


out_pic = pic_file+"_%d_%d.jpeg"%(re_w,re_h)
out_pic_fb = out_pic+".fb"

def img_resize(file_r,file_w,w,h):
	im = Image.open(file_r)
	im = im.resize((w, h), Image.ANTIALIAS)
	im.save(file_w)

def img_tofb_data(file_r,file_w,col_type,alpha):
	im = Image.open(file_r)
	w, h = im.size
	with open(file_w, 'wb') as f:
		for j in range(0, h):
			for i in range(0, w):
				r, g, b = im.getpixel((i, j))
				if col_type == TYPE_ARGB:
					argb = struct.pack('BBBB', alpha, r, g, b)
				elif col_type == TYPE_ABGR:
					argb = struct.pack('BBBB', alpha, b, g, r)
				elif col_type == TYPE_BGRA:
					argb = struct.pack('BBBB', b, g, r, alpha)
				elif col_type == TYPE_RGBA:
					argb = struct.pack('BBBB', r, g, b, alpha)
				f.write(argb)

img_resize(pic_file,out_pic,re_w,re_h)
img_tofb_data(out_pic,out_pic_fb,color_type,255)