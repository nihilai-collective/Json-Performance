
----
### CitmCatalog Test (Minified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19598.5 | 1.01724 | 2341.96ms | 500299 | 40 | 2.45314e+06 | 24344.8 | 0.248033 | 0.126161 | 1(Win) | true |
| simdjson (stage-1) | 15843.1 | 0.0771814 | 3098.1ms | 500299 | 4890 | 2.6419e+06 | 30115.5 | 0.414588 | 0.156123 | 2(Loss) | true |
