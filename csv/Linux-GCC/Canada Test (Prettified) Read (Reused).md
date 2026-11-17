
----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2178.22 | 0.0403093 | 8259.87ms | 5212421 | 160 | 1.35396e+08 | 2.28212e+06 | 0.0172792 | 2.35955 | 10.8569 | 1.78258 | 0.0100525 | 0.0519095 | 0.000243349 | 1(Win) | true |
| Jsonifier (generic) | 2042.16 | 0.114258 | 8730.85ms | 5212421 | 160 | 1.23764e+09 | 2.43417e+06 | 0.315843 | 2.47991 | 11.1545 | 2.10082 | 0.00993631 | 0.0518829 | 0.000846582 | 2(Loss) | true |
