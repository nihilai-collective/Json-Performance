
----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2337.27 | 0.121207 | 6638.18ms | 631514 | 160 | 1.56071e+07 | 257676 | 0.125937 | 1.05907 | 1(Win) | true |
| Glaze | 1918.54 | 0.0707415 | 8066.24ms | 631514 | 640 | 3.1561e+07 | 313915 | 0.000304124 | 1.29026 | 2(Loss) | true |
| Jsonifier | 1681.49 | 0.0579756 | 9170.29ms | 631514 | 640 | 2.75962e+07 | 358170 | 0.0565961 | 1.47218 | 3(Loss) | true |
| simdjson (ondemand) | 1234.87 | 0.0425989 | 6267.8ms | 631514 | 640 | 2.76247e+07 | 487709 | 0.158652 | 2.00471 | 4(Loss) | true |
