
  All values not listed are unused
  Preference change: 
    {
      typeOfUpdate = TypeOfUpdate::PreferenceChange, 
      val1 = index of scene to modify preferences of,
      val2 = index of preference to modify,
      val3 = new value of preference
    }
  Scene change:
    {
      typeOfUpdate = TypeOfUpdate::SceneChange,
      val1 = new index of scene,
    }
  Brightness change:
    {
      typeOfUpdate = TypeOfUpdate::BrightnessChange,
      val1 = new brightness,
    }
  Scene get:
    {
      typeOfUpdate = TypeOfUpdate::SceneGet,
      val1 = index of scene to get
    }
  Scene inform:
    {
      typeOfUpdate = TypeOfUpdate::SceneInform,
      stringVal = name of indexed scene
      val1 = index of scene
      val2 = number of preferences in scene
    }
  Preference get:
    {
      typeOfUpdate = TypeOfUpdate::PreferenceGet,
      val1 = index of scene
      val2 = index of preference of scene
    }
  Preference inform:
    {
      typeOfUpdate = TypeOfUpdate::PreferenceInform,
      stringVal = name of preference
      val1 = index of scene
      val2 = index of preference of scene
      val3 = current value of preference
      val4 = minimum value of preference
      val5 = maximum value of preference
    }
  Status: // note: status can be sent from either remote or display, but display shouldn't read any of the sent status and should send back one
    {
      typeOfUpdate = TypeOfUpdate::Status
      val1 = index of scene
      val2 = brightness
      val3 = number of scenes
      boolVal = true if the strip is off
    }