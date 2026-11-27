
----
### Apache Builds Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1460.2 | 0.836992 | 5053.08ms | 4212000 | 80 | 4.24116e+10 | 2.75091e+06 | 0.738569 | 3.46688 | 15.1241 | 2.90335 | 0.0147402 | 0.0666483 | 0.010184 | 1(Win) | true |
| simdjson (ondemand) | 1293.73 | 1.00213 | 5572.84ms | 4212000 | 40 | 3.87254e+10 | 3.10488e+06 | 1.18922 | 3.90735 | 16.6576 | 2.8979 | 0.0107331 | 0.0670996 | 0.00338313 | 2(Loss) | true |
