
----
### Large Amazon Cellphones Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3333.56 | 0.231664 | 9465.38ms | 10548466 | 30 | 1.46622e+09 | 3.01774e+06 | 0.544933 | 1(Win) | true |
| simdjson (ondemand) | 2870.35 | 0.198427 | 5280.64ms | 10548466 | 30 | 1.45087e+09 | 3.50473e+06 | 0.410491 | 2(Loss) | true |
