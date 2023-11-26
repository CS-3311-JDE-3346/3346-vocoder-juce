const modulatorFile = document.querySelector("#modulator");
const carrierFile = document.querySelector("#carrier");

function uploadSoundFile(fileInput) {
    console.log(fileInput.files[0]);
}

modulatorFile.addEventListener("change", () => {
    uploadSoundFile(modulatorFile);
});

carrierFile.addEventListener("change", () => {
    uploadSoundFile(carrierFile);
});