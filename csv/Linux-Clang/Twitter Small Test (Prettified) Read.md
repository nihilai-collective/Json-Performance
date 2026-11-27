
----
### Twitter Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2642.89 | 0.0948081 | 140.577ms | 3808 | 40 | 67.8872 | 1374.1 | 0.0315457 | 0.918822 | 1(Win) | true |
| Glaze | 2318.1 | 0.0820786 | 161.633ms | 3808 | 40 | 66.1378 | 1566.62 | 0.195897 | 1.04957 | 2(Loss) | true |
| Jsonifier | 2015.14 | 0.134645 | 124.112ms | 3808 | 40 | 235.515 | 1802.15 | 0.171385 | 1.20935 | 3(Loss) | true |
| simdjson (ondemand) | 1357.26 | 0.173232 | 270.248ms | 3808 | 4890 | 105058 | 2675.67 | 0.0647047 | 1.80659 | 4(Loss) | true |
