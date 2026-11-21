
----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2370.7 | 0.147341 | 9431.51ms | 728486 | 160 | 2.98302e+07 | 293052 | 1.19478 | 1.04421 | 1(Win) | true |
| Jsonifier | 1882.08 | 0.206409 | 5611.12ms | 728486 | 30 | 1.74159e+07 | 369133 | 0.00388312 | 1.31533 | 2(Loss) | true |
| Glaze | 1651.31 | 0.114692 | 6345.3ms | 728486 | 640 | 1.49017e+08 | 420720 | 0.11792 | 1.49916 | 3(Loss) | true |
| simdjson (ondemand) | 1507.58 | 0.20983 | 6659.21ms | 728486 | 160 | 1.49601e+08 | 460830 | 0.0697588 | 1.64211 | 4(Loss) | true |
