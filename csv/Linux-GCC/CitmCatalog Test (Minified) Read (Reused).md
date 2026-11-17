
----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2485.9 | 0.137791 | 5832.78ms | 500299 | 160 | 1.11906e+07 | 191931 | 0.129234 | 0.995792 | 1(Win) | true |
| Jsonifier (two-stage) | 2136.66 | 0.106776 | 6574.8ms | 500299 | 320 | 1.81921e+07 | 223302 | 0.139128 | 1.15857 | 2(Loss) | true |
| simdjson (ondemand) | 1864.04 | 0.376797 | 7355.58ms | 500299 | 30 | 2.79053e+07 | 255962 | 0.0218831 | 1.32804 | 3(Loss) | true |
| Glaze | 1820.18 | 0.123105 | 7557.26ms | 500299 | 1280 | 1.33287e+08 | 262129 | 0.373698 | 1.36006 | 4(Loss) | true |
| simdjson (reflection) | 1744.61 | 0.136154 | 7873.29ms | 500299 | 320 | 4.43684e+07 | 273483 | 0.768495 | 1.41897 | 5(Loss) | true |
