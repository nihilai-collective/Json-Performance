
----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2537.83 | 0.240601 | 6844.94ms | 631514 | 1280 | 4.17297e+08 | 237312 | 0.179504 | 1(Win) | true |
| Jsonifier (two-stage) | 2308.54 | 0.428003 | 7692.59ms | 631514 | 640 | 7.97932e+08 | 260883 | 0.839339 | 2(Loss) | true |
| Glaze | 2093.12 | 0.280173 | 8201.93ms | 631514 | 160 | 1.0398e+08 | 287732 | 0.569992 | 3(Loss) | true |
| simdjson (ondemand) | 1039.78 | 0.487886 | 7646.54ms | 631514 | 320 | 2.55545e+09 | 579215 | 1.33058 | 4(Loss) | true |
