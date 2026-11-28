
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1440.11 | 0.175527 | 282.832ms | 4215 | 30 | 720.133 | 2791.27 | 0.156685 | 1.70348 | 1(Win) | true |
| simdjson (reflection) | 1060.92 | 0.164185 | 383.624ms | 4215 | 2560 | 99068.3 | 3788.92 | 0.0803199 | 2.31779 | 2(Loss) | true |
| Glaze | 1043.02 | 0.0528083 | 387.536ms | 4215 | 80 | 331.365 | 3853.95 | 0.0805017 | 2.35808 | 3(Loss) | true |
| simdjson (ondemand) | 740.747 | 0.0809038 | 532.288ms | 4215 | 30 | 578.248 | 5426.6 | 0.0442462 | 3.32539 | 4(Loss) | true |
