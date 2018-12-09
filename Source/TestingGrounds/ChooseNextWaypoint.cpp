// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "AIController.h"
#include "Components/PatrolRoute.h"
#include "BehaviorTree/BlackboardComponent.h"




EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // Patrol Points
    AAIController* AIController = OwnerComp.GetAIOwner();
    APawn* ControlledPawn = AIController->GetPawn();
    EBTNodeResult::Type Result = EBTNodeResult::Failed;
    
    if(UPatrolRoute* PatrolRouteArray = Cast<AActor>(ControlledPawn)->FindComponentByClass<UPatrolRoute>())
    {
        TArray<AActor*> PatrolPoints = PatrolRouteArray->GetPatrolPoints();
        if(PatrolPoints.Num() > 0)
        {
            // waypoint
            auto BlackboardComp = OwnerComp.GetBlackboardComponent();
            auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
            BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);
            
            // cycle index
            int NextIndex = (Index + 1) % PatrolPoints.Num();
            BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName,NextIndex);
            
            Result = EBTNodeResult::Succeeded;
        }
        else
        {
            UE_LOG(LogTemp,Warning,TEXT("The PatrolPoints array is empty."));
        }
    }
    return Result;
}
