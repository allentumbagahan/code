const loginTextBox = document.getElementById("unameInput");
loginTextBox.addEventListener("keyup", function(event) {
    if (event.key === 'Enter') {
        signin()
    }
});

function checkAccountContext() {
    let requiresAccountList = [].slice.call(document.querySelectorAll('.requires-account'))
    let requiresNotAccountList = [].slice.call(document.querySelectorAll('.requires-not-account'))
    if (localStorage.getItem("username") === null) {
        let accountMenu = document.getElementById("accountMenu")
        accountMenu.innerText = "account";
        requiresNotAccountList.map(function (collEl) {
                collEl.classList.remove("collapse")
            }
        );
        requiresAccountList.map(function (remCollEl) {
                remCollEl.classList.add("collapse")
            }
        );
    } else {
        requiresAccountList.map(function (collEl) {
                collEl.classList.remove("collapse")
            }
        );
        requiresNotAccountList.map(function (remCollEl) {
                remCollEl.classList.add("collapse")
            }
        );
        let username = localStorage.getItem("username")
        let accountMenu = document.getElementById("accountMenu")
        accountMenu.innerText = username
        let menuNamePosters = document.querySelectorAll('.menuNamePoster')
        menuNamePosters.forEach(menuNamePoster => {
            menuNamePoster.value = username
        });
        let userNamePosters = document.querySelectorAll('.usernamePoster')
        userNamePosters.forEach(userNamePoster => {
           if (userNamePoster.value === "" || userNamePoster.value === null) {
               userNamePoster.value = username
           }
        });
    }
}

function setPagination() {
    let nextPages = document.querySelectorAll(".nextPage")
    nextPages.forEach(nextPage => {
        nextPage.value = (parseInt(nextPage.value)+1)
    });
    let prevPages = document.querySelectorAll(".prevPage")
    prevPages.forEach(prevPage => {
        prevPage.value = (parseInt(prevPage.value)-1)
    });
}