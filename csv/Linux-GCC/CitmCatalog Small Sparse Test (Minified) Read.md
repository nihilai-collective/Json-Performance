
----
### CitmCatalog Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5045.45 | 0.0480053 | 808.596ms | 5092 | 4890 | 1043.91 | 962.472 | 0.073771 | 1.06121 | 4.72467 | 0.676552 | 0.00127543 | 1.46989e-05 | 1.48595e-06 | 1(Win) | true |
| simdjson (ondemand) | 4440.9 | 0.0669017 | 824.568ms | 5092 | 2560 | 1370.09 | 1093.5 | 0.0605845 | 1.20084 | 5.40083 | 0.66359 | 0.00141314 | 1.19673e-05 | 1.07399e-06 | 2(Loss) | true |
