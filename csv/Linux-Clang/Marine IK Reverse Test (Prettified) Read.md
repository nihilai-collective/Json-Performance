
----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2715.55 | 0.0832361 | 8073.33ms | 7351818 | 160 | 7.38955e+08 | 2.58189e+06 | 0.379842 | 0.911695 | 1(Win) | true |
| Jsonifier | 2495.61 | 0.305789 | 8733.84ms | 7351818 | 30 | 2.21411e+09 | 2.80943e+06 | 0.323392 | 0.992043 | 2(Loss) | true |
| simdjson (ondemand) | 2281.46 | 0.0544743 | 9712.44ms | 7351818 | 80 | 2.24202e+08 | 3.07314e+06 | 0.0125742 | 1.08518 | 3(Loss) | true |
| Glaze | 2085.68 | 0.091223 | 5016.85ms | 7351818 | 30 | 2.82113e+08 | 3.3616e+06 | 1.42211 | 1.18704 | 4(Loss) | true |
