// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/MeshComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(CameraBoom);
	//CameraComponent->SetRelativeLocationAndRotation(FVector(35.0f, 0.0f, 140.0f), FRotator(0.0f, 330.0f, 0.0f));


	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMesh->SetupAttachment(CameraBoom);
	/*bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bEnableMouseOverEvents = true;
	bEnableTouchEvents = true;
	bEnableClickEvents = true;
	bEnableTouchOverEvents = true;*/

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapBegin);
}

void APlayerCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Перевірка чи OtherActor має компонент Static Mesh
	UStaticMeshComponent* OtherStaticMesh = Cast<UStaticMeshComponent>(OtherComp);
	if (OtherStaticMesh)
	{
		// Змініть колір OtherStaticMesh тут. Наприклад:
		//OtherStaticMesh->SetMaterial(0, GetTargetMaterial());
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::Turn);
}

void APlayerCharacter::MoveForward(float Value)
{
	const FVector ForwardVector = GetActorForwardVector();
	AddMovementInput(ForwardVector, Value);
}

void APlayerCharacter::MoveRight(float Value)
{
	const FVector RightVector = GetActorRightVector();
	AddMovementInput(RightVector, Value);
}

void APlayerCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}
