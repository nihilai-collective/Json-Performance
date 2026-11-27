
----
### Twitter Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16878.3 | 0.148408 | 4237.23ms | 716365 | 80 | 288680 | 40476.8 | 0.00790639 | 1(Win) | true |
| Glaze | 4642.38 | 0.0622908 | 7673.98ms | 716365 | 2560 | 2.15117e+07 | 147161 | 0.0490859 | 2(Loss) | true |
| simdjson (reflection) | 437.13 | 0.0853606 | 9997.9ms | 716365 | 40 | 7.11905e+07 | 1.56287e+06 | 0.176456 | 3(Loss) | true |
