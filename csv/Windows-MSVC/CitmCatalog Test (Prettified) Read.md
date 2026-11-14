
----
### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12204.3 | 0.214 | 8996.6ms | 1151920 | 4890 | 1.8145e+08 | 90014 | 0.272946 | 0.248892 | 1(Win) | true |
| simdjson (stage-1) | 11704.8 | 0.628725 | 9362.63ms | 1151920 | 640 | 2.22853e+08 | 93855.2 | 0.281721 | 0.259521 | 2(Loss) | true |
