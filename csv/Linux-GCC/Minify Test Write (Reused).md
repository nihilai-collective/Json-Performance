
----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22070.6 | 0.177834 | 2061.39ms | 466906 | 640 | 823838 | 20175.1 | 0.18393 | 0.112023 | 1(Win) | true |
| simdjson (ondemand) | 18016.4 | 0.145337 | 2480.29ms | 466906 | 4890 | 6.30932e+06 | 24715 | 0.00977959 | 0.137254 | 2(Loss) | true |
| Glaze | 2662.81 | 0.256161 | 8280.39ms | 466906 | 80 | 1.4679e+07 | 167221 | 0.0318863 | 0.929583 | 3(Loss) | true |
