from matplotlib import pyplot as plt
from numpy.lib.index_tricks import index_exp
import numpy as np
from matplotlib import cm as CM

def plot(data, timeLength, frequencyLength, startF, endF):
    fig = plt.figure(figsize=(20,8),dpi=80)

    plt.ion()
    print("data:::::::")
    print(data)
   
    print("timelength:::::::::")
    print(timeLength)

    print("frequencylength:::::::::")
    print(frequencyLength)
    print("start:::::::::")
    print(startF)
    print("end:::::::::")
    print(endF)
    heatmap_dataArray = np.zeros((timeLength,frequencyLength))

    rows = timeLength - 1 

    for i in range(timeLength):
        plt.cla()
        # x_axis = []
        # delta = (endF - startF) / frequencyLength
        # #有时会跨度不够会自动取0
        # for i in range(frequencyLength):
            
        #     temp = startF + i * delta
        #     x_axis.append(temp)
        # x_axis = np.linspace(2,14,2)
        x_axis = np.linspace(startF, endF, frequencyLength)

        # print("startF, endF, int(divide)")
        # print((startF - endF)/delta )
        # x = range(2,38,3)
        heatmap_dataArray[rows] = data[rows]
        
        # print(heatmap_dataArray)
        imag1 = plt.subplot(211)
        imag2 = plt.subplot(212)  
        
        plt.sca(imag1)
        cmap = CM.get_cmap('nipy_spectral', 50)

        imag1.set_xticklabels(['','','','','',''],rotation = 30,fontsize = 'small' )
        map = plt.imshow(heatmap_dataArray, interpolation="nearest", cmap=cmap,aspect='auto', vmin=10,vmax=40)
       
        cb1 = plt.colorbar(mappable=map, cax=None, ax=imag1,shrink=1)
        cb1.set_label('(%)')

        cb2 = plt.colorbar(mappable=map, cax=None, ax=imag2,shrink=0)
       

        


        plt.sca(imag2)
       
        plt.plot(x_axis,heatmap_dataArray[rows])
        plt.pause(1)
        rows = rows - 1

    plt.ioff()
    plt.show()

def plot1(data, timeLength, frequencyLength, startF, endF):
    fig = plt.figure(figsize=(20,8),dpi=80)

    plt.ion()
    #plt两种模式
    #默认是阻塞模式，程序会卡在plt.show()函数中，在plt.plot()之后必须接plt.show()才可出图
    #ion()开启交互模式，只需plot()即可出图，不必show()
    heatmap_dataArray = np.zeros((30,12))

    rows = 29

    for i in range(100):
        plt.cla()
        x = range(2,38,3)
        heatmap_dataArray[rows] = [15,13,14.5,17,20 + i * 10,  25,26,26 + i  * 1000,27,22,18,15]
        print(heatmap_dataArray)


        # ax1 = fig.add_subplot(2,1,1,position=[0.1,0.15,0.9,0.8])
        imag1 = plt.subplot(211)
        
        imag2 = plt.subplot(212)  
        
        
        # imag1 = fig.add_subplot(2,1,1)
        # imag2 = fig.add_subplot(2,1,2)
        #注意标记旋转的角度
        # ax1.set_xticklabels(['','A','B','C','D','E'],rotation = 30,fontsize = 'small' )

        # select the color map
        #可以有多种选择，这里我最终选择的是spectral，那个1000是热度标尺被分隔成多少块，数字越多，颜色区分越细致。
        #cmap = CM.get_cmap('RdYlBu_r', 1000)
        #cmap = CM.get_cmap('rainbow', 1000)
        plt.sca(imag1)
        cmap = CM.get_cmap('summer', 10000)

        # map the colors/shades to your data
        #那个vmin和vmax是数据矩阵中的最大和最小值。这个范围要与数据的范围相协调。
        #那个aspect参数，对确定图形在整个图中的位置和大小有关系。上面的add_subplot中的position参数的数值要想有作用，这里的这个参数一定要选auto。
        map = plt.imshow(heatmap_dataArray, interpolation="nearest", cmap=cmap,aspect='auto', vmin=0,vmax=10000)
        #shrink是标尺缩小的比例
        #plt.sca(cb)
        cb1 = plt.colorbar(mappable=map, cax=None, ax=imag1,shrink=1)
        cb1.set_label('(%)')

        cb2 = plt.colorbar(mappable=map, cax=None, ax=imag2,shrink=1)
        cb2.set_label('(%)')
        
        

        plt.sca(imag2)
        # imag2.axis(True)
        plt.plot(heatmap_dataArray[rows])
        plt.pause(0.1)
        rows = rows - 1

    plt.ioff()
    plt.show()

