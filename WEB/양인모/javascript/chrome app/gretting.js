const form = document.querySelector('.js-form'),
    input = form.querySelector('input'),
    gretting = document.querySelector('.js-grettings');
// local stroage = 작은 자바스크립트 정보를 유저 컴퓨터에 저장하는 방식

const USER_NAME_LS = 'USER_NAME', // localStorage.key
    SHOWING_CN = 'showing'; //showing css

function saveUserName(text)
{
    localStorage.setItem(USER_NAME_LS, text); // 9번 Key, Value
}    

function handleSubmmit(event)
{
    event.preventDefault(); //이벤트의 동작을 막는 것 즉 submit하지 못하게 한다.
    const currentValue = input.value;
    //form의 submit이벤트가 발생하면 root즉 document까지 이벤트가 올라가 다른 곳으로 간다.
    //예시 : submit하면 입력 데이터가 서버로 가는 과정같은 것
    //event의 이 기본적인 과정을 막기위해 prevent.default()함수를 사용한다. 
    paintGreeting(currentValue); //6번
    saveUserName(currentValue); //7번
}
function askForUser()
{
    form.classList.add(SHOWING_CN); //css : form display on block
    form.addEventListener('submit', handleSubmmit); //5번
}

function paintGreeting(username) // username ? paintGreeting and remove form :   
{//8번
    form.classList.remove(SHOWING_CN); // form display off block
    gretting.classList.add(SHOWING_CN); // form display on block
    gretting.innerText = `Hello ${username}`;
}

function loadUserName()
{
    const userName = localStorage.getItem(USER_NAME_LS); //3번
    
    if (userName === null)
    {
        //enter country
        // country is not
        askForUser(); //4번
    }
    else
    {
        // country is
        paintGreeting(userName);
    }
}

function init()
{
    loadUserName(); //2번
}

init(); // 1번