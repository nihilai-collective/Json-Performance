
----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2039.26 | 0.521801 | 5259.77ms | 466906 | 160 | 2.07704e+08 | 218352 | 1.11286 | 1(Win) | true |
| Glaze | 1425.3 | 0.698937 | 7888.79ms | 466906 | 160 | 7.62852e+08 | 312408 | 3.97961 | 2(Loss) | true |
| simdjson (ondemand) | 1106.9 | 0.525304 | 5230.11ms | 466906 | 80 | 3.57233e+08 | 402272 | 0.266569 | 3(Loss) | true |
