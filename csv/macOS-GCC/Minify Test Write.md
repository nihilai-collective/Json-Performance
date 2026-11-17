
----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2295.5 | 0.568408 | 10384.2ms | 466906 | 40 | 4.86277e+07 | 193978 | 0.356157 | 1(Win) | true |
| Glaze | 1579.64 | 0.665125 | 7741.09ms | 466906 | 80 | 2.81216e+08 | 281885 | 0.482513 | 2(Loss) | true |
| simdjson (ondemand) | 1229.14 | 0.598842 | 9937.12ms | 466906 | 30 | 1.41189e+08 | 362266 | 0.499503 | 3(Loss) | true |
