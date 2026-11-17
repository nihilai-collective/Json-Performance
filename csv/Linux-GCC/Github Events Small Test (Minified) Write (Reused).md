
----
### Github Events Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10078.9 | 0.128025 | 746.462ms | 1996 | 80 | 4.67706 | 188.863 | 0.152459 | 0.629791 | 1.30611 | 0.210421 | 0.001002 | 0 | 0 | 1(Win) | true |
| simdjson (reflection) | 7387.75 | 0.100256 | 752.975ms | 1996 | 2560 | 170.826 | 257.661 | 0.330011 | 0.794651 | 1.71744 | 0.233968 | 0.000501393 | 7.02577e-05 | 3.48353e-05 | 2(Loss) | true |
| Glaze | 6078.42 | 0.179073 | 757.804ms | 1996 | 1280 | 402.543 | 313.163 | 0.151946 | 0.942206 | 2.96042 | 0.462926 | 0.000501393 | 5.83198e-05 | 4.14892e-05 | 3(Loss) | true |
