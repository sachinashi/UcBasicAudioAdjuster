// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Sound/SoundMix.h"
#include "Sound/SoundBase.h"
#include "UcAudioAdjDeveloperSettings.generated.h"

class UUcAudioAdjSubsystemHelperBase;

/**
 * 
 */
UCLASS(config = Game, defaultconfig)
class UCBASICAUDIOADJUSTER_API UUcAudioAdjDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UUcAudioAdjDeveloperSettings();

public:
	///** Gets the settings container name for the settings, either Project or Editor */
	virtual FName GetContainerName() const override;
	/** Gets the category for the settings, some high level grouping like, Editor, Engine, Game...etc. */
	virtual FName GetCategoryName() const override;
	/** The unique name for your section of settings, uses the class's FName. */
	virtual FName GetSectionName() const override;

#if WITH_EDITOR
	/** Gets the section text, uses the classes DisplayName by default. */
	virtual FText GetSectionText() const override;
	/** Gets the description for the section, uses the classes ToolTip by default. */
	virtual FText GetSectionDescription() const override;
#endif

public:
	// ヘルパーオブジェクト
	UPROPERTY(EditAnywhere, config, Category = "Helper", meta = (AllowAbstract = "false"))
	TSubclassOf<class UUcAudioAdjSubsystemHelperBase> UcAudioAdjSubsystemHelperClass;

	// 基本効果音：決定
	UPROPERTY(EditAnywhere, config, Category = "SFX")
	TSoftObjectPtr<USoundBase> SFXDecision;

	// 基本効果音：キャンセル
	UPROPERTY(EditAnywhere, config, Category = "SFX")
	TSoftObjectPtr<USoundBase> SFXCancel;
	
	// 基本効果音：カーソル
	UPROPERTY(EditAnywhere, config, Category = "SFX")
	TSoftObjectPtr<USoundBase> SFXCursor;

	// 基本効果音：ブザー
	UPROPERTY(EditAnywhere, config, Category = "SFX")
	TSoftObjectPtr<USoundBase> SFXBuzzer;

	// 基本サウンドミックスクラス（マスター、音楽、効果音、声のサウンドクラスを所有する）
	UPROPERTY(EditAnywhere, BlueprintReadOnly, config, Category = "SoundClasses")
	TSoftObjectPtr<USoundMix> SoundMixClass;

	// 基本サウンドクラス：マスター
	UPROPERTY(EditAnywhere, BlueprintReadOnly, config, Category = "SoundClasses")
	TSoftObjectPtr<USoundClass> SoundClassMaster;

	// 基本サウンドクラス：音楽
	UPROPERTY(EditAnywhere, BlueprintReadOnly, config, Category = "SoundClasses")
	TSoftObjectPtr<USoundClass> SoundClassMusic;

	// 基本サウンドクラス：効果音
	UPROPERTY(EditAnywhere, BlueprintReadOnly, config, Category = "SoundClasses")
	TSoftObjectPtr<USoundClass> SoundClassSFX;

	// 基本サウンドクラス：声
	UPROPERTY(EditAnywhere, BlueprintReadOnly, config, Category = "SoundClasses")
	TSoftObjectPtr<USoundClass> SoundClassVoice;
};
