
----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3220.76 | 0.0283041 | 7425.26ms | 466906 | 2560 | 3.91995e+06 | 138252 | 0.00237994 | 1.56377 | 6.31155 | 1.25978 | 0.00185393 | 0.000113174 | 1.12995e-05 | 1(Win) | true |
| Glaze | 2548.92 | 0.155628 | 9355.53ms | 466906 | 30 | 2.2174e+06 | 174692 | 0.290144 | 1.98785 | 8.75349 | 1.96119 | 0.0025851 | 0.000906035 | 2.07751e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1867.58 | 0.145395 | 6293.94ms | 466906 | 320 | 3.84546e+07 | 238425 | 0.0410295 | 2.67747 | 11.992 | 1.5229 | 0.00474153 | 0.0908918 | 1.49722e-05 | 3(Loss) | true |
