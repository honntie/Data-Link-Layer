// Fill out your copyright notice in the Description page of Project Settings.


#include "DataLinkLayerLibrary.h"

UDataAbstract* UDataLinkLayerLibrary::FindData(UObject* Target, TSubclassOf<UDataAbstract> Data)
{
	static FName NAME_CreateLibrary = FName("CreateLibrary");    // 接口所用的反射函数名
	static UClass* InterfaceClass = UDataOrigin::StaticClass();    // 接口类型
	static TMap<UObject*, DataLibrary> BPDataLibrary;    // 蓝图数据库缓存
	
	// 获取数据
	static auto FindBPLibraryOrCreate = [](UObject* Target){

		// 查询前清空已经GC的接口对象
		BPDataLibrary.Remove(nullptr);
		BPDataLibrary.Shrink();
		
		DataOrigin_CreateLibrary_Parms Params;

		if (const DataLibrary* RefLibrary = BPDataLibrary.Find(Target))
			Params.ReturnValue = *RefLibrary;    // 使用缓存
		else if (const auto Function = Target->FindFunction(NAME_CreateLibrary))
		{
			// 根据接口原理反射调用函数, 但是调用太慢了需要丢进缓存保存
			Target->ProcessEvent(Function, &Params);
			BPDataLibrary.Add(Target, Params.ReturnValue);

			// 解决Object在蓝图中无法实现构建函数问题
			for (UDataAbstract* Data : Params.ReturnValue)
				Data->OnConstruct();
		}
		return Params.ReturnValue;
	}; 
	
	// 查找数据方法
	auto Predicate = [&Data](const UDataAbstract* Item) { return Item->GetClass() == Data; };
	
	DataLibrary Library;    // 使用数据的数组库
	while (IsValid(Target))
	{
		if (Target->GetClass()->ImplementsInterface(InterfaceClass))
		{
			if (IDataOrigin* NativeOrigin = static_cast<IDataOrigin*>(Target->GetNativeInterfaceAddress(InterfaceClass)))
			{
				// C++接口调用
				DataLibraryStruct NativeLibrary = NativeOrigin->GetLibrary();
			
				if (NativeLibrary.bCanAllocate)
				{
					// 允许蓝图追加数据
					NativeLibrary.Library.Append(FindBPLibraryOrCreate(Target));
					NativeLibrary.bCanAllocate = false;
				}
				Library = NativeLibrary.Library;
			}
			else Library = FindBPLibraryOrCreate(Target);    // 蓝图接口
			
			// 获取数据
			if (UDataAbstract** RefData = Library.FindByPredicate(Predicate)) return *RefData;
		}
		Target = Target->GetOuter();    // 寻找上一层对象
	}
	
	return nullptr;
}
