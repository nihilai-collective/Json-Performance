
----
### Apache Builds Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2377.36 | 0.0480136 | 821.721ms | 2632 | 4890 | 1256.67 | 1055.82 | 0.191932 | 2.24744 | 9.46391 | 1.7747 | 0.00144975 | 6.92282e-05 | 1.82588e-05 | 1(Win) | true |
| simdjson (ondemand) | 2023.15 | 0.0721984 | 837.799ms | 2632 | 1280 | 1027.02 | 1240.67 | 0.00566697 | 2.62727 | 10.1246 | 1.70973 | 0.0047344 | 3.2651e-05 | 6.82703e-06 | 2(Loss) | true |
