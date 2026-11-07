
----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2047.77 | 0.0878544 | 8533.38ms | 631514 | 1280 | 8.54555e+07 | 294105 | 0.0426165 | 1.20882 | 1(Win) | true |
| Jsonifier | 1737.83 | 0.127179 | 9887.09ms | 631514 | 320 | 6.21624e+07 | 346557 | 0.118976 | 1.42448 | 2(Loss) | true |
| Glaze | 1699.04 | 0.110796 | 10042.3ms | 631514 | 640 | 9.87163e+07 | 354471 | 0.147977 | 1.45706 | 3(Loss) | true |
| simdjson (ondemand) | 1514.57 | 0.340075 | 5529.55ms | 631514 | 40 | 7.31466e+07 | 397642 | 0.0672263 | 1.63452 | 4(Loss) | true |
