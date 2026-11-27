
----
### Apache Builds Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1879.95 | 0.105818 | 854.912ms | 2632 | 2560 | 5110.19 | 1335.18 | 0.165317 | 2.82256 | 11.095 | 2.03761 | 0.000623931 | 0.000136095 | 6.2779e-05 | 1(Win) | true |
| simdjson (ondemand) | 1609.29 | 0.082708 | 873.909ms | 2632 | 320 | 532.538 | 1559.74 | 0.308591 | 3.28551 | 12.136 | 2.1174 | 0.00246486 | 3.91812e-05 | 2.37462e-06 | 2(Loss) | true |
