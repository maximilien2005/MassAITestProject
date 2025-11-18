#pragma once

#include "CoreMinimal.h"
#include "MassStateTreeTypes.h"
#include "MassNavigationFragments.h" 
#include "MassCommonFragments.h"      
#include "MassSimpleMoveToTask.generated.h"

USTRUCT()
struct FMassSimpleMoveToTaskInstanceData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, Category = Parameter, meta = (Input))
	FVector TargetLocation = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, Category = Parameter, meta = (Input))
	float AcceptableRadius = 0.0f;
};

USTRUCT(meta = (DisplayName = "Simple Move To"))
struct FMassSimpleMoveToTask : public FMassStateTreeTaskBase
{
	GENERATED_BODY()
	using FInstanceDataType = FMassSimpleMoveToTaskInstanceData;

	FMassSimpleMoveToTask();
	virtual bool Link(FStateTreeLinker& Linker) override;
	virtual const UStruct* GetInstanceDataType() const override { return FMassSimpleMoveToTaskInstanceData::StaticStruct(); }
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;

protected:
	TStateTreeExternalDataHandle<FMassMoveTargetFragment> MoveTargetHandle;
	TStateTreeExternalDataHandle<FTransformFragment> TransformHandle;
};