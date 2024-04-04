
#include "Engine/DataTable.h"
#include "SkillData.generated.h"

UENUM(BlueprintType)
enum class ERequireWeaponType : uint8
{
	Empty, // 空手（默认）
	Blade, // 剑
	Axe, // 斧
	// ...其他武器类型
};

UENUM(BlueprintType)
enum class ESkillAttribute : uint8
{
	Physical, // 物理（默认）
	Fire, // 火焰
	Ice, // 冰霜
	//...其他攻击属性
};

UENUM(BlueprintType)
enum class ESkillEffect : uint8
{
	None, // 无 （默认）
	Stun, // 眩晕
	KnockBack, // 击退
	Bleed, // 流血
	//...其他攻击效果
};

USTRUCT(BlueprintType)
struct FSkillData : public FTableRowBase
{
	GENERATED_BODY()

	// 唯一ID，用于在DataTable中查找项目
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	FName SkillId;

	// 技能名称
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	FText SkillName;

	// 技能描述
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	FText SkillDescription;

	// 技能图标
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	UTexture2D* SkillIcon;

	// 需要武器类型
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	ERequireWeaponType RequireWeaponType;

	// 技能属性
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	ESkillAttribute SkillAttribute;

	// 技能效果
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	ESkillEffect SkillEffect;
};

