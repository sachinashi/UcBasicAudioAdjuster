// Fill out your copyright notice in the Description page of Project Settings.


#include "UcAudioAdjSubsystem.h"
#include "UcAudioAdjDeveloperSettings.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundClass.h"

UUcAudioAdjSubsystem::UUcAudioAdjSubsystem()
{
	// 拡張用BPのクラス情報を検索・取得。
	// プロジェクト設定でBPアセットのパスを設定
	TSubclassOf<class UUcAudioAdjSubsystemHelperBase> TempSubClass = 
		GetDefault<UUcAudioAdjDeveloperSettings>()->UcAudioAdjSubsystemHelperClass;
	if(TempSubClass)
	{
		SubsystemHelperClass = TempSubClass;
	}

	// 各種サウンドクラスを生成
	BaseModifier = GetDefault<UUcAudioAdjDeveloperSettings>()->SoundMixClass.LoadSynchronous();
	SoundClassMaster = GetDefault<UUcAudioAdjDeveloperSettings>()->SoundClassMaster.LoadSynchronous();
	SoundClassMusic = GetDefault<UUcAudioAdjDeveloperSettings>()->SoundClassMusic.LoadSynchronous();
	SoundClassSFX = GetDefault<UUcAudioAdjDeveloperSettings>()->SoundClassSFX.LoadSynchronous();
	SoundClassVoice = GetDefault<UUcAudioAdjDeveloperSettings>()->SoundClassVoice.LoadSynchronous();

	VolumeCurrentMaster = VolumeMaster = SoundClassMaster->Properties.Volume;
	VolumeCurrentMusic = VolumeMusic = SoundClassMusic->Properties.Volume;
	VolumeCurrentSFX = VolumeSFX = SoundClassSFX->Properties.Volume;
	VolumeCurrentVoice = VolumeVoice = SoundClassVoice->Properties.Volume;

}

void UUcAudioAdjSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	SubsystemHelper = nullptr;
	if (SubsystemHelperClass)
	{
		//	拡張用BPを生成・設定
		// ※第一引数に GetTransientPackage() を指定するとプラグインのパッケージ化に失敗する模様
		SubsystemHelper = NewObject<UUcAudioAdjSubsystemHelperBase>(this, SubsystemHelperClass);

		if (SubsystemHelper)
		{
			// 初期化
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create SubsystemHelper"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UcAudioAdjSubsystemHelperClass is not set in the project settings"));
	}

	//// 各種サウンドクラスを生成
	// ここで処理を行うと、"SoundClassMasterがnull"のエラーが発生するのでコンストラクタに移動
	//BaseModifier			= GetDefault<UUcAudioAdjDeveloperSettings>()->SoundMixClass.LoadSynchronous();
	//SoundClassMaster	= GetDefault<UUcAudioAdjDeveloperSettings>()->SoundClassMaster.LoadSynchronous();
	//SoundClassMusic	= GetDefault<UUcAudioAdjDeveloperSettings>()->SoundClassMusic.LoadSynchronous();
	//SoundClassSFX		= GetDefault<UUcAudioAdjDeveloperSettings>()->SoundClassSFX.LoadSynchronous();
	//SoundClassVoice		= GetDefault<UUcAudioAdjDeveloperSettings>()->SoundClassVoice.LoadSynchronous();

	//VolumeCurrentMaster		= VolumeMaster	= SoundClassMaster->Properties.Volume;
	//VolumeCurrentMusic		= VolumeMusic	= SoundClassMusic->Properties.Volume;
	//VolumeCurrentSFX			= VolumeSFX		= SoundClassSFX->Properties.Volume;
	//VolumeCurrentVoice		= VolumeVoice	= SoundClassVoice->Properties.Volume;
}

void UUcAudioAdjSubsystem::Deinitialize()
{
	SubsystemHelper = nullptr;
	SubsystemHelperClass = nullptr;
	BaseModifier = nullptr;
	SoundClassMaster = nullptr;
	SoundClassMusic = nullptr;
	SoundClassSFX = nullptr;
	SoundClassVoice = nullptr;
	Super::Deinitialize();
}

USoundBase* UUcAudioAdjSubsystem::GetDecision()
{	
	return GetDefault<UUcAudioAdjDeveloperSettings>()->SFXDecision.LoadSynchronous();
}

USoundBase* UUcAudioAdjSubsystem::GetCancel()
{
	return GetDefault<UUcAudioAdjDeveloperSettings>()->SFXCancel.LoadSynchronous();
}

USoundBase* UUcAudioAdjSubsystem::GetCursor()
{
	return GetDefault<UUcAudioAdjDeveloperSettings>()->SFXCursor.LoadSynchronous();
}

USoundBase* UUcAudioAdjSubsystem::GetBuzzer()
{
	return GetDefault<UUcAudioAdjDeveloperSettings>()->SFXBuzzer.LoadSynchronous();
}

float UUcAudioAdjSubsystem::GetCurrentVolume(const ESoundCategoryId SoundClassId)
{
	if (SoundClassId == ESoundCategoryId::Master)
	{
		return VolumeCurrentMaster;
	}
	else if (SoundClassId == ESoundCategoryId::Music)
	{
		return VolumeCurrentMusic;
	}
	else if (SoundClassId == ESoundCategoryId::SFX)
	{
		return VolumeCurrentSFX;
	}
	else if (SoundClassId == ESoundCategoryId::Voice)
	{
		return VolumeCurrentVoice;
	}
	else
	{
		return 0.0f;
	}
}

float UUcAudioAdjSubsystem::GetVolume(const ESoundCategoryId SoundClassId)
{
	if (SoundClassId == ESoundCategoryId::Master)
	{
		return VolumeMaster;
	}
	else if (SoundClassId == ESoundCategoryId::Music)
	{
		return VolumeMusic;
	}
	else if (SoundClassId == ESoundCategoryId::SFX)
	{
		return VolumeSFX;
	}
	else if (SoundClassId == ESoundCategoryId::Voice)
	{
		return VolumeVoice;
	}
	else
	{
		return 0.0f;
	}
}

TArray<float> UUcAudioAdjSubsystem::SaveVolumeSettings()
{
	TArray<float> Temp = {};
	Temp.Emplace(VolumeMaster);
	Temp.Emplace(VolumeMusic);
	Temp.Emplace(VolumeSFX);
	Temp.Emplace(VolumeVoice);
	return Temp;
}

void UUcAudioAdjSubsystem::LoadVolumeSettings(const UObject* WorldContextObject, TArray<float> Volumes)
{
	if (Volumes.IsValidIndex(0)) {
		VolumeCurrentMaster = VolumeMaster = Volumes[0];
		SetMixVolume(WorldContextObject, ESoundCategoryId::Master, VolumeCurrentMaster);
	}
	if (Volumes.IsValidIndex(1)) {
		VolumeCurrentMusic = VolumeMusic = Volumes[1];
		SetMixVolume(WorldContextObject, ESoundCategoryId::Music, VolumeCurrentMusic);
	}
	if (Volumes.IsValidIndex(2)) {
		VolumeCurrentSFX = VolumeSFX = Volumes[2];
		SetMixVolume(WorldContextObject, ESoundCategoryId::SFX, VolumeCurrentSFX);
	}
	if (Volumes.IsValidIndex(3)) {
		VolumeCurrentVoice = VolumeVoice = Volumes[3];
		SetMixVolume(WorldContextObject, ESoundCategoryId::Voice, VolumeCurrentVoice);
	}
}

void UUcAudioAdjSubsystem::SetMixVolume(const UObject* WorldContextObject, const ESoundCategoryId SoundClassId, float Volume, float Pitch, float FadeInTime, bool bApplyToChildren)
{
	if (SoundClassId == ESoundCategoryId::Master)
	{
		UGameplayStatics::SetSoundMixClassOverride(WorldContextObject, BaseModifier, SoundClassMaster, Volume, Pitch, FadeInTime, bApplyToChildren);
		VolumeCurrentMaster = Volume;
	}
	else if (SoundClassId == ESoundCategoryId::Music)
	{
		UGameplayStatics::SetSoundMixClassOverride(WorldContextObject, BaseModifier, SoundClassMusic, Volume, Pitch, FadeInTime, bApplyToChildren);
		VolumeCurrentMusic = Volume;
	}
	else if (SoundClassId == ESoundCategoryId::SFX)
	{
		UGameplayStatics::SetSoundMixClassOverride(WorldContextObject, BaseModifier, SoundClassSFX, Volume, Pitch, FadeInTime, bApplyToChildren);
		VolumeCurrentSFX = Volume;
	}
	else if (SoundClassId == ESoundCategoryId::Voice)
	{
		UGameplayStatics::SetSoundMixClassOverride(WorldContextObject, BaseModifier, SoundClassVoice, Volume, Pitch, FadeInTime, bApplyToChildren);
		VolumeCurrentVoice = Volume;
	}
	else
	{

	}

	// 音量更新のため、ポップとプッシュを行う
	UGameplayStatics::PopSoundMixModifier(WorldContextObject, BaseModifier);
	UGameplayStatics::PushSoundMixModifier(WorldContextObject, BaseModifier);
}

TArray<ESoundCategoryId> UUcAudioAdjSubsystem::GetChangedSoundClassVolume()
{
	TArray<ESoundCategoryId> ChangedSoundClass = {};

	if (VolumeCurrentMaster != VolumeMaster) 
	{
		ChangedSoundClass.Add(ESoundCategoryId::Master);
	}
	if (VolumeCurrentMusic != VolumeMusic)
	{
		ChangedSoundClass.Add(ESoundCategoryId::Music);
	}
	if (VolumeCurrentSFX != VolumeSFX)
	{
		ChangedSoundClass.Add(ESoundCategoryId::SFX);
	}
	if (VolumeCurrentVoice != VolumeVoice)
	{
		ChangedSoundClass.Add(ESoundCategoryId::Voice);
	}
	return ChangedSoundClass;
}

bool UUcAudioAdjSubsystem::IsChangedSoundClassVolume()
{	
	return !(GetChangedSoundClassVolume().IsEmpty());
}

void UUcAudioAdjSubsystem::OverwriteSoundClassVolume(const ESoundCategoryId SoundClassId)
{
	if (SoundClassId == ESoundCategoryId::Master)
	{
		VolumeMaster = VolumeCurrentMaster;
	}
	else if (SoundClassId == ESoundCategoryId::Music)
	{
		VolumeMusic = VolumeCurrentMusic;
	}
	else if (SoundClassId == ESoundCategoryId::SFX)
	{
		VolumeSFX = VolumeCurrentSFX;
	}
	else if (SoundClassId == ESoundCategoryId::Voice)
	{
		VolumeVoice = VolumeCurrentVoice;
	}
	else
	{

	}
}
