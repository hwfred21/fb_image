# -*- coding: UTF-8 -*-
from PIL import Image

# different form .png an .gif , .jpeg has no alpha channel
def addTransparency(img, factor=0.7):
	img = img.convert('RGBA')
	img_blender = Image.new('RGBA', img.size, (0, 0, 0, 0))
	img = Image.blend(img_blender, img, factor)
	return img

pic_file=r'test.jpg '
img = Image.open(pic_file)
img = addTransparency(img, factor=0.7)
img.save(pic_file+"_out.png")

