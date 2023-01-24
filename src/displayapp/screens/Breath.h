#pragma once

#include "systemtask/SystemTask.h"
#include "components/brightness/BrightnessController.h"
#include "components/motor/MotorController.h"
#include "displayapp/screens/Screen.h"
#include <lvgl/lvgl.h>

namespace Pinetime {
  namespace Applications {
    namespace Screens {
      class Breath : public Screen {
      public:
        Breath(DisplayApp* app, Controllers::MotorController& motorController, System::SystemTask& systemTask, Controllers::BrightnessController& brightnessController);
        ~Breath() override;
        void Refresh() override;

      private:
        TickType_t startTime = 0;
        int16_t bpm = 12;
        int16_t duration = 25;

        Controllers::MotorController& motorController;
        System::SystemTask& systemTask;
        Controllers::BrightnessController& brightnessController;

        lv_task_t* taskRefresh;
      };
    }
  }
}