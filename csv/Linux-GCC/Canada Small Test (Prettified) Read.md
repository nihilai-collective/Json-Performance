
----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2216.45 | 0.0517399 | 1230.6ms | 11579 | 2560 | 17010.5 | 4982.12 | 0.130331 | 2.31206 | 10.7821 | 2.30771 | 0.0041596 | 4.54082e-05 | 2.48632e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2144.85 | 0.102828 | 1249.38ms | 11579 | 640 | 17937.1 | 5148.42 | 0.045757 | 2.37196 | 10.5071 | 1.92271 | 0.00316251 | 0.000186895 | 0.000113082 | 2(Loss) | true |
| simdjson (reflection) | 1780.84 | 0.0282932 | 1355.68ms | 11579 | 4890 | 15051 | 6200.79 | 0.0259364 | 2.8535 | 11.8459 | 2.06244 | 0.0044789 | 4.43649e-05 | 2.08579e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1606.11 | 0.0721505 | 1423.5ms | 11579 | 320 | 7874.49 | 6875.38 | 0.0854222 | 3.16514 | 13.0288 | 2.38881 | 0.0024125 | 2.69885e-05 | 1.13352e-05 | 4(Loss) | true |
| Glaze | 1472.12 | 0.053403 | 1475.37ms | 11579 | 1280 | 20540 | 7501.16 | 0.0228246 | 3.47862 | 15.2628 | 2.83522 | 0.00493728 | 4.56106e-05 | 1.8892e-05 | 5(Loss) | true |
