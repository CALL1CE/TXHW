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
		// �ж��Ƿ������StaticMeshActor
		//AStaticMeshActor* HitCube = Cast<AStaticMeshActor>(OtherActor);
		// �ж��Ƿ������ ImportantCube
		AImportantCube* HitCube = Cast<AImportantCube>(OtherActor);
		if (HitCube != nullptr)
		{
			// ��ȡ��ҽ�ɫ
			AActor* OwnerActor = GetOwner(); // �����䵯���������ǽ�ɫ
			if (OwnerActor)
			{
				AFPS_AndroidCharacter* PlayerCharacter = Cast<AFPS_AndroidCharacter>(OwnerActor);
				if (PlayerCharacter)
				{
					// ���ӻ���
					if (HitCube->bIsImportant)
					{
						PlayerCharacter->AddScore(20); // ÿ����һ����Ҫ Cube ���� 20 ��
					}
					else
					{
						PlayerCharacter->AddScore(10); // ÿ����һ�� Cube ���� 10 ��
					}
				}
			}
			// ��ȡ�����ϵı����������
			if (!HitCube->Tags.Contains("HitOnce"))
			{
				// ����ǵ�һ�α����У����ñ�ǲ��޸�����
				HitCube->Tags.Add("HitOnce");

				// ��ȡ��ǰ���������ֵ
				FVector CurrentScale = HitCube->GetActorScale3D();
				float ScaleFactor = 0.5f; // �滻Ϊ��ϣ���ı���
				FVector NewScale = FVector(CurrentScale.X * ScaleFactor, CurrentScale.Y * ScaleFactor, CurrentScale.Z * ScaleFactor);
				HitCube->SetActorScale3D(NewScale);
			}
			else
			{
				// ����ǵڶ��α����У����ٷ���
				HitCube->Destroy();
			}

		}
		Destroy();
	}
}