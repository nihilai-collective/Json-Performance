
----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1299.39 | 0.119274 | 908.059ms | 9578 | 1280 | 89985.8 | 7029.69 | 0.00889166 | 2.33121 | 1(Win) | true |
| Glaze | 1001.29 | 0.257511 | 1130.42ms | 9578 | 160 | 88295.6 | 9122.5 | 0.495731 | 3.02673 | 2(Loss) | true |
| Jsonifier (two-stage) | 986.458 | 0.0723743 | 1140.66ms | 9578 | 2560 | 114975 | 9259.69 | 0.027006 | 3.07317 | 3(Loss) | true |
| simdjson (ondemand) | 950.004 | 0.632578 | 1183.13ms | 9578 | 40 | 147974 | 9615 | 0.0867453 | 3.18925 | 4(Loss) | true |
