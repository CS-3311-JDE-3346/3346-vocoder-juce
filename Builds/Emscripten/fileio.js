const modulatorSelect = document.querySelector("#modulatorSelect");
const carrierSelect = document.querySelector("#carrierSelect");
const modulatorFileInput = document.querySelector("#modulator");
const carrierFileInput = document.querySelector("#carrier");
const runButton = document.querySelector("#runVocoder");
const downloadButton = document.querySelector("#downloadOutput");

Module.onRuntimeInitialized = () => {
    init();
    carrierFileInput.disabled = false;
    modulatorFileInput.disabled = false;
    runButton.disabled = false;
};

function init() {
    runButton.addEventListener("click", (e) => {
        console.log("Running vocoder");
    });
    downloadButton.addEventListener("click", (e) => {
        console.log("Downloading output");
    });
}

