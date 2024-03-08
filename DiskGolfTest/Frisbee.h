// Copyright Felix Wilton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"

#include "Frisbee.generated.h"

USTRUCT(BlueprintType)
struct FFrisbeeThrow
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FTransform Transform; // position and orientation of the frisbee

	UPROPERTY(BlueprintReadWrite)
	float ThrowVelocity; // in cm per second

	UPROPERTY(BlueprintReadWrite)
	float SpinVelocity; // in radians per second

	UPROPERTY(BlueprintReadWrite)
	float StartingRollAngle; // in degrees
};

UCLASS()
class DISKGOLFTEST_API AFrisbee : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AFrisbee();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* FrisbeeMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCapsuleComponent* ColliderComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Frisbee Parameters")
	float DragCoefficient;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Frisbee Parameters")
	float LiftCoefficient;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Frisbee Parameters")
	bool bRealThrow;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// Starts a new Frisbee throw
	UFUNCTION(BlueprintCallable, Category = "Frisbee")
	void StartThrow(FFrisbeeThrow ThrowParams, bool bIsRealThrow = true);

	/** Returns CollisionComp subobject **/
	UCapsuleComponent* GetCollisionComp() const { return ColliderComponent; }

	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovementComponent; }

};
