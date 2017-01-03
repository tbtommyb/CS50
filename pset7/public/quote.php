<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // render form
        render("symbol_form.php", ["title" => "Choose a symbol"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if(empty($_POST["symbol"])) {
            apologize("You did not enter a symbol");
        }
        $stock = lookup($_POST["symbol"]);
        if(!$stock) {
            apologize("You entered an invalid symbol");
        }
        render("price.php", ["name" => $stock["name"], "symbol" => $stock["symbol"], "price" => $stock["price"]]);
    }

?>