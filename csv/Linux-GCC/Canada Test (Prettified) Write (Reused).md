
----
### Canada Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5638.18 | 0.0565338 | 7147.46ms | 6661989 | 160 | 6.49332e+07 | 1.12685e+06 | 0.106079 | 0.439095 | 1(Win) | true |
| Glaze | 3404.12 | 0.0860068 | 5773.3ms | 6661897 | 30 | 7.72992e+07 | 1.86635e+06 | 0.00193965 | 0.727279 | 2(Loss) | true |
| simdjson (reflection) | 421.111 | 0.268745 | 10631.2ms | 6661989 | 30 | 4.93191e+10 | 1.50871e+07 | 0.0690249 | 5.87907 | 3(Loss) | true |
