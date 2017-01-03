<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // render form
        render("buy_form.php", ["title" => "Choose a symbol"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $symbol = $_POST["symbol"];
        $shares = $_POST["shares"];
        if(empty($symbol)) {
            apologize("You did not enter a symbol");
        }
        if(empty($shares) || !preg_match("/^\d+$/", $shares)) {
            apologize("You did not enter a valid number of shares");
        }
        $stock = lookup($symbol);
        if(!$stock) {
            apologize("You entered an invalid symbol");
        }
        $cash = CS50::query("SELECT cash FROM users WHERE id = (?)", $_SESSION["id"])[0]["cash"];
        if(($stock["price"] * $shares) > $cash) {
            apologize("You don't have enough cash to buy that many :(.");
        }
        $new_balance = $cash - ($shares * $stock["price"]);
    
        if(0 == CS50::query("INSERT INTO portfolios (user_id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)",
            $_SESSION["id"], strtoupper($symbol), $shares)) {
                apologize("Sorry, there was a database error.");
            }
        if(0 == CS50::query("UPDATE users SET cash = (?) WHERE id = (?)", $new_balance, $_SESSION["id"])) {
            apologize("Sorry, there was a database error.");
        }
        log_buy($symbol, $shares, $stock["price"]);
        redirect("/index.php");
    }

?>