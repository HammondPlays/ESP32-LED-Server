// This file contains the JavaScript code for the frontend application.
// It handles user interactions, manipulates the DOM, and implements the application's logic.

// Cache the animation-types response so we don't refetch it every time.
let animationTypesCache = null;
const host = window.location.origin;

document.addEventListener("DOMContentLoaded", async () => {
  const powerSwitch = document.getElementById("powerSwitch");
  const brightnessInput = document.getElementById("brightnessInput");
  const animationRadioButtons = document.getElementsByName(
    "animationModeContainer"
  );

  await fetchAnimationTypes();
  generateAnimationContainer();
  updateCurrentAnimationParameters();
  displayBrightness(brightnessInput);
  updateLedPower(powerSwitch);

});

powerSwitch.addEventListener("change", () => {
  powerSwitch.textContent = powerSwitch.checked ? "On" : "Off";

  fetch(host + "/led", {
    method: "PUT",
    headers: {
      "Content-Type": "application/json",
    },
    body: JSON.stringify({ value: powerSwitch.checked }),
  });
});

document.getElementById("animationSubmit").addEventListener("click", function () {
  const selectedRadioButton = document.querySelector('input[name="animation"]:checked');
  if (selectedRadioButton) {
    console.log("Selected animation mode:", selectedRadioButton.value);
  } else {
    console.error("No animation mode is selected.");
  }

  const color = document.getElementById("colorInput").value;
  const speed = document.getElementById("speedInput").value;
  //const mode = document.querySelector('input[name="mode"]:checked').value;
  fetch(host + "/animations", {
    method: "PUT",
    headers: {
      "Content-Type": "application/json",
    },
    body: JSON.stringify({ animation: selectedRadioButton.value, color: color, speed: speed }),
  })
    .then((response) => response.json())
    .then((data) => {
      console.log("Success:", data);
    })
    .catch((error) => {
      console.error("Error:", error);
    });
});

document.getElementById("brightnessInput")
  .addEventListener("change", function () {
    const brightnessValue = this.value;
    fetch(host + "/brightness", {
      method: "PUT",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify({ brightness: brightnessValue }),
    });
  });

document.getElementById("speedInput").addEventListener("input", function () {
  const speedValue = this.value;
  document.getElementById("speedValue").textContent = speedValue;
});

document.getElementById("animationsContainer")
  .addEventListener("change", function () {
    const selectedMode = document.querySelector('input[name="animation"]:checked').value;
    console.log("Animation mode changed!" + selectedMode);

    displaySelectedAnimationParameters(selectedMode);
  });

function generateAnimationContainer() {
  if (!animationTypesCache) {
    console.error("Animation types cache is not available.");
    return;
  }

  const modeContainer = document.getElementById("animationsContainer");
  Object.keys(animationTypesCache).forEach((mode) => {
    const label = document.createElement("label");
    const input = document.createElement("input");
    input.type = "radio";
    input.name = "animation";
    input.value = mode;
    input.id = mode;
    label.textContent = animationTypesCache[mode].name;
    label.htmlFor = mode;
    modeContainer.appendChild(input);
    modeContainer.appendChild(label);
  });

}

function displaySelectedAnimationParameters(selectedAnimation) {
  if (!animationTypesCache) {
    console.error("Animation types cache is not available.");
    return;
  }

  const selectedAnimationParameters = animationTypesCache[selectedAnimation].parameters;

  Array.from(document.getElementById("animationParameters").children).forEach((param) => {
    if (selectedAnimationParameters.includes(param.id)) {
      param.style.display = "block";
    } else {
      param.style.display = "none";
    }
  });
}

function updateCurrentAnimationParameters() {
  fetchCurrentAnimation()
    .then((data) => {
      const animationId = Object.keys(data)[0];
      const selectedRadioButton = document.getElementById(animationId);
      selectedRadioButton.checked = true;

      const animationParameters = data[animationId];
      console.log("Current animation parameters:", animationParameters);

      for (const key in animationParameters) {
        if (animationParameters.hasOwnProperty(key)) {
          const paramDisplay = document.getElementById(key.toUpperCase());
          const paramInput = document.getElementById(key + "Input");
          const paramValue = document.getElementById(key + "Value");
          paramDisplay.style.display = "block";
          paramInput.value = animationParameters[key];
          if (paramValue) {
            paramValue.textContent = animationParameters[key];
          }
        }
      }
    });
}

function displayBrightness(brightnessInput) {
  fetchBrightness()
    .then((data) => (brightnessInput.value = data.brightness));
}

function updateLedPower(powerSwitch) {
  fetchLedPower()
    .then((data) => (powerSwitch.checked = data.value));
}

async function fetchAnimationTypes() {
  try {
    const response = await fetch(host + "/animation-types");
    const data = await response.json();

    animationTypesCache = data;
    console.log("Animation types:", data);

    return data;
  } catch (error) {
    console.error("Error:", error);
    throw error;
  }
}

function fetchBrightness() {
  return fetch(host + "/brightness", {
    method: "GET",
  })
    .then((response) => response.json());
}

function fetchLedPower() {
  return fetch(host + "/led", {
    method: "GET",
  })
    .then((response) => response.json());
}

function fetchCurrentAnimation() {
  return fetch(host + "/animations", {
    method: "GET",
  })
    .then((response) => response.json());
}
