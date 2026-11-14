
----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3285.84 | 0.102639 | 7354.47ms | 466906 | 1280 | 2.47628e+07 | 135513 | 0.167503 | 1.54446 | 6.31273 | 1.26005 | 0.0018468 | 0.00198381 | 4.45335e-05 | 1(Win) | true |
| Glaze | 2494.17 | 0.120093 | 9518.8ms | 466906 | 320 | 1.47092e+07 | 178527 | 0.227267 | 2.03421 | 8.75464 | 1.96145 | 0.00256937 | 0.00370289 | 3.91808e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1878.31 | 1.14447 | 6350.69ms | 466906 | 160 | 1.17774e+09 | 237062 | 0.175991 | 2.69398 | 11.9921 | 1.52294 | 0.00493318 | 0.078269 | 0.000220909 | 3(Loss) | true |
