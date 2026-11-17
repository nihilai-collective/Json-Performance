
----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 2555.4 | 0.173148 | 6675.64ms | 699405 | 40 | 8.1702e+06 | 261018 | 0.0622176 | 1.18928 | 1(Win) | true |
| Jsonifier | 2405.8 | 0.0475415 | 7080.82ms | 699405 | 1280 | 2.22379e+07 | 277248 | 0.162517 | 1.26278 | 2(Loss) | true |
| simdjson (ondemand) | 1451.86 | 0.224701 | 6404.02ms | 767297 | 320 | 4.10428e+08 | 504009 | 0.177083 | 2.09263 | 3(Loss) | true |
