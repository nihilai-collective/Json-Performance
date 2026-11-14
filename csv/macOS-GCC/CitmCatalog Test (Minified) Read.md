
----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1912.86 | 0.961188 | 6717.08ms | 500299 | 30 | 1.72438e+08 | 249429 | 0.0547083 | 1(Win) | true |
| Glaze | 1278.28 | 0.294308 | 5130.22ms | 500299 | 40 | 4.82697e+07 | 373254 | 0.164304 | 2(Loss) | true |
| Jsonifier (two-stage) DID NOT CONVERGE | 1097.27 | 0.676184 | 5350.81ms | 500299 | 640 | 5.53278e+09 | 434828 | 8.04459 | -(Loss) | false |
| simdjson (reflection) | 1029.56 | 0.307072 | 5958.9ms | 500299 | 640 | 1.29603e+09 | 463423 | 0.138034 | 4(Loss) | true |
| simdjson (ondemand) | 922.014 | 1.0759 | 6179.7ms | 500299 | 40 | 1.23991e+09 | 517478 | 1.41311 | 5(Loss) | true |
