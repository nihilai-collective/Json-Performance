
----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2663.33 | 0.782092 | 6140.49ms | 699405 | 320 | 1.22764e+09 | 250440 | 1.42359 | 1(Win) | true |
| Glaze | 2087.54 | 0.24936 | 8194.92ms | 699405 | 1280 | 8.12555e+08 | 319518 | 0.854682 | 2(Loss) | true |
| simdjson (ondemand) | 1651.25 | 0.262415 | 5767.88ms | 767297 | 40 | 5.40922e+07 | 443149 | 0.199699 | 3(Loss) | true |
