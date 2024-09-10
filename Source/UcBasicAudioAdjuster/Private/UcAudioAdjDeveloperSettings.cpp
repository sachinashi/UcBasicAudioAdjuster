// Fill out your copyright notice in the Description page of Project Settings.


#include "UcAudioAdjDeveloperSettings.h"
#include "UcAudioAdjSubsystem.h"
#include "UObject/ConstructorHelpers.h"

#define LOCTEXT_NAMESPACE "UcAudioAdjDeveloperSettings"

UUcAudioAdjDeveloperSettings::UUcAudioAdjDeveloperSettings()
{
	// デフォルトのヘルパーオブジェクトを生成（プラグインフォルダ内に用意してある前提）
	const wchar_t* DefaultHelperPath = TEXT("/UcBasicAudioAdjuster/HeplerBp/BP_UcAudioAdjSubsystemHelper.BP_UcAudioAdjSubsystemHelper_C");
	static ConstructorHelpers::FClassFinder<UUcAudioAdjSubsystemHelperBase> HelperClassFinder(DefaultHelperPath);
	if (HelperClassFinder.Succeeded())
	{
		UcAudioAdjSubsystemHelperClass = HelperClassFinder.Class;
	}

	// デフォルトの効果音を生成（プラグインフォルダ内に用意してある前提）
	const wchar_t* DefaultSFXDecision = TEXT("/UcBasicAudioAdjuster/BasicSFX/Decision.Decision");
	SFXDecision =TSoftObjectPtr<USoundBase>(FSoftObjectPath(DefaultSFXDecision));

	const wchar_t* DefaultSFXCancel = TEXT("/UcBasicAudioAdjuster/BasicSFX/Cancel.Cancel");
	SFXCancel = TSoftObjectPtr<USoundBase>(FSoftObjectPath(DefaultSFXCancel));

	const wchar_t* DefaultSFXCursor = TEXT("/UcBasicAudioAdjuster/BasicSFX/Cursor.Cursor");
	SFXCursor = TSoftObjectPtr<USoundBase>(FSoftObjectPath(DefaultSFXCursor));

	const wchar_t* DefaultSFXBuzzer = TEXT("/UcBasicAudioAdjuster/BasicSFX/Buzzer.Buzzer");
	SFXBuzzer = TSoftObjectPtr<USoundBase>(FSoftObjectPath(DefaultSFXBuzzer));

	// デフォルトのサウンドクラス類を作成（プラグインフォルダ内に用意してある前提）
	const wchar_t* DefaultSoundMixClass = TEXT("/UcBasicAudioAdjuster/AudioOption/Mix_UcBaseMix.Mix_UcBaseMix");
	SoundMixClass =TSoftObjectPtr<USoundMix>(FSoftObjectPath(DefaultSoundMixClass));

	const wchar_t* DefaultSoundClassMaster = TEXT("/UcBasicAudioAdjuster/AudioOption/UcMaster.UcMaster");
	SoundClassMaster =TSoftObjectPtr<USoundClass>(FSoftObjectPath(DefaultSoundClassMaster));

	const wchar_t* DefaultSoundClassMusic = TEXT("/UcBasicAudioAdjuster/AudioOption/UcMusic.UcMusic");
	SoundClassMusic =TSoftObjectPtr<USoundClass>(FSoftObjectPath(DefaultSoundClassMusic));

	const wchar_t* DefaultSoundClassSFX = TEXT("/UcBasicAudioAdjuster/AudioOption/UcSFX.UcSFX");
	SoundClassSFX =TSoftObjectPtr<USoundClass>(FSoftObjectPath(DefaultSoundClassSFX));

	const wchar_t* DefaultSoundClassVoice = TEXT("/UcBasicAudioAdjuster/AudioOption/UcVoice.UcVoice");
	SoundClassVoice =TSoftObjectPtr<USoundClass>(FSoftObjectPath(DefaultSoundClassVoice));
}

FName UUcAudioAdjDeveloperSettings::GetContainerName() const
{
	return Super::GetContainerName();
}
FName UUcAudioAdjDeveloperSettings::GetCategoryName() const
{
	return "Plugins";
}
FName UUcAudioAdjDeveloperSettings::GetSectionName() const
{
	return Super::GetSectionName();
}

#if WITH_EDITOR
FText UUcAudioAdjDeveloperSettings::GetSectionText() const
{
	return LOCTEXT("UUcAudioAdjDeveloperSettings::GetSectionText", "UcBasicAudioSetting");
}
FText UUcAudioAdjDeveloperSettings::GetSectionDescription() const
{
	return LOCTEXT("UUcAudioAdjDeveloperSettings::GetSectionDescription", "BasicAudioSetting");
}
#endif

#undef LOCTEXT_NAMESPACE