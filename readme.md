

# 整体配置步骤

1. qt:5.15.2_msvc2019_64  
2. python 3.9.7 + matplotlib + numpy
2. vs2019
4. 下载qt并关联vs2019
5. 修改配置页
## qt下载 与 链接
+ 在线下载
+ vs2019 下载插件并链接 若无法打开插件 则需**更新vs2019**（使用下载器更新）
+ qt需要加入环境变量
+ （有可能需要） 工具->外部工具 添加uic工具

## 修改配置页

### 附加包含目录
1. python 3.9/include 
2. fftw  
3. fftw-3.3.5-dll64  

### 附加库目录 附加依赖项
1. python 3.9/libs  
2. fftw
3. fftw-3.3.5-dll64

### 导入dll系统文件WOW64
libfftw3-3.dll 导入到 C:\Windows\System32

### 调试环境
debug x64

# 使用
## 带宽检测（index = 0）
48板卡

## 信号检测页面： （index = 1）
47号板卡

## 任意信号生成 
48号板卡
## 混叠 （index = 1 ）

## 相参信号生成
48号板卡

循环次数上下scroll：spinbox_6    按钮: pushButton_20

  label_131   label_134


## 信号调制方式识别 （index= 3）
47板卡
调制方式识别 ：47

## LTE 

47号板卡


