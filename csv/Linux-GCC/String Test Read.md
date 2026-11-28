
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1443.11 | 0.161745 | 286.996ms | 4215 | 30 | 608.947 | 2785.47 | 0.285625 | 1.69957 | 1(Win) | true |
| Glaze | 1061.15 | 0.058158 | 388.686ms | 4215 | 80 | 388.283 | 3788.09 | 0.294881 | 2.31783 | 2(Loss) | true |
| simdjson (reflection) | 1032.89 | 0.148515 | 388.069ms | 4215 | 4890 | 163357 | 3891.74 | 0.00876324 | 2.38041 | 3(Loss) | true |
| simdjson (ondemand) | 738.602 | 0.198389 | 550.191ms | 4215 | 1280 | 149218 | 5442.36 | 0.0348086 | 3.33604 | 4(Loss) | true |
