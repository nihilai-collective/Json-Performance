
----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2758.59 | 0.368895 | 6708.8ms | 183677 | 40 | 2.19483e+06 | 63499.2 | 0.464843 | 0.897105 | 1(Win) | true |
| simdjson (ondemand) | 2592.88 | 0.0452822 | 6914.75ms | 183677 | 2560 | 2.39575e+06 | 67557.4 | 0.0265531 | 0.954457 | 2(Loss) | true |
