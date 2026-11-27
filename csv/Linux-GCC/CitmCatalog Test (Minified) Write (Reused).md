
----
### CitmCatalog Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9651.83 | 0.0923263 | 4937.27ms | 500299 | 2560 | 5.3325e+06 | 49433.3 | 0.211548 | 0.256361 | 1(Win) | true |
| simdjson (reflection) | 9353.83 | 0.0787957 | 5147.07ms | 500299 | 4890 | 7.89941e+06 | 51008.2 | 0.18005 | 0.264522 | 2(Loss) | true |
| Glaze | 4069.85 | 0.220651 | 6168.26ms | 500299 | 80 | 5.35312e+06 | 117233 | 0.0151324 | 0.60816 | 3(Loss) | true |
