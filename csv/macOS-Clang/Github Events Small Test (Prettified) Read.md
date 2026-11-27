
----
### Github Events Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1718.14 | 0.0337228 | 123.355ms | 2158 | 2560 | 417.707 | 1197.82 | 0.0575594 | 1(Win) | true |
| Jsonifier (two-stage) | 1636.41 | 0.0409219 | 129.909ms | 2158 | 1280 | 339.033 | 1257.65 | 0.0384669 | 2(Loss) | true |
| Glaze | 1552.55 | 0.110213 | 139.296ms | 2158 | 4890 | 10437.3 | 1325.58 | 0.0446536 | 3(Loss) | true |
| simdjson (ondemand) | 1275.52 | 0.21542 | 167.097ms | 2158 | 80 | 966.481 | 1613.49 | 0.059689 | 4(Loss) | true |
