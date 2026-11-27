
----
### Twitter Partial Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5737.52 | 0.142569 | 5735.06ms | 631514 | 160 | 3.58334e+06 | 104968 | 0.0568121 | 1(Win) | true |
| Jsonifier (two-stage) | 5095.49 | 0.322864 | 6332.45ms | 631514 | 2560 | 3.72796e+08 | 118194 | 0.706808 | 2(Loss) | true |
| simdjson (ondemand) | 3970.02 | 0.43247 | 7428.43ms | 631514 | 640 | 2.75469e+08 | 151702 | 2.51429 | 3(Loss) | true |
| Glaze | 2750.86 | 0.124455 | 5728.22ms | 631514 | 160 | 1.18789e+07 | 218934 | 0.0219006 | 4(Loss) | true |
