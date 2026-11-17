
----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 1553.62 | 0.642961 | 7031.68ms | 728486 | 80 | 6.61323e+08 | 447174 | 1.28434 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1546.35 | 0.882055 | 7816.62ms | 728486 | 320 | 5.02534e+09 | 449275 | 0.850848 | 1(Tie) | true |
| Glaze | 1329.8 | 0.357244 | 8778.08ms | 728486 | 640 | 2.22934e+09 | 522437 | 1.17583 | 3(Loss) | true |
| simdjson (reflection) | 1289.29 | 0.47366 | 8308.87ms | 728486 | 40 | 2.60577e+08 | 538854 | 1.86031 | 4(Loss) | true |
| simdjson (ondemand) | 1132.68 | 0.4549 | 9378.46ms | 728486 | 320 | 2.49121e+09 | 613358 | 2.7629 | 5(Loss) | true |
