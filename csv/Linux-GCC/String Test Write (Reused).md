
----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11023.8 | 0.126241 | 833.795ms | 9578 | 2560 | 2801.07 | 828.596 | 0.0442006 | 0.481174 | 2.23585 | 0.274588 | 0.000820321 | 1.54162e-05 | 4.40463e-06 | 1(Win) | true |
| simdjson (reflection) | 9526.21 | 0.111925 | 854.034ms | 9578 | 2560 | 2948.52 | 958.859 | 0.214254 | 0.55383 | 3.07329 | 0.321257 | 0.000105711 | 3.03838e-05 | 1.50899e-05 | 2(Loss) | true |
| Glaze | 5810.94 | 0.0803756 | 909.114ms | 9578 | 80 | 127.701 | 1571.91 | 0.121519 | 0.892786 | 4.44801 | 0.720192 | 0.000254489 | 1.30507e-05 | 0 | 3(Loss) | true |
