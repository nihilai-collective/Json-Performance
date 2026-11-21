
----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 6002.65 | 0.118273 | 5698.97ms | 699405 | 2560 | 4.42163e+07 | 111118 | 0.325876 | 0.412334 | 1(Win) | true |
| Glaze | 4081.06 | 0.174018 | 8743.53ms | 699405 | 80 | 6.47127e+06 | 163439 | 0.0226053 | 0.606547 | 2(Loss) | true |
| simdjson (ondemand) | 2534.65 | 0.188758 | 7393.21ms | 767297 | 80 | 2.37569e+07 | 288699 | 0.0993368 | 0.976648 | 3(Loss) | true |
