
----
### Instruments Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3003.76 | 0.076694 | 151.772ms | 4669 | 80 | 103.402 | 1482.38 | 0.107819 | 0.809925 | 1(Win) | true |
| Jsonifier (two-stage) | 2342.3 | 0.0955001 | 196.842ms | 4669 | 80 | 263.671 | 1901 | 0.00657592 | 1.04257 | 2(Loss) | true |
| Glaze | 1670.78 | 0.155379 | 269.415ms | 4669 | 4890 | 83849.3 | 2665.04 | 0.072535 | 1.46748 | 3(Loss) | true |
| simdjson (ondemand) | 622.313 | 0.145119 | 720.655ms | 4669 | 4890 | 527216 | 7155.09 | 0.0866154 | 3.96276 | 4(Loss) | true |
