
----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 384.947 | 0.4033 | 371.093ms | 1313 | 1280 | 220290 | 3252.85 | 0.00120086 | 6.38072 | 1(Win) | true |
| simdjson (reflection) | 372.832 | 0.112468 | 336.356ms | 1313 | 40 | 570.715 | 3358.55 | 0.272185 | 6.59099 | 2(Loss) | true |
| Glaze | 316.312 | 0.168668 | 392.923ms | 1313 | 30 | 1337.47 | 3958.67 | 0.278646 | 7.77492 | 3(Loss) | true |
