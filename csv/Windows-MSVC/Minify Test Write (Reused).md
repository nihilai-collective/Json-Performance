
----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2863.74 | 0.0411856 | 7951.14ms | 466906 | 2560 | 1.04983e+07 | 155487 | 0.0472025 | 1.06109 | 1(Win) | true |
| Glaze | 1812.56 | 0.0691012 | 6258.87ms | 466906 | 640 | 1.84428e+07 | 245662 | 0.00273503 | 1.67669 | 2(Loss) | true |
| simdjson (ondemand) | 1441.77 | 0.11612 | 7904.49ms | 466906 | 320 | 4.11561e+07 | 308840 | 0.0797713 | 2.1077 | 3(Loss) | true |
