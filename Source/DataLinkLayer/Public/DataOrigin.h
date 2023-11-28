// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAbstract.h"
#include "Templates/SubclassOf.h"
#include "UObject/Interface.h"
#include "DataOrigin.generated.h"

// This class does not need to be modified.    meta=(CannotImplementInterfaceInBlueprint)
UINTERFACE(MinimalAPI)
class UDataOrigin : public UInterface { GENERATED_BODY() };


struct DataLibraryStruct
{
	TArray<UDataAbstract*>& Library;
	bool& bCanAllocate;

	DataLibraryStruct& operator=(const DataLibraryStruct& Struct)
	{
		Library = Struct.Library;
		bCanAllocate = Struct.bCanAllocate;
		return *this;
	}
};

class DATALINKLAYER_API IDataOrigin
{
	GENERATED_BODY()
	
	
public:

	UFUNCTION(BlueprintImplementableEvent)
	TArray<UDataAbstract*> CreateLibrary();

	virtual DataLibraryStruct GetLibrary() = 0;
};

