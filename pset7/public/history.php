<?php

    // configuration
    require("../includes/config.php"); 

    $rows = CS50::query("SELECT symbol, shares, buy, price, time FROM history WHERE user_id = (?)", $_SESSION["id"]);
    $transactions = [];
    foreach ($rows as $row)
    {
        $transactions[] = [
            "symbol" => $row["symbol"],
            "shares" => $row["shares"],
            "price" => $row["price"],
            "buy" => $row["buy"],
            "time" => $row["time"]
        ];
    }
    // render history
    render("transactions.php", ["transactions" => $transactions, "title" => "Transactions"]);

?>
