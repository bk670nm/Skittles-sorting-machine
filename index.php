    <?php
        echo '<h1>Baska page</h1>';
        
        //$data = json_decode(file_get_contents('https://skittlessorting.azurewebsites.net/'), true);
        
        //$r = $data["r"]
        //$g = $data["g"]
        //$b = $data["b"]
        //$t = $data["t"]

        //$db = fopen("db.txt", "w") or die("Unable to open file!");
        //fwrite($db, $data);
        //fclose($db);
        
        //$text = "r=" . $r . " g=" . $g . " b=" . $b . " t=" . $t;
        // $sum = $sn1 + $sn2;
        //echo $text;
        //echo "<div class='background-color: rgb($r,$g,$b);'></div>";

        $r = $_GET["r"];
        $g = $_GET["g"];
        $b = $_GET["b"];
        $t = $_GET["t"];
        
        $file1 = fopen("sensors.txt","w") or die("Unable to open file!");
        $text = "r=" . $r . " g=" . $g . " b=" . $b . " t=" . $t;
        
        fwrite($file1, $text1);
        fclose($file1);
        
        $file2 = fopen("actuator.txt","w") or die("Unable to open file!");
        $text2 = "Value from actuator. Save this value to actuator.txt";
        fwrite($file2, $text2);
        fclose($file2);
        
        $file3 = fopen("actuator.txt","r") or die ("Subor neexistuje");
        $text3 = fread($file3,filesize("actuator.txt"));
        echo $text3;
        fclose($file3);
    ?>

   