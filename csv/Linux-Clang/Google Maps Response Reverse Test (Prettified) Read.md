
----
### Google Maps Response Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1541.92 | 0.0358502 | 2303.46ms | 25388 | 1280 | 40562.7 | 15702.4 | 0.0779198 | 3.34742 | 14.9805 | 2.93556 | 0.00738778 | 2.14791e-05 | 8.40087e-06 | 1(Win) | true |
| simdjson (ondemand) | 1401.88 | 0.023814 | 2460.16ms | 25388 | 2560 | 43305.1 | 17271 | 0.0499756 | 3.67765 | 16.0666 | 2.87835 | 0.00640912 | 1.96482e-05 | 7.12381e-06 | 2(Loss) | true |
