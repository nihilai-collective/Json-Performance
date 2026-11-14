
----
### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19028.6 | 0.306436 | 5611.5ms | 1151920 | 160 | 5.00761e+06 | 57731.9 | 0.0160306 | 0.130046 | 1(Win) | true |
| simdjson (stage-1) | 15976.1 | 0.043071 | 6961.54ms | 1151920 | 4890 | 4.28927e+06 | 68762.6 | 0.127811 | 0.154899 | 2(Loss) | true |
