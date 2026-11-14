
----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2550.3 | 0.0765645 | 823.322ms | 2632 | 2560 | 1453.73 | 984.225 | 0.0905719 | 2.10083 | 9.09157 | 1.54977 | 0.000791787 | 5.50615e-05 | 1.06858e-05 | 1(Win) | true |
| simdjson (ondemand) | 1862.9 | 0.0713221 | 857.044ms | 2632 | 2560 | 2364.18 | 1347.4 | 0.103751 | 2.84415 | 9.88906 | 1.73062 | 0.0026759 | 3.25026e-05 | 2.96828e-06 | 2(Loss) | true |
