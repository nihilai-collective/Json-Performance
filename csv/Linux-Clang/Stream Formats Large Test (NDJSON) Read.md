
----
### Stream Formats Large Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Stream%20Formats%20Large%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 18964.9 | 0.380021 | 5207.73ms | 16197086 | 30 | 2.87416e+08 | 814492 | 0.190483 | 0.267345 | 1.17036 | 0.0705008 | 5.83232e-05 | 0.0157127 | 0.0022426 | 1(Win) | true |
| simdjson (ondemand) | 16070.5 | 0.281315 | 6221.75ms | 16197086 | 320 | 2.33963e+09 | 961184 | 0.998279 | 0.314604 | 1.26024 | 0.0744755 | 0.000115326 | 0.0157363 | 0.00208862 | 2(Loss) | true |
