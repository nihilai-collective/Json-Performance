
----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2531.35 | 0.0268977 | 507.601ms | 9578 | 160 | 150.728 | 3608.46 | 0.160645 | 0.970798 | 1(Win) | true |
| Glaze | 1907.63 | 0.225788 | 630.551ms | 9578 | 1280 | 149614 | 4788.29 | 0.0309607 | 1.29042 | 2(Loss) | true |
| simdjson (ondemand) | 1561.21 | 0.0408651 | 733.611ms | 9578 | 30 | 171.495 | 5850.77 | 0.112679 | 1.57851 | 3(Loss) | true |
| Jsonifier (two-stage) | 1260.72 | 0.227936 | 867.882ms | 9578 | 640 | 174548 | 7245.27 | 0.0501153 | 1.95641 | 4(Loss) | true |
