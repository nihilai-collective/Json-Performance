
----
### Canada Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 849.689 | 0.128555 | 8460.71ms | 2090234 | 40 | 3.63836e+08 | 2.34604e+06 | 0.0554614 | 5.95589 | 27.8699 | 5.59548 | 0.0262562 | 0.130761 | 0.00137577 | 1(Win) | true |
| simdjson (ondemand) | 832.326 | 0.620363 | 8572.53ms | 2090234 | 80 | 1.76598e+10 | 2.39498e+06 | 0.107638 | 6.08524 | 29.4113 | 5.31785 | 0.0221291 | 0.154332 | 0.000843608 | 2(Loss) | true |
