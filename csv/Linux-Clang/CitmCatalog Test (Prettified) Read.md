
----
### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22341.6 | 0.0944195 | 4939.27ms | 1151920 | 2560 | 5.51796e+06 | 49170.8 | 0.04391 | 0.110748 | 1(Win) | true |
| simdjson (stage-1) | 20579.1 | 0.0605781 | 5386.17ms | 1151920 | 4890 | 5.11365e+06 | 53382.1 | 0.108895 | 0.120247 | 2(Loss) | true |
