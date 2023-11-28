# Data Link Layer
有UObject::GetOuter实现的数据链层, C++和蓝图的接口实现有所区别但可进行联动

## 问题
* 重写TMap的TFunc(处理已GC标识的UObject)

## 需求
* 需要解决TArray复制内存问题(C++的引用符号)
* 同层级调用感觉会很奇怪(?单独制作一个数据库类?)
* IDataOrigin::IsAllocate处理方式(检测只被蓝图接口追加数据一次)
* DataAbstract的存放内容
* 可能还需使用更多寻找的方式(Unity问题, 如果直接存放在AActor则不会有问题)

### 23/11/25
* 初步完成测试