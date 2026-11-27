
----
### Google Maps Response Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1403.1 | 0.0719432 | 1596.24ms | 11812 | 320 | 10675.7 | 8028.48 | 0.128672 | 3.6889 | 17.0736 | 3.15044 | 0.00474253 | 1.11116e-05 | 1.05825e-06 | 1(Win) | true |
| simdjson (ondemand) | 1106.63 | 0.0463346 | 1802.74ms | 11812 | 2560 | 56949.3 | 10179.3 | 0.0917877 | 4.62807 | 19.2106 | 3.28209 | 0.00807081 | 3.7237e-05 | 1.61382e-05 | 2(Loss) | true |
