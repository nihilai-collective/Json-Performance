
----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8854.35 | 0.0859828 | 5271.61ms | 1834197 | 640 | 1.84664e+07 | 197556 | 0.00658165 | 0.578732 | 2.89621 | 0.126786 | 0.00184286 | 0.0377792 | 4.42973e-06 | 1(Win) | true |
| simdjson (stage-1) | 7035.47 | 0.13586 | 6558.29ms | 1834197 | 30 | 3.42302e+06 | 248630 | 0.0595484 | 0.731756 | 3.29419 | 0.16035 | 0.00522728 | 0.0375697 | 3.63465e-06 | 2(Loss) | true |
