
----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 23208 | 0.0587913 | 1302.69ms | 136037 | 2560 | 27650.7 | 5590.1 | 0.0185071 | 0.21775 | 0.864574 | 0.124826 | 3.36851e-05 | 2.21964e-06 | 9.07382e-07 | 1(Win) | true |
| Glaze | 8197.84 | 0.0290912 | 2325.12ms | 136076 | 2560 | 54290.8 | 15830 | 0.0575187 | 0.616223 | 3.76371 | 0.630104 | 4.01373e-05 | 5.87907e-06 | 3.35865e-06 | 2(Loss) | true |
| simdjson (reflection) | 627.418 | 0.356711 | 5504.5ms | 136037 | 320 | 1.74094e+08 | 206776 | 0.0459616 | 7.98366 | 34.7199 | 7.11323 | 0.0272444 | 0.0265638 | 0.000178789 | 3(Loss) | true |
