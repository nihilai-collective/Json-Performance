
----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2676.85 | 0.556778 | 6427.1ms | 631514 | 160 | 2.51075e+08 | 224988 | 0.0113576 | 0.924744 | 1(Win) | true |
| simdjson (reflection) | 2424.11 | 0.108346 | 7017.79ms | 631514 | 640 | 4.6373e+07 | 248445 | 0.118984 | 1.02115 | 2(Loss) | true |
| Glaze | 1983.47 | 0.17943 | 8172.63ms | 631514 | 40 | 1.18731e+07 | 303638 | 0.226226 | 1.24811 | 3(Loss) | true |
| Jsonifier | 1970.33 | 0.082514 | 8471.43ms | 631514 | 1280 | 8.14245e+07 | 305665 | 0.386166 | 1.25641 | 4(Loss) | true |
| simdjson (ondemand) | 1411.62 | 0.112861 | 5776.78ms | 631514 | 320 | 7.41942e+07 | 426643 | 0.212672 | 1.75373 | 5(Loss) | true |
