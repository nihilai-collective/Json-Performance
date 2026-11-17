
----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20217.4 | 0.316283 | 1743.01ms | 213963 | 160 | 163042 | 10092.8 | 0.000495403 | 0.250844 | 1.119 | 0.27523 | 0.000144476 | 2.42448e-06 | 1.34369e-06 | 1(Win) | true |
| Glaze | 4880.11 | 0.0497971 | 4962.99ms | 213963 | 4890 | 2.11999e+06 | 41812.8 | 0.101602 | 1.03226 | 3.64005 | 0.598024 | 0.000650071 | 3.13989e-05 | 8.42318e-06 | 2(Loss) | true |
