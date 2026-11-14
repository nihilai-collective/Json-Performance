
----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13510.3 | 0.0868375 | 767.63ms | 108313 | 2560 | 112846 | 7645.66 | 0.0127711 | 0.224234 | 1(Win) | true |
| Glaze | 3953.39 | 0.128163 | 2653.91ms | 108313 | 4890 | 5.48347e+06 | 26128.3 | 1.1567 | 0.768012 | 2(Loss) | true |
