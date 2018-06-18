#!/usr/bin/python
# Just like the Shellhammer version except it saves the segmented file

import sys,os
import time
import numpy as np
from PIL import Image
import caffe
import glob

# argv[1] = path2input_dir
# argv[2] = path2output_dir

def main():
    files = [x.split('/')[-1] for x in glob.glob(argv[1] + "/*.jpg")]
    for f in files:
        predict(argv[1],f)

def predict(path,filename):
# load image, switch to BGR, subtract mean, and make dims C x H x W for Caffe
    im = Image.open(path+filename)
    in_ = np.array(im, dtype=np.float32)
    in_ = in_[:,:,::-1]
    #in_ -= np.array((104.00698793,116.66876762,122.67891434))
    in_ = in_.transpose((2,0,1))

# shape for input (data blob is N x C x H x W), set data
    net.blobs['data'].reshape(1, *in_.shape)
    net.blobs['data'].data[...] = in_

    tic = time.clock()
    net.forward()
    toc = time.clock()
    print(path + filename + ':' + str(toc-tic) + 'sec')
    out = net.blobs['score'].data[0].argmax(axis=0)
    out_8 = np.empty_like(out, dtype=np.uint8)
    np.copyto(out_8, out, casting='unsafe')
    img = Image.fromarray(out_8)
    filename = filename.rstrip('.jpg')
    filename = filename + ".png"
    if compose == 1:
        im = im.convert("RGBA")
        img = img.convert("RGBA")
        cols,rows = img.size
        for x in range(cols):
            for y in range(rows):
                if img.getpixel((x,y))[0] + img.getpixel((x,y))[1] + img.getpixel((x,y))[2] != 0:
                    img.putpixel((x,y),r_a)
                else:
                    img.putpixel((x,y),(0,0,0,0))

        result = Image.alpha_composite(im,img)
        result.save(argv[2]+"/"+filename)
    elif compose == -1:
        img = img.convert('L')
        img = img.point(lambda x: 255 if x>0 else 0)
        img.save(argv[2]+"/"+filename)
    else:
        gray = img.convert("L")
        gray.save(argv[2]+"/"+filename)

if __name__=='__main__':
    argv = sys.argv
    argv[1] = argv[1] + "/"
    caffe.set_mode_gpu()
    #SoccerField3D_Blur.fcn-8s-digits/deploy.prototxt
    #SoccerField3D_Blur.fcn-8s-digits/snapshot_iter_10010.caffemodel
    compose = -1
    deploy = "/mnt/Trancend2T/hdd/workspace/models/both/deploy.prototxt"
    model = "/mnt/Trancend2T/hdd/workspace/models/both/snapshot_iter_10000.caffemodel"
    net = caffe.Net(
            deploy,
            model,
            caffe.TEST
            )
    # color + alpha
    alpha = 200
    w_a = (255,255,255,alpha)
    k_a = (100,100,100,alpha)
    r_a = (255,0,0,alpha)
    g_a = (0,255,0,alpha)
    b_a = (0,0,255,alpha)
    main()
