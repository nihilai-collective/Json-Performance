
----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2403.59 | 0.0455747 | 9196.82ms | 728486 | 1280 | 2.22115e+07 | 289042 | 0.0936173 | 1.02992 | 1(Win) | true |
| Jsonifier | 1830.73 | 0.251231 | 5619.69ms | 728486 | 40 | 3.63581e+07 | 379488 | 0.311946 | 1.35225 | 2(Loss) | true |
| Glaze | 1672.94 | 0.323068 | 6133.66ms | 728486 | 30 | 5.39999e+07 | 415281 | 0.470754 | 1.47981 | 3(Loss) | true |
| simdjson (ondemand) | 1559.56 | 0.171421 | 6638.94ms | 728486 | 30 | 1.74939e+07 | 445470 | 0.267836 | 1.58736 | 4(Loss) | true |
