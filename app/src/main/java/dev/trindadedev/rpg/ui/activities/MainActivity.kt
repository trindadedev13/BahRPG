package dev.trindadedev.rpg.ui.activities

import org.libsdl.app.SDLActivity

class MainActivity : SDLActivity() {

  /**
   * This method is called by SDL before loading the native shared libraries.
   * It can be overridden to provide names of shared libraries to be loaded.
   * The default implementation returns the defaults. It never returns null.
   * An array returned by a new implementation must at least contain "SDL2".
   * Also keep in mind that the order the libraries are loaded may matter.
   *
   * @return names of shared libraries to be loaded (e.g. "SDL2", "main").
   */
  override fun getLibraries(): Array<String> {
    return arrayOf(
        "SDL2",
        "SDL2_image",
        "rpg"
    )
  }
}