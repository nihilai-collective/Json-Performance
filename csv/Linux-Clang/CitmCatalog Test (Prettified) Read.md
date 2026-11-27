
----
### CitmCatalog Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 22032.9 | 0.060272 | 5037.7ms | 1151920 | 2560 | 2.31191e+06 | 49859.8 | 0.00486654 | 0.112309 | 1(Win) | true |
| simdjson (stage-1) | 20293.2 | 0.0665313 | 5495.5ms | 1151920 | 2560 | 3.32074e+06 | 54134.2 | 0.343624 | 0.121929 | 2(Loss) | true |
