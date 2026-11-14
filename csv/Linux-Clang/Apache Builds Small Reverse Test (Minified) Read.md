
----
### Apache Builds Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1271.12 | 0.114739 | 916.558ms | 2632 | 160 | 821.373 | 1974.69 | 0.0398638 | 4.13558 | 16.5657 | 3.24924 | 0.00457827 | 0.000113982 | 1.8997e-05 | 1(Win) | true |
| simdjson (ondemand) | 717.56 | 0.0713339 | 1071.6ms | 2632 | 160 | 996.248 | 3498.06 | 0.117345 | 7.26108 | 30.9586 | 5.91717 | 0.0127826 | 7.83625e-05 | 2.37462e-06 | 2(Loss) | true |
