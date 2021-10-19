<?php
    require 'connection.php';

    $username = $_POST["username"];
    $password = $_POST["password"];
    $filesize = $_POST["filesize"];

    $sql = "SELECT * FROM users JOIN files ON users.id=files.userid AND users.username=? AND users.password=? AND files.size=?";


    $stmt = $connection->prepare($sql);

    $stmt->bind_param("ssi", $username, $password, $filesize);
    
    $stmt->execute();
    $stmt->store_result();
    $rows = $stmt_id->num_rows;
    $stmt->close();

	if ($rows > 0) {
        http_response_code(401);
        exit;
    }

    http_response_code(200);
?>

