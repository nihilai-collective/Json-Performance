
----
### CitmCatalog Test (Minified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5802.67 | 0.0852421 | 8402.45ms | 500299 | 4890 | 2.40227e+07 | 82224.6 | 1.60949 | 1(Win) | true |
| simdjson (stage-1) | 5142.47 | 0.122099 | 9432.85ms | 500299 | 2560 | 3.28532e+07 | 92780.7 | 0.196744 | 2(Loss) | true |
