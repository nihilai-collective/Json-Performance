
----
### Twitter Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 811.595 | 0.078326 | 1050.77ms | 2821 | 640 | 4314.4 | 3314.85 | 0.0333614 | 6.41744 | 26.3339 | 4.94541 | 0.00178848 | 4.04334e-05 | 8.86211e-06 | 1(Win) | true |
| simdjson (ondemand) | 402.7 | 0.0429079 | 1386.66ms | 2821 | 2560 | 21035.7 | 6680.7 | 0.0208346 | 12.8549 | 58.8798 | 11.8788 | 0.0103202 | 7.18661e-05 | 1.8555e-05 | 2(Loss) | true |
