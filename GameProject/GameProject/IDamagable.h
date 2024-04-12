#pragma once
class IDamageable  : public Component{
DECLARE_DYNAMIC_DERIVED_CLASS(IDamageable, Component)
public:
    virtual ~IDamageable() = default;
    virtual void TakeDamage(int damage) = 0;
};