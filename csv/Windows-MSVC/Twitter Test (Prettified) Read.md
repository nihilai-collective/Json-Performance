
----
### Twitter Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1580.03 | 0.443372 | 5057.21ms | 631514 | 40 | 1.14244e+08 | 381170 | 0.98021 | 1.5668 | 1(Win) | true |
| Jsonifier (two-stage) | 1395.21 | 0.668802 | 5545.3ms | 631514 | 320 | 2.66707e+09 | 431662 | 0.0509398 | 1.77433 | 2(Loss) | true |
| Glaze | 1261.41 | 0.567024 | 5957.18ms | 631514 | 320 | 2.34535e+09 | 477449 | 0.952543 | 1.96255 | 3(Loss) | true |
| simdjson (ondemand) | 1204.31 | 0.444975 | 6494.89ms | 631514 | 30 | 1.48554e+08 | 500087 | 0.148194 | 2.05563 | 4(Loss) | true |
