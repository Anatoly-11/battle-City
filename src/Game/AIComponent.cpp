#include "AIComponent.h"
#include "GameObjects/Tank.h"

AIComponent::AIComponent(Tank *pParentTank) noexcept : m_pParentTank(pParentTank) {

}

void AIComponent::update(const double delta) noexcept {
	m_pParentTank->fire();
}