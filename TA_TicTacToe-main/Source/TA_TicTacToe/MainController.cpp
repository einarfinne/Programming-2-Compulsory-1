// Fill out your copyright notice in the Description page of Project Settings.


#include "MainController.h"
#include "Components/SphereComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include <UObject/ConstructorHelpers.h>
#include "Containers/Array.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMainController::AMainController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WinStatus.Init(NULL, 9);

	Spheres.Init(NULL, 9);
	Spheres[0] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh1"));
	Spheres[1] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh2"));
	Spheres[2] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh3"));
	Spheres[3] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh4"));
	Spheres[4] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh5"));
	Spheres[5] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh6"));
	Spheres[6] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh7"));
	Spheres[7] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh8"));
	Spheres[8] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh9"));

	RootComponent = Spheres[4];
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		MeshComponentAsset(TEXT("StaticMesh'/Game/StarterContent/Props/MaterialSphere.MaterialSphere'"));
	for (int i{}; i < 9; i++)
	{
		if (i != 4)
		{
			Spheres[i]->SetupAttachment(GetRootComponent());
		}
		Spheres[i]->SetStaticMesh(MeshComponentAsset.Object);
	}
	


	Red = CreateDefaultSubobject<UMaterial>(TEXT("RedMaterial"));
	Blue = CreateDefaultSubobject<UMaterial>(TEXT("BlueMaterial"));
	White = CreateDefaultSubobject<UMaterial>(TEXT("WhiteMaterial"));


	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 800.f;

	// Attach the Camera to SpringArm
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);



	Spheres[0]->SetRelativeLocation(FVector(200.f, -200.f, 0.f));
	Spheres[1]->SetRelativeLocation(FVector(200.f, 0.f, 0.f));
	Spheres[2]->SetRelativeLocation(FVector(200.f, 200.f, 0.f));
	Spheres[3]->SetRelativeLocation(FVector(0.f, -200.f, 0.f));
	Spheres[4]->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	Spheres[5]->SetRelativeLocation(FVector(0.f, 200.f, 0.f));
	Spheres[6]->SetRelativeLocation(FVector(-200.f, -200.f, 0.f));
	Spheres[7]->SetRelativeLocation(FVector(-200.f, 0.f, 0.f));
	Spheres[8]->SetRelativeLocation(FVector(-200.f, 200.f, 0.f));

	TurnCounter = 0;
	SphereStatus.Init(NULL, 9);

}

// Called when the game starts or when spawned
void AMainController::BeginPlay()
{
	Super::BeginPlay();
	
	
	for (int i{}; i < 9; i++)
	{
		Spheres[i]->SetMaterial(1, White);
		UE_LOG(LogTemp, Warning, TEXT("White Balls"));
	}
}

// Called every frame
void AMainController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("1", IE_Pressed, this, &AMainController::OnePressed);
	PlayerInputComponent->BindAction("2", IE_Pressed, this, &AMainController::TwoPressed);
	PlayerInputComponent->BindAction("3", IE_Pressed, this, &AMainController::ThreePressed);
	PlayerInputComponent->BindAction("4", IE_Pressed, this, &AMainController::FourPressed);
	PlayerInputComponent->BindAction("5", IE_Pressed, this, &AMainController::FivePressed);
	PlayerInputComponent->BindAction("6", IE_Pressed, this, &AMainController::SixPressed);
	PlayerInputComponent->BindAction("7", IE_Pressed, this, &AMainController::SevenPressed);
	PlayerInputComponent->BindAction("8", IE_Pressed, this, &AMainController::EightPressed);
	PlayerInputComponent->BindAction("9", IE_Pressed, this, &AMainController::NinePressed);

}

void AMainController::OnePressed()
{
	TurnController(0);
	
}

void AMainController::TwoPressed()
{
	TurnController(1);
}

void AMainController::ThreePressed()
{
	TurnController(2);
}

void AMainController::FourPressed()
{
	TurnController(3);
}

void AMainController::FivePressed()
{
	TurnController(4);
}

void AMainController::SixPressed()
{
	TurnController(5);
}

void AMainController::SevenPressed()
{
	TurnController(6);
}

void AMainController::EightPressed()
{
	TurnController(7);
}

void AMainController::NinePressed()
{
	TurnController(8);
}





void AMainController::TurnController(int sphereindex)
{
	if (SphereStatus[sphereindex] == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("That index is already taken"));

		return;
	}


	if (TurnCounter % 2 == 0)
	{
		Spheres[sphereindex]->SetMaterial(0, Blue);
		WinStatus[sphereindex] = +1;
		UE_LOG(LogTemp, Warning, TEXT("Blue"));
	}
	else if (TurnCounter % 2 == 1)
	{
		Spheres[sphereindex]->SetMaterial(0, Red);
		WinStatus[sphereindex] = -1;
		UE_LOG(LogTemp, Warning, TEXT("Red"));
	}
	SphereStatus[sphereindex] = true;
	TurnCounter++;
	
	WinCondition();
	
}
void AMainController::WinCondition()
{
	int rad1 = WinStatus[0] + WinStatus[1] + WinStatus[2];
	int rad2 = WinStatus[3] + WinStatus[4] + WinStatus[5];
	int rad3 = WinStatus[6] + WinStatus[7] + WinStatus[8];
	int rad4 = WinStatus[0] + WinStatus[4] + WinStatus[8];
	int rad5 = WinStatus[2] + WinStatus[4] + WinStatus[6];
	int rad6 = WinStatus[3] + WinStatus[1] + WinStatus[2];
	int rad7 = WinStatus[0] + WinStatus[3] + WinStatus[6];
	int rad8 = WinStatus[2] + WinStatus[5] + WinStatus[8];

	if (rad1 == 3 || rad2 == 3 || rad3 == 3 || rad4 == 3 || rad5 == 3 || rad6 == 3 || rad7 == 3 || rad8 == 3)
	{
		UE_LOG(LogTemp, Warning, TEXT("Blue Player Has Won!"))
	}
	else if (rad1 == -3 || rad2 == -3 || rad3 == -3 || rad4 == -3 || rad5 == -3 || rad6 == -3 || rad7 == -3 || rad8 == -3)
	{
		UE_LOG(LogTemp, Warning, TEXT("Red Player Has Won!"));
	}
}