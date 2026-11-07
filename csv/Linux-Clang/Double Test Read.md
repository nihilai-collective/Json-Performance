
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1401.5 | 0.265715 | 125.776ms | 1811 | 2560 | 27449 | 1232.33 | 0.00367685 | 1.72992 | 1(Win) | true |
| Glaze | 902.66 | 0.0703237 | 195.856ms | 1811 | 80 | 144.838 | 1913.35 | 0.185195 | 2.70651 | 2(Loss) | true |
| Jsonifier (two-stage) | 509.46 | 0.0751845 | 343.443ms | 1811 | 30 | 194.892 | 3390.07 | 0.0206443 | 4.82188 | 3(Loss) | true |
| simdjson (ondemand) | 315.572 | 0.0567681 | 584.073ms | 1811 | 30 | 289.582 | 5472.93 | 0.0663433 | 7.81136 | 4(Loss) | true |
