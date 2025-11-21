
#include "MassSimpleMoveToTask.h"
#include "MassAITestProject.h" 
#include "MassStateTreeExecutionContext.h"
#include "MassMovementTypes.h"
#include "StateTreeLinker.h"

FMassSimpleMoveToTask::FMassSimpleMoveToTask()
{
	bShouldCallTick = true;
}

//Copy from MW_GotoLocation
//\Plugins\MassWanderAI\Source\MassWanderAI\Private\StateTree\Tasks\MW_GotoLocation.cpp
bool FMassSimpleMoveToTask::Link(FStateTreeLinker& Linker)
{
	Linker.LinkExternalData(MoveTargetHandle);
	Linker.LinkExternalData(TransformHandle);
	return true; 
}

//Copy from MW_GotoLocation
EStateTreeRunStatus FMassSimpleMoveToTask::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
	const FTransformFragment& Transform = Context.GetExternalData(TransformHandle); 
	FMassMoveTargetFragment& MoveTarget = Context.GetExternalData(MoveTargetHandle);

	const FVector CurrentLocation = Transform.GetTransform().GetLocation();

	MoveTarget.Center = InstanceData.TargetLocation;
	MoveTarget.SlackRadius = InstanceData.AcceptableRadius; 
	MoveTarget.Forward = (MoveTarget.Center - CurrentLocation).GetSafeNormal();

	
	MoveTarget.DistanceToGoal = FVector::Dist(MoveTarget.Center, CurrentLocation);
	MoveTarget.CreateNewAction(EMassMovementAction::Move, *Context.GetWorld());

	return EStateTreeRunStatus::Running;
}


//Copy from MW_GotoLocation
EStateTreeRunStatus FMassSimpleMoveToTask::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
	const FTransformFragment& Transform = Context.GetExternalData(TransformHandle);
	FMassMoveTargetFragment& MoveTarget = Context.GetExternalData(MoveTargetHandle); 
	const FVector CurrentLocation = Transform.GetTransform().GetLocation();

	MoveTarget.DistanceToGoal = FVector::Dist(MoveTarget.Center, CurrentLocation);
	MoveTarget.Forward = (MoveTarget.Center - CurrentLocation).GetSafeNormal();
	if (MoveTarget.DistanceToGoal <= InstanceData.AcceptableRadius)
	{
		MoveTarget.CreateNewAction(EMassMovementAction::Stand, *Context.GetWorld());
		return EStateTreeRunStatus::Succeeded;
	}

	return EStateTreeRunStatus::Running;
}


//signal fait dans se code C:\Users\maxim\Documents\GitHub\MassAITestProject\Plugins\MassSmartObjectAI\Source\MassSmartObjectAI\Private\Processors\StateTreeMovementUpdateProcessor.cpp