// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataOrigin.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DataLinkLayerLibrary.generated.h"

/**
 * 
 */

UCLASS()
class DATALINKLAYER_API UDataLinkLayerLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

private:
	typedef TArray<UDataAbstract*> DataLibrary;
	
	struct DataOrigin_CreateLibrary_Parms
	{
		DataLibrary ReturnValue;
	};

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(DefaultToSelf="Target", DeterminesOutputType="Data"))
	static UDataAbstract* FindData(UObject* Target, TSubclassOf<UDataAbstract> Data);
};
