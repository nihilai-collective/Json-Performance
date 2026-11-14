
----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 2699.67 | 0.609372 | 6270.95ms | 699405 | 1280 | 2.90142e+09 | 247069 | 0.54586 | 1.12562 | 1(Win) | true |
| Jsonifier | 2077.27 | 0.763251 | 8256.46ms | 699405 | 640 | 3.84404e+09 | 321097 | 0.444724 | 1.46237 | 2(Loss) | true |
| simdjson (ondemand) | 1324.59 | 0.436491 | 7117.86ms | 767297 | 640 | 3.7213e+09 | 552436 | 1.09316 | 2.29326 | 3(Loss) | true |
