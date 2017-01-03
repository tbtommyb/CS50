<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // render form
        render("sell_form.php", ["title" => "Choose a symbol"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if(empty($_POST["symbol"])) {
            apologize("You did not enter a symbol");
        }
        $symbol = $_POST["symbol"];
        $stock = lookup($symbol);
        $price = $stock["price"];
        $shares = CS50::query("SELECT shares FROM portfolios WHERE user_id = (?) AND symbol = (?)", $_SESSION["id"], $symbol)[0]["shares"];
        $new_balance = $cash + ($shares * $stock["price"]);
        
        if(0 == CS50::query("DELETE FROM portfolios WHERE user_id = (?) AND symbol = (?)", $_SESSION["id"], $symbol)) {
            apologize("There was a database error");
        }
        if(0 == CS50::query("UPDATE users SET cash = (?) WHERE id = (?)", $new_balance, $_SESSION["id"])) {
            apologize("Sorry, there was a database error.");
        }
        log_sell($symbol, $shares, $price);
        redirect("/index.php");
    }

?>