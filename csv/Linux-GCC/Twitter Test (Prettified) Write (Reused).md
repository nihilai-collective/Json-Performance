
----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20989.1 | 0.122402 | 4092.61ms | 716365 | 80 | 126984 | 32549.3 | 0.130899 | 0.241003 | 0.715267 | 0.0981888 | 0.000177703 | 0.0075465 | 1.19527e-05 | 1(Win) | true |
| Glaze | 6543.64 | 0.170487 | 5744.81ms | 716365 | 1280 | 4.0553e+07 | 104403 | 0.104953 | 0.776612 | 2.69622 | 0.435824 | 0.000335361 | 0.00611656 | 2.53079e-05 | 2(Loss) | true |
| simdjson (reflection) | 510.571 | 0.361927 | 8481.27ms | 716365 | 160 | 3.75248e+09 | 1.33807e+06 | 0.0639609 | 9.78733 | 30.5956 | 6.83535 | 0.0704912 | 0.290488 | 0.000958066 | 3(Loss) | true |
