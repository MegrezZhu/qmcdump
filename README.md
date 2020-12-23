# qmcdump

一个简单的QQ音乐解码（qmcflac/qmc0/qmc3 转 flac/mp3），仅为个人学习参考用。

## 12月23日更新

添加了对整个文件夹转换操作的支持。

## 构建

### 使用 make

已提供有 `makefile` 文件，`mac/Linux`环境下直接 `make` 或者 `make install` 即可。

### 其他方式

请直接使用源代码自行编译。

## 使用

```sh
Usage

  qmcdump <input_file_path> [output_file_path]
  qmcdump <input_directory> [output_directory]
```

默认输出路径为源文件夹。