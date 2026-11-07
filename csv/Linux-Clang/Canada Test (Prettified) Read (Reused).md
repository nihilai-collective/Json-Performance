
----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2459.85 | 0.0337713 | 7750.56ms | 5373214 | 160 | 7.91895e+07 | 2.08317e+06 | 0.21806 | 1.00647 | 1(Win) | true |
| Jsonifier | 2334.01 | 0.0419429 | 8134.79ms | 5373214 | 160 | 1.35675e+08 | 2.19549e+06 | 0.151981 | 1.06074 | 2(Loss) | true |
| simdjson (ondemand) | 2024.77 | 0.0635111 | 9231.48ms | 5373214 | 30 | 7.75062e+07 | 2.5308e+06 | 0.0544683 | 1.22274 | 3(Loss) | true |
| Glaze | 1857.31 | 0.17536 | 10092.1ms | 5373214 | 30 | 7.02234e+08 | 2.75899e+06 | 0.231743 | 1.333 | 4(Loss) | true |
