#pragma once

UENUM(BlueprintType)
enum class ECharacterState: uint8
{
	ECS_Unequipped = 0 UMETA(DisplayName = "Unequipped"),
	ECS_EquippedOneHandedWeapon = 1 UMETA(DisplayName = "Equipped One-Handed Weapon"),
	ECS_EquippedTwoHandedWeapon = 2 UMETA(DisplayName = "Equipped Two-Handed Weapon"),
};

UENUM(BlueprintType)
enum class EActionState: uint8
{
	EAS_Unoccupied = 0 UMETA(DisplayName = "Unoccupied"),
	EAS_Attacking = 1 UMETA(DisplayName = "Attacking"),
	EAS_Equipping = 2 UMETA(DisplayName = "Equipping"),
};
