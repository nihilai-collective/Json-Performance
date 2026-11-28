
----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1743.71 | 0.0424325 | 233.759ms | 4215 | 160 | 153.097 | 2305.28 | 0.115901 | 1.40345 | 1(Win) | true |
| Glaze | 879.864 | 0.281177 | 459.179ms | 4215 | 1280 | 211219 | 4568.59 | 0.23938 | 2.7973 | 2(Loss) | true |
