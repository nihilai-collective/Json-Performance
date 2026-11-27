
----
### Prettify Test Write Results [(Here is the data we used for this test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5365.99 | 0.46576 | 6382.84ms | 699405 | 30 | 1.00555e+07 | 124302 | 0.453257 | 0.461282 | 1(Win) | true |
| Glaze | 3287.14 | 0.228626 | 5394.27ms | 699405 | 40 | 8.60856e+06 | 202913 | 0.0738216 | 0.753062 | 2(Loss) | true |
| simdjson (ondemand) | 2700.06 | 0.0452383 | 7083.84ms | 767297 | 1280 | 1.92398e+07 | 271013 | 0.186344 | 0.916814 | 3(Loss) | true |
