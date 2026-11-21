
----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1573.31 | 0.789635 | 5711.93ms | 5373214 | 80 | 5.29155e+10 | 3.25702e+06 | 0.890257 | 1(Win) | true |
| Jsonifier (two-stage) | 1484.95 | 1.0401 | 5926.61ms | 5373214 | 40 | 5.15297e+10 | 3.45083e+06 | 2.0504 | 2(Loss) | true |
| simdjson (ondemand) | 1278.82 | 1.14328 | 6664.16ms | 5373214 | 40 | 8.39494e+10 | 4.00705e+06 | 1.34052 | 3(Loss) | true |
| Glaze | 1207.99 | 0.467649 | 6933.48ms | 5373214 | 80 | 3.14829e+10 | 4.24202e+06 | 4.15754 | 4(Loss) | true |
