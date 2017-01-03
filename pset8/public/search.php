<?php

    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $places = [];
    $location = $_GET["geo"];
    
    if(is_numeric($location))
    {
        $places = CS50::query("SELECT * FROM places WHERE postal_code LIKE ?", $location . "%");
    }
    else
    {
        $words = preg_split('/[,\s]+/', $location);
        if(count($words) == 2)
        {
            $city = $words[0];
            $state = $words[1];
            $places = CS50::query("SELECT * FROM places WHERE MATCH (postal_code, place_name, admin_name1, admin_code1) AGAINST
                                (? IN BOOLEAN MODE)", "+".$city." +".$state);
        }
        else
        {
            $places = CS50::query("SELECT * FROM places WHERE MATCH (postal_code, place_name, admin_name1, admin_code1) AGAINST
                                (? IN BOOLEAN MODE)", "+".$location);
        }
    }

    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>