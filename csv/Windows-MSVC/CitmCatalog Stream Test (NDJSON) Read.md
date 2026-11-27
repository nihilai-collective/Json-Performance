
----
### CitmCatalog Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 736.728 | 1.52697 | 9112.39ms | 4525120 | 30 | 2.40011e+11 | 5.85765e+06 | 2.79098 | 4.12483 | -(Win) | false |
| simdjson (ondemand) | 657.496 | 0.740693 | 10235.1ms | 4525120 | 30 | 7.09042e+10 | 6.56353e+06 | 1.39941 | 4.62237 | 2(Loss) | true |
