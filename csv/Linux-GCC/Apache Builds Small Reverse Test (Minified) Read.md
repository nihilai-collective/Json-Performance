
----
### Apache Builds Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1340.41 | 0.0812385 | 915.775ms | 2632 | 2560 | 5924.59 | 1872.61 | 0.0623265 | 3.87705 | 15.916 | 3.1155 | 0.0021658 | 0.000107452 | 4.28916e-05 | 1(Win) | true |
| simdjson (ondemand) | 705.323 | 0.0718727 | 1082.71ms | 2632 | 640 | 4187 | 3558.75 | 0.0352688 | 7.37941 | 29.3921 | 5.95517 | 0.0117698 | 5.46163e-05 | 1.60287e-05 | 2(Loss) | true |
