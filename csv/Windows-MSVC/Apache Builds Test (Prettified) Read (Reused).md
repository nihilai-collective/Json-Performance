
----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1695.34 | 0.0974386 | 8666.72ms | 124597 | 640 | 2.985e+06 | 70089.2 | 0.2138 | 1.79208 | 1(Win) | true |
| Jsonifier | 1659.63 | 0.0685284 | 8834.21ms | 124597 | 640 | 1.54068e+06 | 71597.2 | 0.0690098 | 1.83074 | 2(Loss) | true |
| Glaze | 1479.94 | 0.0448771 | 9764.58ms | 124597 | 1280 | 1.66183e+06 | 80290.5 | 0.0186857 | 2.05308 | 3(Loss) | true |
| simdjson (ondemand) | 1376.69 | 0.0476416 | 5184.97ms | 124597 | 2560 | 4.3287e+06 | 86312.3 | 0.0334791 | 2.20711 | 4(Loss) | true |
