
----
### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21181.7 | 0.126197 | 5216.76ms | 1151920 | 640 | 2.74158e+06 | 51863.5 | 0.956994 | 0.116819 | 1(Win) | true |
| simdjson (stage-1) | 19239.7 | 0.119858 | 5725.08ms | 1151920 | 1280 | 5.99508e+06 | 57098.4 | 0.101824 | 0.128619 | 2(Loss) | true |
