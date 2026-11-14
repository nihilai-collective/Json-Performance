
----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1391.75 | 0.044122 | 8913.98ms | 500299 | 640 | 1.4643e+07 | 342823 | 0.20997 | 3.6421 | 16.7854 | 3.13058 | 0.0145547 | 0.0145646 | 2.76772e-05 | 1(Win) | true |
| simdjson (ondemand) | 1202.49 | 0.144218 | 5139.44ms | 500299 | 40 | 1.30978e+07 | 396778 | 0.109079 | 4.22009 | 17.7439 | 2.9633 | 0.0205423 | 0.0176067 | 1.79393e-05 | 2(Loss) | true |
