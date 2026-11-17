
----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1606.95 | 0.284622 | 571.029ms | 9578 | 1280 | 335037 | 5684.25 | 0.0731172 | 1.53343 | 1(Win) | true |
| Glaze | 1437.23 | 0.240328 | 639.701ms | 9578 | 1280 | 298616 | 6355.48 | 0.207621 | 1.71546 | 2(Loss) | true |
| simdjson (ondemand) | 1130.67 | 0.154173 | 821.448ms | 9578 | 2560 | 397131 | 8078.65 | 0.43796 | 2.18263 | 3(Loss) | true |
| Jsonifier (two-stage) | 904.886 | 0.184458 | 1021.01ms | 9578 | 1280 | 443782 | 10094.4 | 0.0295249 | 2.7289 | 4(Loss) | true |
