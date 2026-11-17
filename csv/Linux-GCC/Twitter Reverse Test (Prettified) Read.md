
----
### Twitter Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 852.882 | 0.130332 | 5229ms | 360584 | 640 | 1.76732e+08 | 403198 | 0.0691928 | 5.98354 | 22.046 | 4.19885 | 0.0173682 | 0.00373803 | 4.50398e-05 | 1(Win) | true |
| simdjson (ondemand) | 436.303 | 0.161648 | 5009.08ms | 360584 | 80 | 1.29857e+08 | 788168 | 0.014706 | 11.5344 | 46.8979 | 9.4643 | 0.0564554 | 0.00468584 | 4.51698e-05 | 2(Loss) | true |
