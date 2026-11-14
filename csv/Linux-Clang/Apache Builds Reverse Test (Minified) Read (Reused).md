
----
### Apache Builds Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1456.24 | 0.0967431 | 8180.2ms | 94653 | 160 | 575391 | 61987.1 | 0.00937607 | 3.51891 | 17.1026 | 3.36093 | 0.00747322 | 8.31986e-06 | 3.76375e-06 | 1(Win) | true |
| simdjson (ondemand) | 849.251 | 0.051091 | 6433.52ms | 94653 | 640 | 1.88741e+06 | 106291 | 0.051214 | 6.02828 | 31.2898 | 6.18435 | 0.00871436 | 1.02182e-05 | 4.25898e-06 | 2(Loss) | true |
