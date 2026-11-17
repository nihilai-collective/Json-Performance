
----
### Stream Formats Large Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 18283.6 | 0.0798789 | 5453.37ms | 16197086 | 320 | 1.45736e+08 | 844844 | 0.784728 | 0.275939 | 1.26283 | 0.0751262 | 9.68207e-05 | 0.0157225 | 0.000125728 | 1(Win) | true |
| Jsonifier (generic) | 17920 | 0.203171 | 5532.23ms | 16197086 | 40 | 1.22683e+08 | 861985 | 0.0991126 | 0.28236 | 1.33568 | 0.070273 | 7.86916e-05 | 0.0157177 | 0.000165786 | 2(Loss) | true |
