
----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15286.7 | 0.305352 | 8425.58ms | 1439562 | 4890 | 3.67741e+08 | 89808.1 | 0.483349 | 1(Win) | true |
| Glaze | 4085.12 | 0.153521 | 8815.39ms | 1439584 | 1280 | 3.40731e+08 | 336072 | 0.769756 | 2(Loss) | true |
| simdjson (reflection) | 272.449 | 1.01278 | 7241.87ms | 1439562 | 30 | 7.81341e+10 | 5.039e+06 | 0.23686 | 3(Loss) | true |
