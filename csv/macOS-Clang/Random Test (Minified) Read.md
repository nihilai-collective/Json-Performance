
----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1083.56 | 0.288499 | 9278.3ms | 409725 | 30 | 3.24704e+07 | 360611 | 0.00580463 | 1(Win) | true |
| simdjson (ondemand) | 797.52 | 0.213976 | 6293.1ms | 409725 | 80 | 8.79273e+07 | 489949 | 0.0316948 | 2(Loss) | true |
