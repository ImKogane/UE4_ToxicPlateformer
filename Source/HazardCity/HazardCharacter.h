// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "HazardCharacter.generated.h"

UENUM(BlueprintType, meta=(Bitflags, UseEnumValuesAsMaskValuesInEditor="true"))
enum class EAbilities : uint8
{
	Empty			= 0 UMETA(Hidden),
	ToxicImmunity	= 1 << 0,
	Jetpack			= 1 << 1,
	CleanSoda		= 1 << 2,
	Last			= 1 << 3 UMETA(Hidden),
};
ENUM_CLASS_FLAGS(EAbilities)

#define flag(X) static_cast<uint8>(X)

UCLASS(Blueprintable, BlueprintType)
class HAZARDCITY_API AHazardCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHazardCharacter();
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Bitmask, BitmaskEnum="EAbilities"))
	int32 UnlockedAbilities = 0;

	UFUNCTION(BlueprintPure)
	bool HasAbilities(UPARAM(meta=(Bitmask, BitmaskEnum="EAbilities")) int32 Abilities);
	
	UFUNCTION(BlueprintPure)
	bool MatchAbilities(UPARAM(meta=(Bitmask, BitmaskEnum="EAbilities")) int32 Abilities, UPARAM(meta=(Bitmask, BitmaskEnum="EAbilities")) int32 AbilitiesToMatch);
	
	UFUNCTION(BlueprintCallable)
	int32 ChangeAbilities(UPARAM(meta=(Bitmask, BitmaskEnum="EAbilities")) int32 Abilities, const bool bIsUnlock = true);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	int32 ChangeAbilitiesInternal(UPARAM(meta=(Bitmask, BitmaskEnum="EAbilities")) int32 Abilities, const bool bIsUnlock = true);
	
	UFUNCTION(BlueprintCallable)
	int32 LockAbilities(UPARAM(meta=(Bitmask, BitmaskEnum="EAbilities")) int32 Abilities);
	
	UFUNCTION(BlueprintCallable)
	int32 UnlockAbilities(UPARAM(meta=(Bitmask, BitmaskEnum="EAbilities")) int32 Abilities);
	
};
