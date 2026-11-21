
----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2617.89 | 0.216766 | 176.454ms | 4669 | 2560 | 34799.2 | 1700.88 | 0.106426 | 1(Win) | true |
| Jsonifier (two-stage) | 1699.9 | 0.166424 | 278.313ms | 4669 | 30 | 570.11 | 2619.4 | 0.00381752 | 2(Loss) | true |
| Glaze | 1274.46 | 0.284737 | 374.695ms | 4669 | 40 | 3958.63 | 3493.8 | 0.29489 | 3(Loss) | true |
| simdjson (ondemand) | 563.402 | 0.269909 | 797.118ms | 4669 | 320 | 145611 | 7903.25 | 0.0189364 | 4(Loss) | true |
