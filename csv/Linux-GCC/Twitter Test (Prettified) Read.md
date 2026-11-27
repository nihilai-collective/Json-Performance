
----
### Twitter Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2237.08 | 0.22175 | 6871.36ms | 631514 | 320 | 1.14046e+08 | 269217 | 0.171545 | 1.10654 | 1(Win) | true |
| simdjson (reflection) | 2096.36 | 0.308204 | 7392.15ms | 631514 | 80 | 6.27193e+07 | 287287 | 0.147648 | 1.18083 | 2(Loss) | true |
| Jsonifier (two-stage) | 2034.04 | 0.175271 | 7582.21ms | 631514 | 160 | 4.3091e+07 | 296090 | 0.0561019 | 1.217 | 3(Loss) | true |
| Glaze | 1700.9 | 0.270507 | 8996.95ms | 631514 | 80 | 7.33926e+07 | 354081 | 0.133319 | 1.45541 | 4(Loss) | true |
| simdjson (ondemand) | 1291.66 | 0.0884031 | 6045.16ms | 631514 | 320 | 5.43695e+07 | 466268 | 1.39696 | 1.91658 | 5(Loss) | true |
