<?php
    require 'connection.php';

    $id = $_GET["id"];

    $sql = "DELETE FROM news WHERE id=?";

    $stmt = $connection->prepare($sql);

    $stmt->bind_param("i", $id);
    
    $stmt->execute();
    $stmt->close();
?>

