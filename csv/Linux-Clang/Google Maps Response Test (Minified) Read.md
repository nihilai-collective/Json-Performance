
----
### Google Maps Response Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 10283.7 | 0.114334 | 819.698ms | 11812 | 2560 | 4015.45 | 1095.4 | 0.0586627 | 0.523607 | 2.58813 | 0.1915 | 8.53211e-05 | 1.16738e-05 | 5.22509e-06 | 1(Win) | true |
| simdjson (stage-1) | 9359 | 0.0935465 | 829.195ms | 11812 | 30 | 38.0333 | 1203.63 | 0.0776032 | 0.568732 | 2.59042 | 0.11683 | 0.000318885 | 2.25759e-05 | 5.64398e-06 | 2(Loss) | true |
