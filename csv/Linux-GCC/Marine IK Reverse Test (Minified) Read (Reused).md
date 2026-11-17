
----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 931.274 | 0.168792 | 6531.58ms | 1834197 | 30 | 3.01552e+08 | 1.87831e+06 | 0.214985 | 2.6585 | 1(Win) | true |
| Jsonifier (two-stage) | 841.829 | 0.101648 | 7219.7ms | 1834197 | 40 | 1.78446e+08 | 2.07789e+06 | 0.39677 | 2.94098 | 2(Loss) | true |
| Glaze | 710.204 | 0.147559 | 8513.26ms | 1834197 | 30 | 3.9626e+08 | 2.46299e+06 | 0.889776 | 3.48605 | 3(Loss) | true |
| simdjson (reflection) | 689.654 | 0.0560234 | 8547ms | 1834197 | 80 | 1.61532e+08 | 2.53638e+06 | 0.22718 | 3.58992 | 4(Loss) | true |
| simdjson (ondemand) | 624.538 | 0.171532 | 9771.22ms | 1834197 | 30 | 6.92447e+08 | 2.80083e+06 | 0.244268 | 3.96423 | 5(Loss) | true |
