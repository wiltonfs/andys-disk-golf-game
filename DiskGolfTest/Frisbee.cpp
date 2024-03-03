// Copyright Felix Wilton. All Rights Reserved.


#include "Frisbee.h"

// Sets default values
AFrisbee::AFrisbee()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InitialLifeSpan = 3.0f; // Die after 3 seconds by default

	// Set up the root component
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// Set up the Projectile Movement Component
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(RootComponent);
	ProjectileMovementComponent->InitialSpeed = 1000.f; // Launch speed
	ProjectileMovementComponent->MaxSpeed = 3000.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = false;
	ProjectileMovementComponent->bShouldBounce = true;

	// Set up the Frisbee Mesh Component
	FrisbeeMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrisbeeMeshComponent"));
	FrisbeeMeshComponent->SetupAttachment(RootComponent);

	// Set up the Collider Component
	ColliderComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ColliderComponent"));
	ColliderComponent->SetupAttachment(RootComponent);
	ColliderComponent->SetCapsuleSize(50.f, 20.f);
	ColliderComponent->BodyInstance.SetCollisionProfileName("Projectile");
	ColliderComponent->OnComponentHit.AddDynamic(this, &AFrisbee::OnHit);		// set up a notification for when this component hits something blocking
	ColliderComponent->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f)); // Players can't walk on it
	ColliderComponent->CanCharacterStepUpOn = ECB_No;

	// Set default values for blueprint-accessible parameters
	DragCoefficient = 0.1f;
	LiftCoefficient = 0.05f;
}

AFrisbee::AFrisbee(const FFrisbeeThrow& FrisbeeThrow)
{
	// Set Frisbee parameters based on the FFrisbeeThrow struct
	SetActorTransform(FrisbeeThrow.Transform);

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InitialLifeSpan = 3.0f; // Die after 3 seconds by default

	// Set up the root component
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// Set up the Projectile Movement Component
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(RootComponent);
	ProjectileMovementComponent->InitialSpeed = FrisbeeThrow.InitialSpeed; // Launch speed
	ProjectileMovementComponent->MaxSpeed = 5000.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = false;
	ProjectileMovementComponent->bShouldBounce = true;

	// Set up the Frisbee Mesh Component
	FrisbeeMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrisbeeMeshComponent"));
	FrisbeeMeshComponent->SetupAttachment(RootComponent);

	// Set up the Collider Component
	ColliderComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ColliderComponent"));
	ColliderComponent->SetupAttachment(RootComponent);
	ColliderComponent->SetCapsuleSize(50.f, 20.f);
	ColliderComponent->BodyInstance.SetCollisionProfileName("Projectile");
	ColliderComponent->OnComponentHit.AddDynamic(this, &AFrisbee::OnHit);		// set up a notification for when this component hits something blocking
	ColliderComponent->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f)); // Players can't walk on it
	ColliderComponent->CanCharacterStepUpOn = ECB_No;

	// Set default values for blueprint-accessible parameters
	DragCoefficient = 0.1f;
	LiftCoefficient = 0.05f;
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
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}
}

