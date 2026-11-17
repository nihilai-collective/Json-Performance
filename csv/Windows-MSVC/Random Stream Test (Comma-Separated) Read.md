
----
### Random Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 854.339 | 0.117393 | 8567.1ms | 4506446 | 30 | 1.0462e+09 | 5.03042e+06 | 0.147087 | 3.55741 | 1(Win) | true |
| simdjson (ondemand) | 672.964 | 0.12138 | 10702.4ms | 4506446 | 30 | 1.80261e+09 | 6.3862e+06 | 0.0702584 | 4.51638 | 2(Loss) | true |
