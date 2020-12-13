[![Code Quality Score](https://www.code-inspector.com/project/12/score/svg)](https://www.code-inspector.com/public/project/12/POK/dashboard)
[![Code Grade](https://www.code-inspector.com/project/12/status/svg)](https://www.code-inspector.com/public/project/12/POK/dashboard)
[![Build status](https://travis-ci.org/pok-kernel/pok.svg?master)](https://travis-ci.org/pok-kernel)

POK
===

POK kernel, a secure and safe micro-kernel for embedded systems.

More information on https://pok-kernel.github.io/

For commercial support: http://www.reblochon.io.

Contact: pok at gunnm dot org


## 个人笔记

### 获取时间
如果想要在用户程序（即 `examples` 下面的代码）中使用 `pok_time_get` 获取时间，那么要在 `deployment.h` 中定义：
```c
#define POK_NEEDS_GETTICK 1
```

恕我直（tu）言（cao），这个代码的宏定义设计太反人类的。