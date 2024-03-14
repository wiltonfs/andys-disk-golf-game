// Copyright Felix Wilton. All Rights Reserved.


#include "Frisbee.h"

// Sets default values
AFrisbee::AFrisbee()
{
 	// Set this actor to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;

	// Set up the Collider Component
	ColliderComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleColliderComponent"));
	ColliderComponent->SetCapsuleSize(20.f, 20.f);
	ColliderComponent->BodyInstance.SetCollisionProfileName("Projectile");
	ColliderComponent->OnComponentHit.AddDynamic(this, &AFrisbee::OnHit);		// set up a notification for when this component hits something blocking
	ColliderComponent->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f)); // Players can't walk on it
	ColliderComponent->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = ColliderComponent;

	// Set up the Projectile Movement Component
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(RootComponent);
	ProjectileMovementComponent->MaxSpeed = 10000.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = false;
	ProjectileMovementComponent->bShouldBounce = true;

	// Set up the Frisbee Mesh Component
	FrisbeeMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrisbeeMeshComponent"));
	FrisbeeMeshComponent->SetupAttachment(RootComponent);

	// Set default values for blueprint-accessible parameters
	DragCoefficient = 0.1f;
	LiftCoefficient = 0.05f;
	
	// Reset velocity and angle
	ResetFrisbee();
}

// Called when the game starts or when spawned
void AFrisbee::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFrisbee::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Calculate frisbee physics, apply forces

}

void AFrisbee::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Add impulse if we hit a physics object
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

	}
}

void AFrisbee::ResetFrisbee()
{
	ProjectileMovementComponent->InitialSpeed = 0.0f;
	ProjectileMovementComponent->Velocity = FVector::ZeroVector;
	bRealThrow = false;

	// Reset the frisbee's rotation
	FRotator NewRotation = FRotator::ZeroRotator;
	SetActorRotation(NewRotation);

}

void AFrisbee::StartThrow(FFrisbeeThrow ThrowParams, bool bIsRealThrow)
{
	ResetFrisbee();

	bRealThrow = bIsRealThrow;

	// Reset the frisbee's position and velocity
	SetActorTransform(ThrowParams.Transform);
	ProjectileMovementComponent->Velocity = ThrowParams.Transform.GetRotation().GetForwardVector() * ThrowParams.ThrowVelocity;
	
	// Set the frisbee's initial angular velocity (spin)
	FVector SpinAxis = ThrowParams.Transform.GetRotation().GetUpVector();
	FRotator SpinRotation = FRotator(0.0f, 0.0f, FMath::RadiansToDegrees(ThrowParams.SpinVelocity));
	FrisbeeMeshComponent->SetPhysicsAngularVelocityInDegrees(SpinRotation.Euler() * ThrowParams.SpinVelocity); // Set angular velocity

	// Set the frisbee's initial roll angle
	FRotator NewRotation = GetActorRotation();
	NewRotation.Roll = ThrowParams.StartingRollAngle;
	SetActorRotation(NewRotation);

	// Re-activate the simulation
	ProjectileMovementComponent->SetUpdatedComponent(RootComponent);
	ProjectileMovementComponent->bSimulationEnabled = true;
	ProjectileMovementComponent->Activate();
}

