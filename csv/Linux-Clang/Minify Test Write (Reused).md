
----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3888.21 | 0.129408 | 5819.38ms | 466906 | 1280 | 2.81121e+07 | 114520 | 0.348249 | 0.636545 | 1(Win) | true |
| Glaze | 2468.96 | 0.135108 | 9219.76ms | 466906 | 320 | 1.89996e+07 | 180350 | 0.147742 | 1.0026 | 2(Loss) | true |
| simdjson (ondemand) | 1685.55 | 0.102806 | 6712.6ms | 466906 | 640 | 4.72058e+07 | 264173 | 0.249928 | 1.46863 | 3(Loss) | true |
