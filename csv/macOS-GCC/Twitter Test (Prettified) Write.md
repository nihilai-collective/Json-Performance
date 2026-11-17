
----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15723.2 | 0.25448 | 4345.5ms | 716365 | 4890 | 5.97862e+07 | 43450.3 | 0.288903 | 1(Win) | true |
| Glaze | 3755.83 | 0.389411 | 9286.82ms | 716365 | 320 | 1.60555e+08 | 181898 | 1.90476 | 2(Loss) | true |
| simdjson (reflection) | 333.988 | 0.653051 | 6302.57ms | 716365 | 160 | 2.85511e+10 | 2.04552e+06 | 2.28312 | 3(Loss) | true |
