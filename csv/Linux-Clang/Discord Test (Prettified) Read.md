
----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2336.06 | 0.265433 | 3390.01ms | 83958 | 160 | 1.3243e+06 | 34275 | 0.087469 | 1.05891 | 1(Win) | true |
| Jsonifier | 1938.01 | 0.277283 | 4162.52ms | 83958 | 160 | 2.09982e+06 | 41314.9 | 0.504515 | 1.27659 | 2(Loss) | true |
| Glaze | 1704.39 | 0.060207 | 4700.1ms | 83958 | 4890 | 3.91189e+06 | 46977.7 | 0.384722 | 1.45172 | 3(Loss) | true |
| simdjson (ondemand) | 1183.62 | 0.110279 | 6857.7ms | 83958 | 640 | 3.56174e+06 | 67647.1 | 0.0381837 | 2.09086 | 4(Loss) | true |
