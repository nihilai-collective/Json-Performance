
----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2541.71 | 1.22701 | 3955.82ms | 108313 | 80 | 1.98928e+07 | 40640.1 | 0.044794 | 1(Win) | true |
| Jsonifier (two-stage) | 1642.9 | 2.46891 | 6117.59ms | 108313 | 30 | 7.22883e+07 | 62873.6 | 3.28063 | 2(Loss) | true |
| Glaze | 1345.38 | 0.759811 | 7989.95ms | 108313 | 320 | 1.089e+08 | 76777.6 | 0.750118 | 3(Loss) | true |
| simdjson (ondemand) | 708.089 | 0.0718479 | 8027.58ms | 108313 | 1280 | 1.40613e+07 | 145879 | 0.336658 | 4(Loss) | true |
