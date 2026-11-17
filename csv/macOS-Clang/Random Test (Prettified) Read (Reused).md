
----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2053.37 | 0.232953 | 5445.76ms | 728486 | 30 | 1.86365e+07 | 338340 | 0.133219 | 1(Win) | true |
| Jsonifier (two-stage) | 1789.89 | 0.183797 | 7145.9ms | 728486 | 40 | 2.03575e+07 | 388146 | 0.431092 | 2(Loss) | true |
| Glaze | 1345.06 | 0.362927 | 7669ms | 728486 | 640 | 2.24892e+09 | 516510 | 0.156915 | 3(Loss) | true |
| simdjson (ondemand) | 1142.76 | 0.0709305 | 8900.46ms | 728486 | 320 | 5.95039e+07 | 607946 | 0.108071 | 4(Loss) | true |
