
----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21674.5 | 0.0651248 | 2084.11ms | 466906 | 40 | 7159.99 | 20543.8 | 0.395269 | 0.114069 | 1(Win) | true |
| simdjson (ondemand) | 17839.9 | 0.790358 | 2501.03ms | 466906 | 30 | 1.16747e+06 | 24959.6 | 0.322943 | 0.138624 | 2(Loss) | true |
| Glaze | 2603.93 | 0.425473 | 8858.81ms | 466906 | 30 | 1.58805e+07 | 171002 | 0.205384 | 0.950631 | 3(Loss) | true |
