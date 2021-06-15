const nowTime = document.querySelector("#nowTime");

function getTime() {
  const Today = new Date();
  const hours = Today.getHours();
  const minutes = Today.getMinutes();
  const seconds = Today.getSeconds();

  nowTime.innerText = `${hours < 10 ? `0${hours}` : `${hours}`}:${
    minutes < 10 ? `0${minutes}` : `${minutes}`
  }:${seconds < 10 ? `0${seconds}` : `${seconds}`}`;
}

function init() {
  getTime();
  setInterval(getTime, 1000);
}

init();
