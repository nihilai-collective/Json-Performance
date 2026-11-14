
----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3301.85 | 0.101078 | 7329.83ms | 466906 | 320 | 5.94577e+06 | 134857 | 0.0567271 | 1.54601 | 6.31155 | 1.25978 | 0.00184325 | 0.00171222 | 3.45359e-05 | 1(Win) | true |
| Glaze | 2494.6 | 0.165256 | 9560.33ms | 466906 | 640 | 5.56865e+07 | 178496 | 0.0427356 | 2.03605 | 8.75349 | 1.96119 | 0.00261625 | 0.0035695 | 3.42916e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1856.43 | 0.407818 | 6388.77ms | 466906 | 1280 | 1.22474e+09 | 239857 | 0.0768105 | 2.73459 | 11.9918 | 1.52286 | 0.00487851 | 0.0948458 | 0.000272561 | 3(Loss) | true |
