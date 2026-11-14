
----
### CitmCatalog Test (Minified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9301.2 | 0.255181 | 5179.3ms | 500299 | 1280 | 2.19324e+07 | 51296.9 | 0.147209 | 0.326509 | 1(Win) | true |
| simdjson (stage-1) | 8438.18 | 0.509297 | 5620.03ms | 500299 | 2560 | 2.12297e+08 | 56543.3 | 0.382227 | 0.359791 | 2(Loss) | true |
