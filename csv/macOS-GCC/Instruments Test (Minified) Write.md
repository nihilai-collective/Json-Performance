
----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12582.3 | 0.445 | 798.939ms | 108313 | 1280 | 1.70834e+06 | 8209.6 | 1.76013 | 1(Win) | true |
| simdjson (reflection) | 8527.08 | 0.128408 | 1348.49ms | 108313 | 1280 | 309711 | 12113.8 | 0.248682 | 2(Loss) | true |
| Glaze | 1874.01 | 0.523881 | 6030.51ms | 108313 | 160 | 1.33415e+07 | 55120 | 0.231683 | 3(Loss) | true |
