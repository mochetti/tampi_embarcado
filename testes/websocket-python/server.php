<?php

require './vendor/autoload.php';
use Ratchet\Server\EchoServer;

$app = new Ratchet\App('0.0.0.0', 9980);
$app->route('/', new EchoServer, ['*']);
$app->run();
