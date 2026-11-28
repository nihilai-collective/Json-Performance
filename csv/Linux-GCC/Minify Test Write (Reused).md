
----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21135.2 | 0.10249 | 2107.91ms | 466906 | 4890 | 2.27991e+06 | 21068 | 0.209755 | 0.116962 | 1(Win) | true |
| simdjson (ondemand) | 17408.6 | 0.37523 | 2606.67ms | 466906 | 160 | 1.47383e+06 | 25578 | 0.0613697 | 0.142063 | 2(Loss) | true |
| Glaze | 2653.86 | 0.172829 | 8660.59ms | 466906 | 80 | 6.72703e+06 | 167784 | 0.321232 | 0.93272 | 3(Loss) | true |
