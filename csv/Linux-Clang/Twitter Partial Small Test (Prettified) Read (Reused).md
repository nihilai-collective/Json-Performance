
----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 7703.3 | 0.0968498 | 51.1306ms | 3808 | 30 | 6.25402 | 471.433 | 0.0424058 | 0.303125 | 1(Win) | true |
| Jsonifier | 7536.33 | 0.0436149 | 51.2959ms | 3808 | 640 | 28.2699 | 481.878 | 0.201925 | 0.309481 | 2(Loss) | true |
| simdjson (ondemand) | 7495.93 | 0.203381 | 51.6101ms | 3808 | 80 | 77.6703 | 484.475 | 0.305383 | 0.309549 | 3(Loss) | true |
| Glaze | 3763.31 | 0.0953229 | 101.933ms | 3808 | 40 | 33.8462 | 965 | 0.0862813 | 0.638557 | 4(Loss) | true |
