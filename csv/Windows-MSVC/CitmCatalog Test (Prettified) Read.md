
----
### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21621.1 | 0.341952 | 5219.52ms | 1151920 | 160 | 4.82991e+06 | 50809.4 | 0.0798918 | 0.114435 | 1(Win) | true |
| simdjson (stage-1) | 20258.3 | 0.451456 | 5525.33ms | 1151920 | 80 | 4.79468e+06 | 54227.5 | 0.309841 | 0.122145 | 2(Loss) | true |
