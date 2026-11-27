
----
### CitmCatalog Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 18501.9 | 1.0526 | 8030.12ms | 1439562 | 40 | 2.44014e+07 | 74201.6 | 0.280963 | 1(Win) | true |
| Glaze DID NOT CONVERGE | 3483.68 | 0.516053 | 9228.77ms | 1439584 | 160 | 6.61769e+08 | 394093 | 5.96627 | -(Loss) | false |
| simdjson (reflection) | 276.246 | 1.21006 | 6850.78ms | 1439562 | 30 | 1.08493e+11 | 4.96975e+06 | 0.912116 | 3(Loss) | true |
