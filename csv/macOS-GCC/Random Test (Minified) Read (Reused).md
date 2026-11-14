
----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1395.76 | 0.185025 | 5637.28ms | 461466 | 320 | 1.08911e+08 | 315305 | 0.881459 | 1(Win) | true |
| Jsonifier (two-stage) | 1172.34 | 0.474868 | 6404.59ms | 461466 | 640 | 2.03374e+09 | 375392 | 1.73818 | 2(Loss) | true |
| Glaze | 928.644 | 0.0794044 | 7522.58ms | 461466 | 640 | 9.06255e+07 | 473904 | 0.231213 | 3(Loss) | true |
| simdjson (reflection) | 894.512 | 0.198304 | 7660.87ms | 461466 | 40 | 3.80744e+07 | 491987 | 0.00130086 | 4(Loss) | true |
| simdjson (ondemand) | 789.552 | 0.108801 | 8630.24ms | 461466 | 640 | 2.35378e+08 | 557390 | 0.384173 | 5(Loss) | true |
