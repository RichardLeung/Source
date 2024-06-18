// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGAttributeInfo.h"

FRPGAttributesInfo URPGAttributeInfo::FindAttributeInfo(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	// 便利所有属性信息，找到匹配的属性信息
	for (const FRPGAttributesInfo& AttributeInfo : AttributesInfomation)
	{
		if (AttributeInfo.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return AttributeInfo;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attribute %s not found in %s"), *AttributeTag.ToString(), *GetName());
	}

	return FRPGAttributesInfo();
}
