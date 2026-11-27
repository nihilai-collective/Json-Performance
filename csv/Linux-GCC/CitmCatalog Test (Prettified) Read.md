
----
### CitmCatalog Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 20967.8 | 0.0862111 | 5347.04ms | 1151920 | 1280 | 2.61141e+06 | 52392.5 | 0.0987353 | 0.118017 | 1(Win) | true |
| simdjson (stage-1) | 17705.1 | 0.11751 | 6257.4ms | 1151920 | 1280 | 6.80467e+06 | 62047.3 | 0.0578346 | 0.139768 | 2(Loss) | true |
