// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaBattle.h"
#include "ABGameInstance.h"
#include "ABPawn.h"


// Sets default values
AABPawn::AABPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Body = CreateDefaultSubobject<UCapsuleComponent>(TEXT("root"));
	RootComponent = Body;
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Body);
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("movement"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(Mesh);
	Camera->SetRelativeLocationAndRotation(FVector(0.0f, -300.0f, 350.0f), FRotator(-30.0f, 90.0f, 0.0f));

	Body->SetCapsuleHalfHeight(88.0f);
	Body->SetCapsuleRadius(36.0f);
	Mesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	
	//변수가 중복되지 않게 하기 위해(계속 변수를 공유한다) static을 사용한다.
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		SK_Mesh(TEXT("SkeletalMesh'/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_FrostGiant.SK_CharM_FrostGiant'"));
	Mesh->SetSkeletalMesh(SK_Mesh.Object);
	//AutoPossessPlayer = EAutoReceiveInput::Player0;

	MaxHP = 100.0f;
}

// Called when the game starts or when spawned
void AABPawn::BeginPlay()
{
	Super::BeginPlay();
	CurrentHP = MaxHP;

	int32 NewIndex = FMath::RandRange(0, CharacterAssets.Num() - 1);
	UABGameInstance* ABGameInstance = Cast<UABGameInstance>(GetGameInstance());
	if (ABGameInstance)
	{
		TAssetPtr<USkeletalMesh> NewCharacter = Cast<USkeletalMesh>(ABGameInstance->AssetLoader.SynchronousLoad(CharacterAssets[NewIndex]));
		if (NewCharacter)
		{
			Mesh->SetSkeletalMesh(NewCharacter.Get());
		}
	}
}

// Called every frame
void AABPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AABPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

