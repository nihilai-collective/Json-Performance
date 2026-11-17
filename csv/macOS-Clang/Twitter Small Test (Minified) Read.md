
----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2138.62 | 0.33942 | 136.682ms | 2889 | 640 | 12237.2 | 1288.29 | 0.119928 | 1(Win) | true |
| Glaze | 1652.49 | 0.390228 | 170.006ms | 2889 | 4890 | 206998 | 1667.28 | 0.521246 | 2(Loss) | true |
| Jsonifier (two-stage) | 1580.54 | 0.577236 | 189.659ms | 2889 | 4890 | 495108 | 1743.18 | 0.942107 | 3(Loss) | true |
| simdjson (ondemand) | 792.519 | 0.158465 | 363.356ms | 2889 | 30 | 910.464 | 3476.47 | 0.277289 | 4(Loss) | true |
