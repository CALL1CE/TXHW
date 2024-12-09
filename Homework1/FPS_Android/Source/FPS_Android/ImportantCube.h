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
	// �����ж��Ƿ�����Ҫ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Important Cube")
	bool bIsImportant = false; // Ĭ��ֵΪ false	
	
};
