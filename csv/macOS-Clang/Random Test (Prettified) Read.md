
----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1607.89 | 0.149218 | 5524.46ms | 728486 | 640 | 2.66043e+08 | 432081 | 0.132628 | 1(Win) | true |
| Jsonifier (two-stage) | 1239.84 | 0.0958112 | 7178.35ms | 728486 | 640 | 1.8447e+08 | 560346 | 0.0513289 | 2(Loss) | true |
| Glaze | 1204.8 | 0.166729 | 7390.49ms | 728486 | 320 | 2.95795e+08 | 576644 | 0.0895569 | 3(Loss) | true |
| simdjson (ondemand) | 992.14 | 0.128185 | 9239.24ms | 728486 | 320 | 2.57821e+08 | 700242 | 0.0751336 | 4(Loss) | true |
