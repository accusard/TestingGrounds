// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "AIController.h"
#include "PatrollingGuard.h"
#include "BehaviorTree/BlackboardComponent.h"




EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // Patrol Points
    AAIController* AIController = OwnerComp.GetAIOwner();
    APawn* ControlledPawn = AIController->GetPawn();
    APatrollingGuard* PatrollingGuard = Cast<APatrollingGuard>(ControlledPawn);
    TArray<AActor*> PatrolPoints = PatrollingGuard->GetPatrolPoints();
    if(PatrolPoints.Num() > 0)
    {
        // waypoint
        auto BlackboardComp = OwnerComp.GetBlackboardComponent();
        auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
        BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);
        
        // cycle index
        int NextIndex = (Index + 1) % PatrolPoints.Num();
        BlackboardComp->SetValueAsInt(WaypointKey.SelectedKeyName,NextIndex);
        
        return EBTNodeResult::Succeeded;
    }
    else
    {
        UE_LOG(LogTemp,Warning,TEXT("The PatrolPoint array is empty."));
        return EBTNodeResult::Failed;
    }
}
