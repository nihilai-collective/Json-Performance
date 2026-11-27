
----
### Twitter Partial Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 7086.44 | 0.115659 | 41.865ms | 2889 | 160 | 32.3534 | 388.794 | 0.15295 | 0.326125 | 1(Win) | true |
| Jsonifier | 6798.31 | 0.0943444 | 43.1266ms | 2889 | 320 | 46.7817 | 405.272 | 0.0362542 | 0.340532 | 2(Loss) | true |
| Jsonifier (two-stage) | 6729.02 | 0.0566185 | 43.3702ms | 2889 | 640 | 34.3945 | 409.445 | 0.0270872 | 0.343964 | 3(Loss) | true |
| simdjson (reflection) | 6357.97 | 0.0693451 | 45.5432ms | 2889 | 320 | 28.8962 | 433.341 | 0.0699997 | 0.364574 | 4(Loss) | true |
| Glaze | 2936.96 | 0.171835 | 98.7756ms | 2889 | 30 | 77.9552 | 938.1 | 0 | 0.818345 | 5(Loss) | true |
