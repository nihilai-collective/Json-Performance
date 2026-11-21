
----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1477.1 | 0.171343 | 6028.34ms | 728486 | 320 | 2.07829e+08 | 470340 | 0.961755 | 1(Win) | true |
| Glaze | 1129.08 | 0.499154 | 8170.47ms | 728486 | 30 | 2.82998e+08 | 615314 | 1.54463 | 2(Loss) | true |
| Jsonifier (two-stage) | 1074.11 | 0.588142 | 8053.55ms | 728486 | 40 | 5.7885e+08 | 646801 | 0.0878028 | 3(Loss) | true |
| simdjson (ondemand) | 893.674 | 0.16161 | 9836.05ms | 728486 | 320 | 5.05094e+08 | 777396 | 0.465407 | 4(Loss) | true |
