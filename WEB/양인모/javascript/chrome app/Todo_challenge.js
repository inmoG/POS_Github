const toDoForm = document.querySelector(".js-toDoForm"),
  toDoInput = toDoForm.querySelector("input"),
  pendingList = document.querySelector(".js-PendingList"),
  finishedList = document.querySelector(".js-FinishedList");

const PENDING_KEY = "PENDING";
const FINISHED_KEY = "FINISHED";
let ToDos = []; // localStorage Array
let finToDos = [];

// Pending function
function load_Pen_ToDos() {
  const loadedToDos = localStorage.getItem(PENDING_KEY);
  if (loadedToDos !== null) {
    const parsedToDos = JSON.parse(loadedToDos); //current loadedToDos is string so must change Object
    parsedToDos.forEach(function(todo) {
      paint_Pen_ToDo(todo.text);
    });
  }
}

function clean_Pending_ToDos(li) {
  const cleanToDos = ToDos.filter(function(ToDo) {
    return ToDo.id !== parseInt(li.id);
  }); //cleanToDos is Array
  ToDos = cleanToDos;
}

function savePending() {
  localStorage.setItem(PENDING_KEY, JSON.stringify(ToDos));
}

function deleted_Pen_ToDo(event) {
  const btn = event.target;
  const li = btn.parentNode;
  pendingList.removeChild(li);
  clean_Pending_ToDos(li);
  savePending();
}

function paint_Pen_ToDo(text) {
  // paint pending todos
  const li = document.createElement("li");
  const span = document.createElement("span");
  const delBtn = document.createElement("button");
  const finBtn = document.createElement("button");
  span.innerText = text;
  delBtn.innerHTML = "❌";
  finBtn.innerHTML = "✔";
  li.appendChild(span);
  li.appendChild(delBtn);
  li.appendChild(finBtn);
  pendingList.appendChild(li);
  delBtn.addEventListener("click", deleted_Pen_ToDo);
  finBtn.addEventListener("click", Create_Fin_ToDo);

  const newId = ToDos.length + 1;
  li.id = newId;
  const ToDoObj = {
    text: text,
    id: newId
  };
  ToDos.push(ToDoObj);
  savePending();
}

// finished function
function restore_Fin_Btn(event) {
  // create restore_Fin_Btn when restore finish restore button click
  const reBtn = event.target;
  let li = reBtn.parentNode;
  finishedList.removeChild(li);

  finToDos.filter(function(ToDo) {
    if (ToDo.id === parseInt(li.id)) {
      paint_Pen_ToDo(ToDo.text);
    }

    const finished_Del_ToDos = finToDos.filter(function(ToDo) {
      return ToDo.id !== parseInt(li.id);
    });
    finToDos = finished_Del_ToDos;
    saveFinished();
  });
}

function deleted_Fin_Btn(event) {
  // create deleted_Fin_Btn when finish deleted button click
  const delBtn = event.target;
  let li = delBtn.parentNode;
  finishedList.removeChild(li); //삭제 선택한 걸 finToDos에서 삭제

  const finished_ToDos = finToDos.filter(function(ToDo) {
    return ToDo.id !== parseInt(li.id);
  });
  finToDos = finished_ToDos;
  saveFinished();
}

function load_Fin_ToDos() {
  // load finished ToDos when refresh
  const loaded_Fin_ToDos = localStorage.getItem(FINISHED_KEY);
  if (loaded_Fin_ToDos !== null) {
    const parsed_Fin_ToDos = JSON.parse(loaded_Fin_ToDos); //current loadedToDos is string so must change Object
    parsed_Fin_ToDos.forEach(function(todo) {
      paint_Fin_ToDos(todo.text, todo.id);
      finObj = {
        text: todo.text,
        id: todo.id
      };
      finToDos.push(finObj);
    });
  }
}

function paint_Fin_ToDos(text, id) {
  // paint finished ToDos
  li = document.createElement("li");
  const span = document.createElement("span");
  const delBtn = document.createElement("button");
  const reBtn = document.createElement("button");
  span.innerText = text;
  delBtn.innerHTML = "❌";
  reBtn.innerHTML = "🔙";
  li.appendChild(span);
  li.appendChild(delBtn);
  li.appendChild(reBtn);
  finishedList.appendChild(li);
  li.id = id;
  delBtn.addEventListener("click", deleted_Fin_Btn);
  reBtn.addEventListener("click", restore_Fin_Btn);
}

function Create_Fin_ToDo(event) {
  // create finished list Array
  const newId = finToDos.length + 1;
  const finBtn = event.target;
  let li = finBtn.parentNode;
  let text;
  pendingList.removeChild(li);

  const finished_ToDos = ToDos.filter(function(ToDo) {
    return ToDo.id === parseInt(li.id);
  });

  finished_ToDos.forEach(function(ToDo) {
    text = ToDo.text;
  });

  finObj = {
    text: text,
    id: newId
  };
  finToDos.push(finObj);

  clean_Pending_ToDos(li);
  savePending();
  paint_Fin_ToDos(text, newId);
  saveFinished();
}

function saveFinished() {
  // save finished list localStorage
  localStorage.setItem(FINISHED_KEY, JSON.stringify(finToDos));
}

// common function
function handleSubmit(event) {
  event.preventDefault(); //event prevent behavior
  const currentValue = toDoInput.value;
  paint_Pen_ToDo(currentValue);
  toDoInput.value = ""; //인풋 영역을 비워주는 용도
}

function loadToDos() {
  // call loadToDos when refresh
  load_Pen_ToDos();
  load_Fin_ToDos();
}

function init() {
  loadToDos();
  toDoForm.addEventListener("submit", handleSubmit);
}

init();
