
----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2596.34 | 0.681062 | 191.659ms | 3808 | 30 | 2722.48 | 1398.73 | 0.404374 | 1(Win) | true |
| Glaze | 2360.78 | 0.151801 | 191.182ms | 3808 | 160 | 872.475 | 1538.3 | 0.0886503 | 2(Loss) | true |
| Jsonifier (two-stage) | 2254.71 | 0.593003 | 191.714ms | 3808 | 1280 | 116772 | 1610.67 | 0.283383 | 3(Loss) | true |
| simdjson (ondemand) | 1046.75 | 0.16286 | 401.659ms | 3808 | 30 | 957.766 | 3469.4 | 0.441013 | 4(Loss) | true |
