plugins {
  id("com.android.application")
  id("kotlin-android")
}

android {
  namespace = "dev.trindadedev.rpg"
  compileSdk = 35

  defaultConfig {
    applicationId = "dev.trindadedev.rpg"
    minSdk = 21
    targetSdk = 35
    versionCode = 1
    versionName = "1.0"
        
    vectorDrawables.useSupportLibrary = true

    ndk {
      abiFilters += listOf("armeabi-v7a", "arm64-v8a", "x86", "x86_64")
    }

    externalNativeBuild {
      cmake {
        arguments += listOf("-DANDROID_PLATFORM=android-19", "-DANDROID_STL=c++_shared")
        cppFlags += "-std=c++17"
      }
    }
  }

  externalNativeBuild {
    cmake {
      path = file("src/main/cpp/CMakeLists.txt")
    }
  }

  compileOptions {
    sourceCompatibility = JavaVersion.VERSION_21
    targetCompatibility = JavaVersion.VERSION_21
  }

  signingConfigs {
    create("release") {
      // temporary keystore
      storeFile = file(layout.buildDirectory.dir("../release_key.jks"))
      storePassword = "release_temp"
      keyAlias = "release_temp"
      keyPassword = "release_temp"
    }
    getByName("debug") {
      storeFile = file(layout.buildDirectory.dir("../testkey.keystore"))
      storePassword = "testkey"
      keyAlias = "testkey"
      keyPassword = "testkey"
    }
  }

  buildTypes {
    release {
      isMinifyEnabled = true
      proguardFiles(getDefaultProguardFile("proguard-android-optimize.txt"), "proguard-rules.pro")
      signingConfig = signingConfigs.getByName("release")
    }
  }

  buildFeatures {
    viewBinding = true
    prefab = true
  }
}

tasks.withType<org.jetbrains.kotlin.gradle.tasks.KotlinCompile>().configureEach {
  kotlinOptions.jvmTarget = "21"
}

dependencies {
  implementation(files("libs/sdl.aar"))  // sdl3 (3.2.8)
}