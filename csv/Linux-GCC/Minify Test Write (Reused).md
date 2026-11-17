
----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4191.74 | 0.630699 | 5555.81ms | 466906 | 30 | 1.34659e+07 | 106227 | 0.0625626 | 0.590456 | 1(Win) | true |
| Glaze | 2637.77 | 0.274095 | 9076.27ms | 466906 | 30 | 6.42255e+06 | 168808 | 0.0721603 | 0.93848 | 2(Loss) | true |
| simdjson (ondemand) | 1913.13 | 0.160403 | 5886.79ms | 466906 | 80 | 1.11503e+07 | 232748 | 0.904782 | 1.29396 | 3(Loss) | true |
