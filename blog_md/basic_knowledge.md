---
title: '数字图像基础'
date: 2020-02-18 20:44:55
tags: [图像处理]
published: true
hideInList: false
feature: 
isTop: false
---
一些关于数字图像处理的基本知识
<!-- more -->

# 基本概念
**单色光**：没有颜色的光，单色光的唯一属性是强度。
**灰度级**：单色光的强度，从黑到白的单色光的度量值范围。
**灰度图像**：用单色光来表示的图像。

一幅图像可以用一个矩阵来表示，矩阵中某点的值表示图像在该点的灰度级。
**空间域**：一幅数字图像的坐标张成的实平面部分。
**像素**：图像矩阵中的元素，也可以称之为图像单元或图像元素。

**噪声**：存在于图像数据中的不必要的或多余的干扰信息。
**对比度**：图像中最高和最低灰度级间的灰度差。
**饱和度**：指图像色彩的纯净程度。

**空间分辨率**：用来度量图像中可辨别的最小细节，，通常用单位距离的线对数或单位距离的点数（像素数）来衡量。
**dpi**：每英寸点数，通常作为单位距离点数的单位。
**灰度分辨率**：指灰度级中可分辨的最小变化，用于量化灰度的比特数。例如，通常说一幅被量化为256级的图像有8比特的灰度分辨率。

# 图像内插
&emsp;&emsp;内插是在诸如放大、收缩、旋转和几何校正等任务中广泛应用的基本工具，是一种基本的图像重取样方法，本质上，内插是用已知数据来估计未知位置的数值的处理。本文介绍的内插主要用于调整图像的大小（收缩和放大）。
## 最近邻内插
&emsp;&emsp;最近邻内插根据原图像和目标图像的尺寸，计算缩放的比例，然后根据缩放比例计算离目标像素最近的原像素，将该原像素作为目标像素。
&emsp;&emsp;假设原图像大小为$W_s \times H_s$，目标图像大小为$W_d \times H_d$，原图像在$(x0,y0)$位置处的像素表示为$f_s(x0,y0)$，则目标图像在$(x, y)$位置处的像素$f_d(x,y)$的计算公式如下：

$$f_d(x, y) = f_s(\lfloor \frac{W_s}{W_d} \times x + 0.5 \rfloor, \lfloor \frac{H_s}{H_d} \times y + 0.5 \rfloor)$$

&emsp;&emsp;上式中$\lfloor \frac{W_s}{W_d} \times x + 0.5 \rfloor$表示对$\frac{W_s}{W_d} \times x$四舍五入。
&emsp;&emsp;最近邻内插算法实现的图像缩放的原理很简单，但缺点是得到的图像效果不太好。[^最近邻内插]
[^最近邻内插]: 有关最近邻内插的内容参考了<https://www.cnblogs.com/skyfsm/p/7578302.html>

## 双线性内插
&emsp;&emsp;双线型内插利用了源图中虚拟点四周的四个真实存在的像素，来共同决定目标图中的一个像素，使用双线性内插的缩放效果比简单的最邻近内插要好很多。
计算方法：
&emsp;&emsp;假设原图像大小为$W_s \times H_s$，目标图像大小为$W_d \times H_d$，首先根据源图像和目标图像的尺寸比例，计算目标图像像素坐标$(x_d,y_d)$在原图像中浮点坐标$(x_f,y_f)$，计算公式如下：

$$x_f = \frac{W_s}{W_d} \times x_d$$

$$y_f = \frac{H_s}{H_d} \times y_d$$

&emsp;&emsp;接下来在原图像中寻找离浮点坐标$(x_f,y_f)$最近的四个像素点，分别是坐标为$(\lfloor x_f \rfloor,\lfloor y_f \rfloor)$，$(\lfloor x_f + 1 \rfloor,\lfloor y_f \rfloor)$，$(\lfloor x_f \rfloor,\lfloor y_f + 1 \rfloor)$，$(\lfloor x_f + 1 \rfloor,\lfloor y_f + 1 \rfloor)$的四个像素。根据这四个像素计算出浮点坐标的像素值，再将浮点坐标的像素值作为目标图像对应位置的像素值。浮点坐标的像素值的计算方法如下：
&emsp;&emsp;首先，在$x$方向上进行两次线性插值计算，计算出$(x_f,\lfloor y_f \rfloor)$和$(x_f,\lfloor y_f + 1 \rfloor)$处的像素值，计算公式如下，设原图中在点$(x,y)$处的像素值为$f_s(x,y)$

$$f_s(x_f,\lfloor y_f \rfloor) = (x_f - \lfloor x_f \rfloor) \times f_s(\lfloor x_f \rfloor,\lfloor y_f \rfloor) + (\lfloor x_f + 1 \rfloor - x_f) \times f_s(\lfloor x_f + 1 \rfloor,\lfloor y_f \rfloor$$

$$f_s(x_f,\lfloor y_f + 1 \rfloor) = (x_f - \lfloor x_f \rfloor) \times f_s(\lfloor x_f \rfloor,\lfloor y_f + 1 \rfloor) + (\lfloor x_f + 1 \rfloor - x_f) \times f_s(\lfloor x_f + 1 \rfloor,\lfloor y_f + 1 \rfloor$$

&emsp;&emsp;然后利用$f_s(x_f,\lfloor y_f \rfloor)$和$f_s(x_f,\lfloor y_f + 1 \rfloor)$在$y$方向上进行一次插值计算，得出$f_s(x_f,y_f)$，计算公式如下：

$$f_s(x_f,y_f) = (y_f - \lfloor y_f \rfloor) \times f_s(x_f,\lfloor y_f \rfloor) + (\lfloor y_f + 1\rfloor - y_f) \times f_s(x_f,\lfloor y_f + 1 \rfloor)$$

&emsp;&emsp;实际上，双线性内插是根据四个像素点与浮点坐标的距离来计算四个像素点的权重，然后将四个像素点的加权平均和作为浮点坐标的像素值。图片使用双线性内插的缩放效果要优于最邻近内插，但是计算量要比最邻近内插大一点。[^双线性内插]
[^双线性内插]: 有关双线性内插的内容参考了<https://www.cnblogs.com/yssongest/p/5303151.html>

## 双三次内插
&emsp;&emsp;双三次内插的原理于双线性内插相似，都是根据浮点坐标附近的像素来计算出浮点坐标的像素值，计算时也是根据与浮点坐标之间的距离来计算附近像素点的权重，最后根据附近像素点的权重和像素值取加权平均和。与双线性内插不同的是，双三次内插计算了浮点坐标附近的16个像素点，而双线性内插只计算了4个。
&emsp;&emsp;双三次内插的核心问题是，如何根据像素点与浮点坐标的距离计算权重，有关双三次内插的计算方法参考自<https://blog.csdn.net/qq_29058565/article/details/52769497>，我偷个懒，就不再详细解释了。
&emsp;&emsp;与前面两种内插方法相比，双三次内插在保存细节方面比双线性内插相对要好一些，但是计算量比前两种方法都要高一些，是商业图像编辑程序如Adobe Photoshap和Corel Photopaint的标准内插方法。[^双三次内插]
[^双三次内插]: 此处引用自冈萨雷斯的《数字图像处理》第三版第37页。

# 像素间的基本关系
## 相邻像素
&emsp;&emsp;**4邻域**：与像素相邻的四个水平和垂直的相邻像素，坐标为$(x,y)$的像素的4邻域坐标为$(x+1,y)、(x-1,y)、(x,y+1)、(x,y-1)$，像素点p的4邻域可以用$N_4(p)$表示。
&emsp;&emsp;**D邻域**：与像素相邻的四个对角相邻像素，坐标为$(x,y)$的像素的D邻域坐标为$(x-1,y-1)、(x-1,y+1)、(x+1,y-1)、(x+1,y+1)$，像素点p的4邻域可以用$N_D(p)$表示。
&emsp;&emsp;**8邻域**：由像素的4邻域和D邻域组成。像素点p的8邻域可以用$N_8(p)$表示。
&emsp;&emsp;位于图像边界的像素点的4邻域、D邻域和8邻域会落入图像的外部。

## 邻接性、连通性、区域和边界
	