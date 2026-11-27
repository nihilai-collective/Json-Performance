
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1662.2 | 0.0741464 | 79.7819ms | 1313 | 160 | 49.9189 | 753.325 | 0.107739 | 1.43485 | 1(Win) | true |
| simdjson (reflection) | 952.785 | 0.0695402 | 132.818ms | 1313 | 40 | 33.4096 | 1314.22 | 0.00824245 | 2.54299 | 2(Loss) | true |
| Glaze | 898.139 | 0.0437846 | 143.205ms | 1313 | 320 | 119.244 | 1394.19 | 0.216994 | 2.70401 | 3(Loss) | true |
| simdjson (ondemand) | 338.798 | 0.0311327 | 381.217ms | 1313 | 30 | 39.7195 | 3695.93 | 0.134202 | 7.25732 | 4(Loss) | true |
