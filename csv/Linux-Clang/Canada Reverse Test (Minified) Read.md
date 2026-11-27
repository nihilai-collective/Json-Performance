
----
### Canada Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 726.125 | 0.176699 | 8548.27ms | 2090234 | 30 | 7.05926e+08 | 2.74526e+06 | 0.0567238 | 6.98173 | 35.0793 | 6.98988 | 0.0276154 | 0.156661 | 0.000811153 | 1(Win) | true |
| simdjson (ondemand) | 698.453 | 0.135218 | 8898.2ms | 2090234 | 160 | 2.38288e+09 | 2.85403e+06 | 0.832021 | 7.27097 | 36.0909 | 6.61271 | 0.0227642 | 0.180149 | 0.00457126 | 2(Loss) | true |
