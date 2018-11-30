// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "PatrollingGuard.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGGROUNDS_API APatrollingGuard : public ATP_ThirdPersonCharacter
{
	GENERATED_BODY()
	
public:
    UFUNCTION()
    const TArray<AActor*> GetPatrolPoints() const;
    
protected:
    UPROPERTY(EditAnywhere)
    TArray<AActor*> PatrolPoints_CPP;
	
	
};
