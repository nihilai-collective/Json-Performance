
----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8062.26 | 0.0972061 | 5930.81ms | 500299 | 4890 | 1.61824e+07 | 59179.8 | 0.00945667 | 0.30689 | 1(Win) | true |
| Glaze | 3333.54 | 0.202849 | 7362.89ms | 500299 | 1280 | 1.07895e+08 | 143128 | 0.144255 | 0.74247 | 2(Loss) | true |
