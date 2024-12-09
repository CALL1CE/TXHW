// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "ImportantCube.generated.h"

/**
 * 
 */
UCLASS()
class FPS_ANDROID_API AImportantCube : public AStaticMeshActor
{
	GENERATED_BODY()
	
	
public:
	// 用于判断是否是重要方块
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Important Cube")
	bool bIsImportant = false; // 默认值为 false	
	
};
