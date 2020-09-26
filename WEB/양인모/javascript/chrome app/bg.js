const body = document.querySelector('body');
const IMG_NUMBER = 4;

/*
function handleImgLoad()
{
    console.log('finished loading');
}*/

function paintImage(imgNumber) {
    const image = new Image();
    image.src = `D:\Study\Coding\WebProject\nomad_coder\VanillaJS\chrome app\Images\${imgNumber + 1}.jpg`;
    image.classList.add('bgImage');
    body.prepend(image);
    //image.addEventListener('loadend', handleImgLoad);
}

function genRandom() {
    const number = Math.floor(Math.random() * IMG_NUMBER);
    return number;
}

function init() {
    //math.cell() 반올림 math.floor() 소수점 버리기
    const randomNumber = genRandom();
    paintImage(randomNumber);
}

init();