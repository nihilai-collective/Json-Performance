
----
### Apache Builds Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1254.79 | 0.0798916 | 922.542ms | 2632 | 2560 | 6538.41 | 2000.39 | 0.185692 | 4.16689 | 16.5084 | 3.24544 | 0.00351459 | 5.01638e-05 | 9.49848e-06 | 1(Win) | true |
| simdjson (ondemand) | 712.097 | 0.0477271 | 1076.17ms | 2632 | 2560 | 7245.41 | 3524.9 | 0.0587019 | 7.28894 | 29.4202 | 5.95783 | 0.0111261 | 4.15559e-05 | 3.85876e-06 | 2(Loss) | true |
