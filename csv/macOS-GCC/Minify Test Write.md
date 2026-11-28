
----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 7536.22 | 0.111169 | 6407.8ms | 466906 | 1280 | 5.52238e+06 | 59084.8 | 0.288916 | 1(Win) | true |
| Jsonifier | 7090.34 | 0.40488 | 6640.13ms | 466906 | 640 | 4.13769e+07 | 62800.4 | 1.73466 | 2(Loss) | true |
| Glaze | 1835.63 | 0.123359 | 6751.7ms | 466906 | 640 | 5.73076e+07 | 242574 | 1.71439 | 3(Loss) | true |
