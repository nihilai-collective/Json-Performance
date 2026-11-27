
----
### Google Maps Response Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1284.06 | 0.0460754 | 1613.14ms | 11812 | 2560 | 41827 | 8772.82 | 0.116408 | 3.98922 | 18.1686 | 3.39625 | 0.00512019 | 3.16812e-05 | 1.35588e-05 | 1(Win) | true |
| simdjson (ondemand) | 1045.34 | 0.0791464 | 1821.24ms | 11812 | 640 | 46556.3 | 10776.3 | 0.189699 | 4.93198 | 20.2722 | 3.51981 | 0.00900977 | 2.71175e-05 | 1.13761e-05 | 2(Loss) | true |
