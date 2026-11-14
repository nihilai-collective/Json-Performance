
----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2837.09 | 1.6269 | 6022.64ms | 699405 | 30 | 4.3889e+08 | 235102 | 1.61546 | 1(Win) | true |
| Glaze | 2194.91 | 0.408763 | 7585.39ms | 699405 | 160 | 2.4688e+08 | 303886 | 0.605487 | 2(Loss) | true |
| simdjson (ondemand) | 1644.01 | 0.233585 | 5808.24ms | 767297 | 40 | 4.32383e+07 | 445101 | 0.00814863 | 3(Loss) | true |
