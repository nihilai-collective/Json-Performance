
----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2392.55 | 0.0885295 | 837.715ms | 2632 | 2560 | 2208.34 | 1049.12 | 0.143701 | 2.22 | 9.09157 | 1.54977 | 0.000766409 | 5.23901e-05 | 1.36541e-05 | 1(Win) | true |
| simdjson (ondemand) | 1810.81 | 0.0843764 | 871.56ms | 2632 | 2560 | 3501.93 | 1386.16 | 0.175901 | 2.91427 | 9.89172 | 1.731 | 0.00180634 | 9.39459e-05 | 4.49694e-05 | 2(Loss) | true |
