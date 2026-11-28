
----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2076.57 | 0.144473 | 44.7111ms | 905 | 80 | 28.8449 | 415.625 | 0.00601468 | 1.11952 | 1(Win) | true |
| simdjson (reflection) | 265.473 | 0.325047 | 332.929ms | 905 | 2560 | 285884 | 3251.09 | 0.0318264 | 9.25166 | 2(Loss) | true |
| Glaze | 209.645 | 0.0260359 | 423.783ms | 905 | 80 | 91.91 | 4116.84 | 0.287922 | 11.7351 | 3(Loss) | true |
