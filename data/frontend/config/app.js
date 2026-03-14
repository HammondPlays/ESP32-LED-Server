// This file contains the JavaScript code for the frontend application.
// It handles user interactions, manipulates the DOM, and implements the application's logic.

document.addEventListener("DOMContentLoaded", () => {
  const ledModeRadioButtons = document.getElementsByName(
    "ledModeContainer"
  );

  const host = window.location.origin;
});


document.getElementById("ledModeSubmit").addEventListener("click", function () {
  const host = window.location.origin;
  const selectedRadioButton = document.querySelector('input[name="ledMode"]:checked');
  if (selectedRadioButton) {
    console.log("Selected led mode:", selectedRadioButton.value);
  } else {
    console.error("No led mode is selected.");
  }

  const ledCount = document.getElementById("ledCountInput").value;
  //const mode = document.querySelector('input[name="mode"]:checked').value;
  fetch(host + "/led-mode", {
    method: "PUT",
    headers: {
      "Content-Type": "application/json",
    },
    body: JSON.stringify({ ledMode: selectedRadioButton.value, ledCount: ledCount }),
  })
    .then((response) => response.json())
    .then((data) => {
      console.log("Success:", data);
    })
    .catch((error) => {
      console.error("Error:", error);
    });
});

document.getElementById("ledCountInput").addEventListener("input", function () {
  const ledCountValue = this.value;
  document.getElementById("ledCountValue").textContent = ledCountValue;
});

document.getElementById("ledModeContainer")
  .addEventListener("change", function () {
    const selectedMode = document.querySelector('input[name="ledMode"]:checked').value;
    console.log("LED mode changed!" + selectedMode);

    const host = window.location.origin;

    fetch(host + "/led-modes", {
      method: "GET",
    })
      .then((response) => response.json())
      .then((data) => {
        currentAnimationParameters = data[selectedMode].parameters;

        Array.from(document.getElementById("ledModeParameters").children).forEach((param) => {
          if (currentAnimationParameters.includes(param.id)) {
            param.style.display = "block";
          } else {
            param.style.display = "none";
          }
        });
      })
      .catch((error) => {
        console.error("Error:", error);
      });
  });

function fetchModes() {
  const host = window.location.origin;
  fetch(host + "/led-modes", {
    method: "GET",
  })
    .then((response) => response.json())
    .then((data) => {
      console.log(data);
      const modeContainer = document.getElementById("ledModeContainer");
      Object.keys(data).forEach((mode) => {
        const label = document.createElement("label");
        const input = document.createElement("input");
        input.type = "radio";
        input.name = "ledMode";
        input.value = mode;
        input.id = mode;
        label.textContent = data[mode].name;
        label.htmlFor = mode;
        modeContainer.appendChild(input);
        modeContainer.appendChild(label);
      });
    })
    .catch((error) => {
      console.error("Error:", error);
    });

  fetch(host + "/led-mode", {
    method: "GET",
  })
    .then((response) => response.json())
    .then((data) => {
      const ledModeId = Object.keys(data)[0];
      const selectedRadioButton = document.getElementById(ledModeId);
      selectedRadioButton.checked = true;

      const ledModeParameters = data[ledModeId].parameters;
      ledModeParameters.forEach((param) => {
        document.getElementById(param).style.display = "block";
      });
    });
}

// Fetch modes on page load
document.addEventListener("DOMContentLoaded", fetchModes);
