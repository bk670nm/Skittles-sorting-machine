<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Form</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>

    <?php
    echo '<h1>Baskasss page</h1>';

    $r = $_GET["r"];
    $g = $_GET["g"];
    $b = $_GET["b"];
    $t = $_GET["t"];

    $file1 = fopen("db.txt","w") or die("Unable to open file!");

    $values = array();

    fwrite($file1, $r . "\n" . $g . "\n" . $b . "\n" . $t);
    fclose($file1);

    if ($file = fopen("db.txt", "r")) {
        $values = file("db.txt", FILE_IGNORE_NEW_LINES);
        $values = array_map('intval', $values);

        fclose($file);
    }

    var_dump($values); // array(4) { [0]=> int(10) [1]=> int(20) [2]=> int(30) [3]=> int(50) }
    // tu rob co ti treba
    ?>

    
</body>
</html>

   