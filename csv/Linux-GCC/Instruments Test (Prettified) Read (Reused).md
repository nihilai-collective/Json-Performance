
----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2652.79 | 0.05392 | 7510.36ms | 183677 | 640 | 811304 | 66031.7 | 0.0560851 | 1.92673 | 8.42444 | 1.60165 | 0.00198029 | 4.09176e-06 | 1.95656e-06 | 1(Win) | true |
| simdjson (ondemand) | 2553.86 | 0.0677206 | 7756.8ms | 183677 | 640 | 1.38082e+06 | 68589.6 | 0.161303 | 1.98688 | 9.20961 | 1.41372 | 0.00419874 | 1.68264e-05 | 1.11949e-05 | 2(Loss) | true |
