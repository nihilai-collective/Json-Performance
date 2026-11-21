
----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 6111.47 | 0.114595 | 5650.61ms | 699405 | 640 | 1.0011e+07 | 109140 | 0.327197 | 0.404995 | 1(Win) | true |
| Glaze | 4047.97 | 0.133125 | 8494.84ms | 699405 | 640 | 3.0795e+07 | 164775 | 0.0234498 | 0.611494 | 2(Loss) | true |
| simdjson (ondemand) | 2487.76 | 0.200801 | 7594.91ms | 767297 | 160 | 5.58161e+07 | 294140 | 0.380815 | 0.994966 | 3(Loss) | true |
