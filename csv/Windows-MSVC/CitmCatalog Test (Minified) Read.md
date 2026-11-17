
----
### CitmCatalog Test (Minified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21777.8 | 0.229979 | 2227.81ms | 500299 | 1280 | 3.24952e+06 | 21908.7 | 0.0488295 | 0.113546 | 1(Win) | true |
| simdjson (stage-1) | 18626.5 | 0.155261 | 2596.65ms | 500299 | 2560 | 4.04915e+06 | 25615.3 | 0.0782922 | 0.132754 | 2(Loss) | true |
