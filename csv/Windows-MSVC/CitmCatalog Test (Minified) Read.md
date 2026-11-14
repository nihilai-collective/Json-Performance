
----
### CitmCatalog Test (Minified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22285.7 | 0.128164 | 2173.47ms | 500299 | 4890 | 3.68172e+06 | 21409.3 | 0.228232 | 0.110957 | 1(Win) | true |
| simdjson (stage-1) | 19207.3 | 0.485283 | 2546.49ms | 500299 | 160 | 2.32507e+06 | 24840.6 | 0.0578354 | 0.128748 | 2(Loss) | true |
