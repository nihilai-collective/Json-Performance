
----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2829.98 | 0.0739932 | 133.42ms | 3808 | 160 | 144.255 | 1283.26 | 0.0637619 | 0.857072 | 1(Win) | true |
| Glaze | 2341.68 | 0.0557899 | 158.787ms | 3808 | 160 | 119.776 | 1550.85 | 0.0346704 | 1.03929 | 2(Loss) | true |
| Jsonifier | 1946.33 | 0.141651 | 193.28ms | 3808 | 30 | 209.568 | 1865.87 | 0.0572001 | 1.25355 | 3(Loss) | true |
| simdjson (ondemand) | 1331 | 0.106785 | 277.283ms | 3808 | 30 | 254.671 | 2728.47 | 0.0488436 | 1.8432 | 4(Loss) | true |
