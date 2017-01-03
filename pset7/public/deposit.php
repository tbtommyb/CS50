<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // render form
        render("deposit_form.php", ["title" => "Deposit cash"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $deposit = $_POST["deposit"];
        if(empty($deposit)) {
            apologize("You did not enter a deposit value");
        }
        $cash = CS50::query("SELECT cash FROM users WHERE id = (?)", $_SESSION["id"])[0]["cash"];
        $new_balance = $cash + $deposit;
    
        if(0 == CS50::query("UPDATE users SET cash = (?) WHERE id = (?)", $new_balance, $_SESSION["id"])) {
            apologize("Sorry, there was a database error.");
        }
        redirect("/index.php");
    }

?>