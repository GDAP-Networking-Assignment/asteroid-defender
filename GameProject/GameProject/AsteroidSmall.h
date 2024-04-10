#pragma once
class AsteroidSmall : public Asteroid {

   DECLARE_DYNAMIC_DERIVED_CLASS(AsteroidSmall, Asteroid)

public:
    void Initialize() override;
    void Update() override;
};