
----
### CitmCatalog Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1494.11 | 0.182935 | 8230.59ms | 500299 | 160 | 5.46021e+07 | 319336 | 0.0312797 | 1.65683 | 1(Win) | true |
| simdjson (ondemand) | 1377.28 | 0.0862522 | 8857.09ms | 500299 | 320 | 2.85697e+07 | 346424 | 0.265647 | 1.7974 | 2(Loss) | true |
