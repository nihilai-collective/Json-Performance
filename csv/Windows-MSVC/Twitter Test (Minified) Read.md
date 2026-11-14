
----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1087.9 | 0.24558 | 5882.96ms | 264040 | 1280 | 4.13575e+08 | 231462 | 0.815588 | 2.79323 | 1(Win) | true |
| simdjson (ondemand) | 964.14 | 0.311922 | 6763.32ms | 264040 | 160 | 1.06187e+08 | 261174 | 0.0100498 | 3.15186 | 2(Loss) | true |
