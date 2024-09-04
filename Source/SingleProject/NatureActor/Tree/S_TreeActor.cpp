// Fill out your copyright notice in the Description page of Project Settings.


#include "S_TreeActor.h"

AS_TreeActor::AS_TreeActor()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TreeMesh"));
	RootComponent = Mesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> TreeMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Mediterranean_Coast/Meshes/SM_Olive_Small_01.SM_Olive_Small_01'"));
	if (TreeMeshRef.Succeeded())
	{
		Mesh->SetStaticMesh(TreeMeshRef.Object);
	}


}

void AS_TreeActor::BeginPlay()
{
	Super::BeginPlay();
}
