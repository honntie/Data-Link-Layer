// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DataAbstract.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class DATALINKLAYER_API UDataAbstract : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnConstruct();
};
