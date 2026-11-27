
----
### Marine IK Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3987.53 | 0.465115 | 829.525ms | 4604 | 320 | 8393.32 | 1101.11 | 0.248091 | 1.34017 | 6.42268 | 0.994353 | 0.000663825 | 1.35752e-05 | 1.35752e-06 | 1(Win) | true |
| simdjson (ondemand) | 3903.18 | 0.0793258 | 833.022ms | 4604 | 2560 | 2038.45 | 1124.91 | 0.0770797 | 1.36679 | 6.82732 | 0.941573 | 0.000659158 | 1.91749e-05 | 3.2241e-06 | 2(Loss) | true |
