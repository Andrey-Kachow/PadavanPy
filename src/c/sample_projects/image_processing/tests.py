
#ppm viewer
#https://jumpshare.com/viewer/ppm

def write_int(img, size, value):
	for _ in range(size):
		b = value % 256
		value //= 256
		img.write(chr(b).encode('utf-8'))

def write_rgbax87953(img, r, g, b, a):
	value = a * 2**5 + (g)

with open('kek.ppm', 'wt') as img:
	img.write("P3\n")
	img.write("50 50\n255\n")
	for i in range(50 * 50):
		img.write("255 0 255 \n")

## BMP
# with open('kek.bmp', 'wb') as img:

# 	bits_per_px = 24
# 	img_w = 50
# 	img_h = 50
# 	rowsize = (bits_per_px * img_w + 31) // 32 * 4
# 	pad_size = (rowsize - img_w * 3)
# 	px_arr_size = rowsize * img_h

# 	# BMP header	
# 	img.write('BM'.encode('utf-8'))
# 	write_int(img, 4, px_arr_size + 54)
# 	write_int(img, 2, 0)
# 	write_int(img, 2, 0)
# 	write_int(img, 4, 54)

# 	# DIB header BITMAPINFOHEADER
# 	write_int(img, 4, 40)
# 	write_int(img, 4, img_w)
# 	write_int(img, 4, img_h)
# 	write_int(img, 2, 1)
# 	write_int(img, 2, bits_per_px)
# 	write_int(img, 4, 0)
# 	write_int(img, 4, px_arr_size)
# 	write_int(img, 4, 2835)
# 	write_int(img, 4, 2835)
# 	write_int(img, 4, 0)
# 	write_int(img, 4, 0)
	

# 	# pixels
# 	for row in range(img_h):
# 		for col in range(img_w):
# 			write_int(img, 1, 0)
# 			write_int(img, 1, 0)
# 			write_int(img, 1, 255)
# 			print("rgb")
# 		for col in range(pad_size):
# 			print("pad")
# 			write_int(img, 1, 0)

