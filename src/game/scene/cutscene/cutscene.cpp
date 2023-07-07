#include "cutscene.h"

omniscia::core::Cutscene::Cutscene() {}
omniscia::core::Cutscene::Cutscene(const Cutscene&) {}

omniscia::core::Cutscene::Cutscene(const std::initializer_list<CE_StepObject> &steps) : _ended(false), _started(false) {
    for(const CE_StepObject& objectStep : steps) {
        for(const auto& step : objectStep._steps) {
            _steps.push_back(step);
        }
    }

    for(auto& step : _steps) {
        step.bind_cutscene_data_pool(_cutsceneDataPool);
    }

    _started = 0;
    _currentStep = _steps.begin();
}

void omniscia::core::Cutscene::free() {
    _steps.clear();
    _cutsceneDataPool.clear();
}

void omniscia::core::Cutscene::start() {
    _started = true;
    _ended = false;
    _currentStep = _steps.begin();

    for(auto& step : _steps)
        step.reset();
}

bool omniscia::core::Cutscene::is_ended() const {
    return _ended;
}

void omniscia::core::Cutscene::update() {
    if(!_started)
        return;

    if(_ended)
        return;

    if(_currentStep == _steps.end()) {
        _ended = true;
        return;
    }

    CE_Step& currentStep = *_currentStep;

    currentStep.execute();

    if(currentStep.is_done())
        ++_currentStep;
}

bool omniscia::core::ended_cutscene_predicate(omniscia::core::Cutscene const* cutscene) {
    if(cutscene == nullptr) return true;

    return cutscene->is_ended(); 
}