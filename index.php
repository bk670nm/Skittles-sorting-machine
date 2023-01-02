<?php
    function read_from_file($path) : array
    {
        $file = fopen($path, "r") or die("Unable to open file!");
        $data = file($path, FILE_IGNORE_NEW_LINES);
        fclose($file);

        return array_map('intval', $data);
    }

    function write_to_file($path, $data)
    {
        $file = fopen($path, "w") or die("Unable to open file!");

        fwrite($file, $data["r"] . "\n" . $data["g"] . "\n" . $data["b"] . "\n" . $data["t"]);

        fclose($file);

        return $data;
    }

    $method = $_SERVER['REQUEST_METHOD'];
    $angle = 120; // default

    if ($method == 'POST') {
        $data = json_decode(file_get_contents('php://input'), true);

        $values = write_to_file("db.txt", $data);

        if ($data["r"] >= 13 and $data["r"] <= 15 and $data["g"] >=15 and $data["g"] <= 20  ){ // orange
            $angle = 30;
        }
        else if($data["r"] >= 11 and $data["r"] <= 14 and $data["g"] >=13 and $data["g"] <= 15  ){ // yellow
            $angle = 30;
        }
        else if($data["r"] >= 16 and $data["r"] <= 20 and $data["g"] >= 14 and $data["g"] <= 18){ // green
            $angle = 90;
        }
        else if($data["r"] >= 16 and $data["r"] <= 23 and $data["g"] >= 17 and $data["g"] <= 25 ){ // red, purple
            $angle = 60;
        }

        echo $angle;
        exit;
    }

    $color = "No color";
    $val = read_from_file("db.txt");
    if ($method == 'GET') {
        if ($val[0] >= 12 and $val[0] <= 15 and $val[1] >=15 and $val[1] <= 20  ){ // orange) {
            $color = "Orange";
        }
        else if($val[0] >= 11 and $val[0] <= 14 and $val[1] >=13 and $val[1] <= 15 ){ // yellow
            $color = "Yellow";
        }
        else if($val[0] >= 16 and $val[0] <= 20 and $val[1] >= 14 and $val[1] <= 18){ // green
            $color = "Green";
        }
        else if($val[0] >= 16 and $val[0] <= 23 and $val[1] >= 17 and $val[1] <= 25) { // red,purple
            $color = "Red/Purple";
        }
    }

    $page = $_SERVER['PHP_SELF'];
    $sec = "3";
?>

<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta http-equiv="refresh" content="<?php echo $sec?>;URL='<?php echo $page?>'">
        <title>Skittles</title>
        <link rel="stylesheet" href="style.css">
    </head>

    <body>
        <div class="bg-image"></div>

        <div class="bg-text">
            <h1>Skittles sorting machine</h1>
            <?php
                echo '<p>RGB: '.$val[0].'   '. $val[1] .'   '. $val[2] .'</p>';
                echo '<p>Actual color: '.$color.'</p>';
                echo '<p>Temperature: '. $val[3].'</p>';
            ?>
        </div>
    </body>
</html>