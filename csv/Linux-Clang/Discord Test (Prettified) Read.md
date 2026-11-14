
----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2519.18 | 0.0372128 | 3929.31ms | 83958 | 4890 | 684068 | 31783.6 | 0.0280837 | 2.00994 | 8.75913 | 1.54904 | 0.00425355 | 1.72157e-05 | 8.91233e-06 | 1(Win) | true |
| Glaze | 2188.99 | 0.0389228 | 4403.83ms | 83958 | 4890 | 991185 | 36577.9 | 0.0605765 | 2.30755 | 10.5709 | 2.16641 | 0.00638816 | 6.18505e-05 | 3.80485e-05 | 2(Loss) | true |
| Jsonifier | 1693.59 | 0.0820575 | 5493.71ms | 83958 | 1280 | 1.92645e+06 | 47277.6 | 0.0813859 | 2.98805 | 9.80381 | 2.1723 | 0.00865633 | 3.08655e-05 | 1.83779e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1379.42 | 0.0538649 | 6571.96ms | 83958 | 4890 | 4.78029e+06 | 58045.3 | 0.15769 | 3.65216 | 15.1337 | 2.45407 | 0.00809657 | 4.775e-05 | 2.75213e-05 | 4(Loss) | true |
