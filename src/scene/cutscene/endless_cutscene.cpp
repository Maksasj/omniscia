#include "endless_cutscene.h"

omniscia::core::EndlessCutscene::EndlessCutscene(const std::initializer_list<CE_StepObject> &steps) : Cutscene(steps) {

}

void omniscia::core::EndlessCutscene::update() {
    if(!_started)
        return;

    if(_ended)
        return;

    if(_currentStep >= _steps.end()) {
        _ended = true;
        start();
        return;
    }

    CE_Step& currentStep = *_currentStep;

    currentStep.execute();

    if(currentStep.is_done())
        ++_currentStep;
}
