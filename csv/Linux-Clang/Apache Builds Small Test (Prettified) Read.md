
----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2266.97 | 0.0778993 | 863.399ms | 3370 | 320 | 390.287 | 1417.7 | 0.0742291 | 2.34281 | 9.11424 | 1.64955 | 0.000617582 | 4.08012e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1950.8 | 0.0518307 | 887.695ms | 3370 | 2560 | 1866.58 | 1647.47 | 0.0496018 | 2.70389 | 9.89021 | 1.69525 | 0.00314262 | 4.38149e-05 | 1.69232e-05 | 2(Loss) | true |
