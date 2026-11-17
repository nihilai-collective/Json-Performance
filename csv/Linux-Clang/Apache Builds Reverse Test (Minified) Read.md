
----
### Apache Builds Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1132.97 | 0.0169548 | 8716.11ms | 94653 | 4890 | 892334 | 79674.2 | 0.0121462 | 4.48201 | 20.9675 | 4.21809 | 0.0105955 | 2.63496e-05 | 1.61153e-05 | 1(Win) | true |
| simdjson (ondemand) | 704.529 | 0.0435959 | 6928.8ms | 94653 | 640 | 1.99684e+06 | 128125 | 0.155978 | 7.2114 | 35.153 | 7.04403 | 0.0150085 | 3.03246e-05 | 1.69864e-05 | 2(Loss) | true |
