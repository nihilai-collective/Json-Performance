
----
### Twitter Partial Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 6142.23 | 0.291045 | 64.427ms | 3808 | 640 | 1895.15 | 591.25 | 0.158311 | 0.481349 | 1(Win) | true |
| Jsonifier | 6018.17 | 0.566106 | 63.1003ms | 3808 | 640 | 7468.6 | 603.438 | 0.259605 | 0.488291 | 2(Loss) | true |
| simdjson (ondemand) | 4944.62 | 0.215749 | 76.7116ms | 3808 | 1280 | 3213.93 | 734.453 | 0.223881 | 0.596976 | 3(Loss) | true |
| Glaze | 3434.13 | 0.525938 | 114.116ms | 3808 | 80 | 2474.68 | 1057.5 | 0.714286 | 0.871389 | 4(Loss) | true |
