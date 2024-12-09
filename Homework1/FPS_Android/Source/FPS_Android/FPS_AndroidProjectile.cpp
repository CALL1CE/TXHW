// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPS_AndroidProjectile.h"
#include "FPS_AndroidCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/StaticMeshActor.h"
#include "ImportantCube.h"
AFPS_AndroidProjectile::AFPS_AndroidProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AFPS_AndroidProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AFPS_AndroidProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		// 判断是否击中了StaticMeshActor
		//AStaticMeshActor* HitCube = Cast<AStaticMeshActor>(OtherActor);
		// 判断是否击中了 ImportantCube
		AImportantCube* HitCube = Cast<AImportantCube>(OtherActor);
		if (HitCube != nullptr)
		{
			// 获取玩家角色
			AActor* OwnerActor = GetOwner(); // 假设射弹的所有者是角色
			if (OwnerActor)
			{
				AFPS_AndroidCharacter* PlayerCharacter = Cast<AFPS_AndroidCharacter>(OwnerActor);
				if (PlayerCharacter)
				{
					// 增加积分
					if (HitCube->bIsImportant)
					{
						PlayerCharacter->AddScore(20); // 每击中一个重要 Cube 增加 20 分
					}
					else
					{
						PlayerCharacter->AddScore(10); // 每击中一个 Cube 增加 10 分
					}
				}
			}
			// 获取方块上的标记组件或变量
			if (!HitCube->Tags.Contains("HitOnce"))
			{
				// 如果是第一次被击中，设置标记并修改缩放
				HitCube->Tags.Add("HitOnce");

				// 获取当前方块的缩放值
				FVector CurrentScale = HitCube->GetActorScale3D();
				float ScaleFactor = 0.5f; // 替换为你希望的倍数
				FVector NewScale = FVector(CurrentScale.X * ScaleFactor, CurrentScale.Y * ScaleFactor, CurrentScale.Z * ScaleFactor);
				HitCube->SetActorScale3D(NewScale);
			}
			else
			{
				// 如果是第二次被击中，销毁方块
				HitCube->Destroy();
			}

		}
		Destroy();
	}
}