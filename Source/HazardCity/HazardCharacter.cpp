// Fill out your copyright notice in the Description page of Project Settings.

#include "HazardCharacter.h"

// Sets default values
AHazardCharacter::AHazardCharacter()
{
}

void AHazardCharacter::BeginPlay()
{
	Super::BeginPlay();

	// At BeginPlay, we lock every ability to do one big refresh, then unlock those we set by default in BP
	
	const int32 Saved = UnlockedAbilities;
	
	for (int i=1; i < flag(EAbilities::Last); i*=2)
		UnlockedAbilities |= i;

	LockAbilities(UnlockedAbilities);
	
	UnlockAbilities(Saved);
}

bool AHazardCharacter::HasAbilities(int32 Abilities)
{
	return ( UnlockedAbilities & Abilities ) == Abilities;
}

bool AHazardCharacter::MatchAbilities(int32 Abilities, int32 AbilitiesToMatch)
{
	return ( Abilities & AbilitiesToMatch ) == AbilitiesToMatch;
}

int32 AHazardCharacter::LockAbilities(int32 Abilities)
{
	return ChangeAbilities(Abilities, false);
}

int32 AHazardCharacter::UnlockAbilities(int32 Abilities)
{
	return ChangeAbilities(Abilities, true);
}

int32 AHazardCharacter::ChangeAbilities(int32 Abilities, const bool bIsUnlock)
{
	return ChangeAbilitiesInternal(Abilities, bIsUnlock);
}

int32 AHazardCharacter::ChangeAbilitiesInternal_Implementation(int32 Abilities, const bool bIsUnlock)
{
	if (bIsUnlock)
	{
		// Unlock abilities (add them)
		
		const int32 Original = UnlockedAbilities;
		const int32 ToUnlock = Abilities;

		const int32 New = Original | ToUnlock;
		const int32 InvertedOriginal = ~Original;
	
		const int32 NewUnlocked = New & InvertedOriginal;
	
		UnlockedAbilities = New;
		return NewUnlocked;
	}
	else
	{
		// Lock abilities (remove them)
		
		const int32 Original = UnlockedAbilities;
		const int32 ToLock = Abilities;
	
		const int32 InvertedToLock = ~ToLock;
		const int32 New = Original & InvertedToLock;
	
		const int32 InvertedNew = ~New;
	
		const int32 NewLocked = InvertedNew & Original;
	
		UnlockedAbilities = New;
		return NewLocked;
	}
}
