// Copyright Felix Wilton. All Rights Reserved.


#include "Frisbee.h"

// Sets default values
AFrisbee::AFrisbee()
{
 	// Set this actor to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;

	// Set up the Frisbee Mesh Component
	FrisbeeMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrisbeeMeshComponent"));

	// Set up the Collider Component
	FrisbeeMeshComponent->BodyInstance.SetCollisionProfileName("Projectile");
	FrisbeeMeshComponent->OnComponentHit.AddDynamic(this, &AFrisbee::OnHit);		// set up a notification for when this component hits something blocking
	FrisbeeMeshComponent->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f)); // Players can't walk on it
	FrisbeeMeshComponent->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = FrisbeeMeshComponent;

	// Set up the Projectile Movement Component
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(RootComponent);
	ProjectileMovementComponent->MaxSpeed = 10000.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = false;
	ProjectileMovementComponent->bShouldBounce = true;

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

	SpinValue = ThrowParams.SpinVelocity;

	// Reset the frisbee's position and velocity
	SetActorTransform(ThrowParams.Transform);
	ProjectileMovementComponent->Velocity = ThrowParams.Transform.GetRotation().GetForwardVector() * ThrowParams.ThrowVelocity;
	
	// Set the frisbee's initial angular velocity (spin)
	FVector SpinAxis = ThrowParams.Transform.GetRotation().GetUpVector();
	FRotator SpinRotation = FRotator(0.0f, 0.0f, FMath::RadiansToDegrees(ThrowParams.SpinVelocity));
	//FrisbeeMeshComponent->SetPhysicsAngularVelocityInDegrees(SpinRotation.Euler() * ThrowParams.SpinVelocity); // Set angular velocity

	// Set the frisbee's initial roll angle
	FRotator NewRotation = GetActorRotation();
	NewRotation.Roll = ThrowParams.StartingRollAngle;
	SetActorRotation(NewRotation);

	// Re-activate the simulation
	ProjectileMovementComponent->SetUpdatedComponent(RootComponent);
	ProjectileMovementComponent->bSimulationEnabled = true;
	ProjectileMovementComponent->Activate();
}

// -------------------------------------------------------- FRISBEE PHYSICS

void AFrisbee::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Environmental constants
	const float Rho = 1.18f; // Air density in kg/m^3
	float r = .1; // Radius in m
	float h = .01;

	FVector V = ProjectileMovementComponent->Velocity;
	float Speed = V.Size();
	float WingArea = PI * FMath::Square(r);
	float CrossSectionalArea = r * h;

	// Calculate angle of attack using velocity direction
	float AngleOfAttack = FMath::RadiansToDegrees(FMath::Atan2(V.Z, V.X));

	// Get the frisbee's rotation as a quaternion
	FQuat FrisbeeRotation = GetActorQuat();
	FVector Z = FVector(0, 0, 1);
	FVector Y = FVector(0, 1, 0);
	FVector WorldZAxis = FrisbeeRotation.RotateVector(Z);
	FVector WorldYAxis = FrisbeeRotation.RotateVector(Y);

	// Lift force
	FVector LiftDirection = WorldZAxis;
	FVector LiftForce = LiftDirection * 0.5f * Rho * FMath::Square(Speed) * LiftCoefficient * WingArea;

	// Drag force
	FVector DragDirection = -V.GetSafeNormal();
	float DragMagnitude = 0.5f * Rho * FMath::Square(Speed) * DragCoefficient * CrossSectionalArea;
	FVector DragForce = DragMagnitude * DragDirection;

	// "Side" force
	FVector SideForce = WorldYAxis * SideCoefficient * SpinValue * Speed;

	// Apply forces to the frisbee
	FVector TotalForce = DragForce + LiftForce + SideForce;
	ProjectileMovementComponent->AddForce(TotalForce);
}




