
----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (reflection) STATISTICAL TIE | 2207.21 | 0.317459 | 387.64ms | 8051 | 1280 | 156098 | 3478.61 | 0.0991913 | 1.11335 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2206.18 | 0.088458 | 357.802ms | 8051 | 30 | 284.323 | 3480.23 | 0.0382969 | 1.1136 | 1(Tie) | true |
| Jsonifier | 1929.58 | 0.051525 | 409.202ms | 8051 | 80 | 336.278 | 3979.11 | 0.0348817 | 1.27499 | 3(Loss) | true |
| simdjson (ondemand) | 1912.8 | 0.150543 | 415.731ms | 8051 | 40 | 1460.64 | 4014.03 | 0.0500079 | 1.28617 | 4(Loss) | true |
| Glaze | 1693.47 | 0.0557194 | 461.136ms | 8051 | 80 | 510.562 | 4533.91 | 0.229633 | 1.45354 | 5(Loss) | true |
