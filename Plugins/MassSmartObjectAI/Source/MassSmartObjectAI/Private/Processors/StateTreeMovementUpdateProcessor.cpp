#include "Processors/StateTreeMovementUpdateProcessor.h"

#include "MassCommonFragments.h"
#include "MassExecutionContext.h"
#include "MassNavigationFragments.h"
#include "MassSignalSubsystem.h"
#include "MassStateTreeFragments.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

UStateTreeMovementUpdateProcessor::UStateTreeMovementUpdateProcessor() :
	EntityQuery(*this)
{
	// Important : s'assurer qu'il s'exécute automatiquement
	bAutoRegisterWithProcessingPhases = true;
}

void UStateTreeMovementUpdateProcessor::ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager)
{
	EntityQuery.AddRequirement<FMassStateTreeInstanceFragment>(EMassFragmentAccess::None);

	EntityQuery.AddRequirement<FMassMoveTargetFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadOnly);
	EntityQuery.AddSubsystemRequirement<UMassSignalSubsystem>(EMassFragmentAccess::ReadWrite);
}

void UStateTreeMovementUpdateProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	FVector TargetLocation = FVector::ZeroVector;
	if (const UWorld* World = Context.GetWorld())
	{
		if (const APawn* PlayerPawn = World->GetFirstPlayerController() ? World->GetFirstPlayerController()->GetPawn() : nullptr)
		{
			TargetLocation = PlayerPawn->GetActorLocation();
		}
	}
	EntityQuery.ForEachEntityChunk(Context, [this, TargetLocation](FMassExecutionContext& Context)
		{
			auto& SignalSubsystem = Context.GetMutableSubsystemChecked<UMassSignalSubsystem>();

			const auto MassMoveTargetFragments = Context.GetMutableFragmentView<FMassMoveTargetFragment>();
			const auto TransformFragments = Context.GetFragmentView<FTransformFragment>();

			const int32 NumEntities = Context.GetNumEntities();
			for (int EntityIdx = 0; EntityIdx < NumEntities; EntityIdx++)
			{
				auto& MassMoveTargetFragment = MassMoveTargetFragments[EntityIdx];
				const auto& TransformFragment = TransformFragments[EntityIdx];

				if (MassMoveTargetFragment.GetCurrentAction() == EMassMovementAction::Move)
				{
					MassMoveTargetFragment.Center = TargetLocation;
					auto Distance = FVector::Dist2D(TransformFragment.GetTransform().GetLocation(), MassMoveTargetFragment.Center);

					if (Distance < MassMoveTargetFragment.SlackRadius)
					{
						SignalSubsystem.SignalEntityDeferred(Context, UE::Mass::Signals::StateTreeActivate, Context.GetEntity(EntityIdx));
					}
				}
			}
		});
}