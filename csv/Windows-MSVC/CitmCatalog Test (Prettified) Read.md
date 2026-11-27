
----
### CitmCatalog Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 13811.5 | 0.273238 | 8122.14ms | 1151920 | 1280 | 6.04582e+07 | 79539.4 | 0.378006 | 0.219936 | 1(Win) | true |
| simdjson (stage-1) | 11643.6 | 0.460803 | 9511.41ms | 1151920 | 160 | 3.02425e+07 | 94348.1 | 0.146185 | 0.260894 | 2(Loss) | true |
