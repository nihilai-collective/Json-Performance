
----
### Marine IK Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2582.21 | 0.0418861 | 897.339ms | 4604 | 320 | 162.321 | 1700.37 | 0.0687824 | 2.04316 | 9.16638 | 1.7487 | 0.00086881 | 1.62902e-05 | 4.7513e-06 | 1(Win) | true |
| simdjson (ondemand) | 2249.36 | 0.0445859 | 912.751ms | 4604 | 2560 | 1939.04 | 1951.98 | 0.0185074 | 2.33252 | 13.3165 | 2.35295 | 0.00109908 | 2.79988e-05 | 6.27851e-06 | 2(Loss) | true |
