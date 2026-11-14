
----
### CitmCatalog Test (Minified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21071.1 | 0.277947 | 2319.98ms | 500299 | 640 | 2.53507e+06 | 22643.5 | 0.158305 | 0.117358 | 1(Win) | true |
| simdjson (stage-1) | 17267.7 | 0.130206 | 2860.42ms | 500299 | 1280 | 1.65678e+06 | 27630.9 | 0.0591803 | 0.143239 | 2(Loss) | true |
