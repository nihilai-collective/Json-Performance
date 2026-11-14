
----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 740.051 | 0.160224 | 117.853ms | 905 | 4890 | 17074.2 | 1166.24 | 0.314949 | 4.04676 | 1(Win) | true |
| Glaze | 722.617 | 0.136135 | 124.66ms | 905 | 320 | 846.003 | 1194.38 | 0.314961 | 4.1318 | 2(Loss) | true |
| Jsonifier (two-stage) | 272.947 | 0.0792876 | 318.97ms | 905 | 4890 | 30737 | 3162.07 | 0.00849405 | 11.0647 | 3(Loss) | true |
| simdjson (ondemand) | 123.004 | 0.0986288 | 694.542ms | 905 | 30 | 1436.78 | 7016.67 | 0.142315 | 24.6274 | 4(Loss) | true |
