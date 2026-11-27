
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1355.64 | 0.133303 | 289.54ms | 4215 | 30 | 468.717 | 2965.2 | 0.557822 | 1.80919 | 1(Win) | true |
| Glaze | 1006.02 | 0.0885723 | 401.493ms | 4215 | 30 | 375.747 | 3995.67 | 0.276058 | 2.44512 | 2(Loss) | true |
| simdjson (ondemand) | 808.488 | 0.114981 | 500.183ms | 4215 | 4890 | 159813 | 4971.92 | 0.116229 | 3.04644 | 3(Loss) | true |
