
----
### Github Events Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1169.61 | 0.0460701 | 902.226ms | 2158 | 320 | 210.286 | 1759.59 | 0.0122528 | 4.50665 | 16.1196 | 3.20621 | 0.00296426 | 8.6886e-05 | 1.15848e-05 | 1(Win) | true |
| simdjson (ondemand) | 932.391 | 0.110541 | 951.065ms | 2158 | 640 | 3810.06 | 2207.26 | 0.0297403 | 5.62186 | 22.4958 | 3.91149 | 0.00332991 | 5.28557e-05 | 3.62025e-06 | 2(Loss) | true |
