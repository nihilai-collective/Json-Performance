
----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20053.6 | 0.0864786 | 7972.53ms | 1439562 | 80 | 280405 | 68460.4 | 0.0990285 | 0.251919 | 0.703086 | 0.104897 | 0.000444858 | 0.0188311 | 5.77433e-06 | 1(Win) | true |
| Glaze | 5749.81 | 0.118721 | 6326.35ms | 1439584 | 640 | 5.14281e+07 | 238772 | 0.00861496 | 0.875412 | 3.1224 | 0.499162 | 0.000870322 | 0.0615474 | 1.30886e-05 | 2(Loss) | true |
| simdjson (reflection) | 556.406 | 1.1891 | 7776.9ms | 1439562 | 80 | 6.88665e+10 | 2.4674e+06 | 0.0276395 | 9.03032 | 35.7848 | 6.43753 | 0.0159097 | 0.309561 | 0.00132322 | 3(Loss) | true |
