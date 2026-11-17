
----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 966.5 | 0.0878234 | 8354.91ms | 2251027 | 160 | 6.08834e+08 | 2.22116e+06 | 0.194812 | 2.56158 | 1(Win) | true |
| Glaze | 855.413 | 0.145558 | 9461.54ms | 2251027 | 40 | 5.33755e+08 | 2.5096e+06 | 0.0644205 | 2.8942 | 2(Loss) | true |
| Jsonifier (two-stage) | 849.369 | 0.172158 | 9372.27ms | 2251027 | 40 | 7.57324e+08 | 2.52746e+06 | 0.419447 | 2.91482 | 3(Loss) | true |
| simdjson (ondemand) | 832.766 | 0.153019 | 9654.91ms | 2251027 | 40 | 6.22391e+08 | 2.57785e+06 | 0.191016 | 2.9729 | 4(Loss) | true |
