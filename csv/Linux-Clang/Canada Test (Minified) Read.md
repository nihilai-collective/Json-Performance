
----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 839.886 | 0.253965 | 8015.14ms | 2251027 | 160 | 6.742e+09 | 2.556e+06 | 1.41738 | 2.94775 | 1(Win) | true |
| Jsonifier (two-stage) | 796.076 | 0.374042 | 8655.14ms | 2251027 | 30 | 3.05222e+09 | 2.69666e+06 | 0.679015 | 3.10998 | 2(Loss) | true |
| Glaze | 777.94 | 0.0925109 | 8961.38ms | 2251027 | 30 | 1.95514e+08 | 2.75953e+06 | 1.10809 | 3.18249 | 3(Loss) | true |
| simdjson (ondemand) | 691.67 | 0.123896 | 9220.96ms | 2251027 | 30 | 4.43606e+08 | 3.10372e+06 | 1.45024 | 3.57925 | 4(Loss) | true |
