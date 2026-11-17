
----
### Canada Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 725.945 | 0.479607 | 8538.18ms | 2090234 | 160 | 2.77507e+10 | 2.74594e+06 | 0.460488 | 6.96104 | 35.6642 | 7.02223 | 0.0230406 | 0.154874 | 0.000237067 | 1(Win) | true |
| simdjson (ondemand) | 691.528 | 0.180048 | 9066.8ms | 2090234 | 160 | 4.30991e+09 | 2.88261e+06 | 0.175511 | 7.32005 | 36.0929 | 6.61299 | 0.0229803 | 0.17814 | 0.000215697 | 2(Loss) | true |
