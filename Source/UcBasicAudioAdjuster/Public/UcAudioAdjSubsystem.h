// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UcAudioAdjDeveloperSettings.h"
#include "UcAudioAdjSubsystem.generated.h"

UENUM(BlueprintType, Category = "Audio|Option")
enum class ESoundCategoryId: uint8
{
	Master
	, Music
	, SFX
	, Voice
};


UCLASS(Abstract, Blueprintable, MinimalAPI, meta = (ShowWorldContextPin))
class UUcAudioAdjSubsystemHelperBase : public UObject
{
public:
	GENERATED_BODY()
public:
	
};


/**
 * 
 */
UCLASS()
class UCBASICAUDIOADJUSTER_API UUcAudioAdjSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UUcAudioAdjSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override; 
	virtual void Deinitialize() override;

	// Helper
	UFUNCTION(BlueprintPure, Category = "Audio|Option|Helper")
	UUcAudioAdjSubsystemHelperBase* GetSubsystemHelper()
	{
		return SubsystemHelper;
	};

	// ----------------------------------------
	// Volume Setting Function
	// ----------------------------------------

	// Set volume 
	UFUNCTION(BlueprintCallable, Category = "Audio|Option", meta = (WorldContext = "WorldContextObject", AdvancedDisplay = "3", UnsafeDuringActorConstruction = "true", Keywords = "Audio"))
	void SetMixVolume(const UObject* WorldContextObject, const ESoundCategoryId SoundClassId, float Volume = 1.0f, float Pitch = 1.0f, float FadeInTime = 0.0f, bool bApplyToChildren = true);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Audio|Option", meta = (UnsafeDuringActorConstruction = "true", Keywords = "Audio"))
	TArray<ESoundCategoryId> GetChangedSoundClassVolume();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Audio|Option", meta = (UnsafeDuringActorConstruction = "true", Keywords = "Audio"))
	bool IsChangedSoundClassVolume();

	UFUNCTION(BlueprintCallable, Category = "Audio|Option", meta = (UnsafeDuringActorConstruction = "true", Keywords = "Audio"))
	void OverwriteSoundClassVolume(const ESoundCategoryId SoundClassId);

	// ----------------------------------------
	// Basic SE
	// ----------------------------------------

	// Decision
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Audio|Option|BasicSFX")
	USoundBase* GetDecision();

	// cancel
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Audio|Option|BasicSFX")
	USoundBase* GetCancel();

	// cursor
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Audio|Option|BasicSFX")
	USoundBase* GetCursor();

	// buzzer
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Audio|Option|BasicSFX")
	USoundBase* GetBuzzer();

	// ----------------------------------------
	// Propaty
	// ----------------------------------------

	// current volume(in changeing)
	UFUNCTION(BlueprintPure, Category = "Audio|Option|Volume", meta = (Keywords = "Audio"))
	float GetCurrentVolume(const ESoundCategoryId SoundClassId);
	
	// volume
	UFUNCTION(BlueprintPure, Category = "Audio|Option|Volume", meta = (Keywords = "Audio"))
	float GetVolume(const ESoundCategoryId SoundClassId);

	// ----------------------------------------
	// save, load
	// ----------------------------------------

	// save
	UFUNCTION(BlueprintPure, Category = "Audio|Option|Volume|SaveData", meta = (Keywords = "Audio"))
	TArray<float> SaveVolumeSettings();

	// load
	UFUNCTION(BlueprintCallable, Category = "Audio|Option|Volume|SaveData", meta = (WorldContext = "WorldContextObject", Keywords = "Audio"))
	void LoadVolumeSettings(const UObject* WorldContextObject, TArray<float> Volumes);

public:
	// ヘルパーの実体
	UPROPERTY(BlueprintReadOnly, Category = "Audio|Option")
	TObjectPtr<UUcAudioAdjSubsystemHelperBase> SubsystemHelper;

	// ----------------------------------------
	// サウンドクラス類の実体
	// ----------------------------------------

	UPROPERTY(BlueprintReadOnly, Category = "Audio|Option|SoundClass")
	TObjectPtr<USoundMix> BaseModifier;

	UPROPERTY(BlueprintReadOnly, Category = "Audio|Option|SoundClass")
	TObjectPtr<USoundClass> SoundClassMaster;

	UPROPERTY(BlueprintReadOnly, Category = "Audio|Option|SoundClass")
	TObjectPtr<USoundClass> SoundClassMusic;

	UPROPERTY(BlueprintReadOnly, Category = "Audio|Option|SoundClass")
	TObjectPtr<USoundClass> SoundClassSFX;

	UPROPERTY(BlueprintReadOnly, Category = "Audio|Option|SoundClass")
	TObjectPtr<USoundClass> SoundClassVoice;

private:
	// ヘルパークラスの型
	TSubclassOf< class UUcAudioAdjSubsystemHelperBase > SubsystemHelperClass;

	float VolumeCurrentMaster = 1.0f;
	float VolumeCurrentMusic = 0.8f;
	float VolumeCurrentSFX = 0.8f;
	float VolumeCurrentVoice = 0.8f;

	float VolumeMaster = 1.0f;
	float VolumeMusic = 0.8f;
	float VolumeSFX = 0.8f;
	float VolumeVoice = 0.8f;
};
