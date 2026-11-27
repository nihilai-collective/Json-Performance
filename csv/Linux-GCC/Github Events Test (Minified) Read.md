
----
### Github Events Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 18345.9 | 0.0337228 | 998.331ms | 53331 | 1280 | 1118.76 | 2772.3 | 0.186489 | 0.285489 | 1.45394 | 0.08496 | 3.77653e-05 | 2.22666e-06 | 1.02544e-07 | 1(Win) | true |
| simdjson (stage-1) | 15382.1 | 0.0538516 | 1043.62ms | 53331 | 40 | 126.82 | 3306.47 | 0.0143678 | 0.33899 | 1.74743 | 0.0651966 | 0.00010688 | 1.87508e-06 | 0 | 2(Loss) | true |
