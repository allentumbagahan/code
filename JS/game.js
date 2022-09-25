function signin() {
    try {
        let username = document.getElementById("unameInput").value;
        hive_keychain.requestHandshake(finishSignin(username));
        //account-menu, login-box
    }
    catch (err) {
        console.log("keychain not installed")
        //show modal with link to keychain website or "new to hive" info page
    }
}

function finishSignin(username) {
    try {
        hive_keychain.requestSignBuffer(
            username,
            "Log In",
            "Posting",
            function (response) {
                if (response.error) {
                    console.log(response.error)
                    //show modal/toast
                } else {
                    let username = response.data.username
                    console.log(response.data)
                    localStorage.setItem('username', username);
                    checkAccountContext();
                }
            }
        );
    }
    catch (e) {
        console.log(e)
    }
}

function signout() {
    localStorage.removeItem('username');
    checkAccountContext();
}
