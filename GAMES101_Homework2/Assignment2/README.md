# 已完成项目
- [5 分] 正确地提交所有必须的文件，且代码能够编译运行。
- [20 分] 正确实现三角形栅格化算法。
- [10 分] 正确测试点是否在三角形内。
- [10 分] 正确实现 z-buffer 算法, 将三角形按顺序画在屏幕上。
- [提高项 5 分] 用 super-sampling 处理 Anti-aliasing。

# 其他
- 修改hard-coded三角形的颜色参数，测试代码对颜色的插值：完成
- (update) 按照 `Zn = -Znear, Zf = -Zfar` 重新计算了投影矩阵，修复了画面视角不正确的问题。并导出了 `MSAA_colorful_projectionFIXED.png` 。