
----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4449.57 | 0.144133 | 5453.7ms | 466906 | 640 | 1.33146e+07 | 100072 | 1.6822 | 0.556279 | 1(Win) | true |
| Glaze | 2482.25 | 0.359678 | 8916.27ms | 466906 | 30 | 1.24887e+07 | 179384 | 0.0802102 | 0.99725 | 2(Loss) | true |
| simdjson (ondemand) | 1888.28 | 0.0796746 | 5961.66ms | 466906 | 1280 | 4.51832e+07 | 235811 | 0.206086 | 1.31096 | 3(Loss) | true |
