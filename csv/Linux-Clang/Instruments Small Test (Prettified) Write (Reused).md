
----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15781.7 | 0.30258 | 786.47ms | 9249 | 2560 | 7321.55 | 558.909 | 0.303311 | 0.345425 | 1.16791 | 0.2783 | 0.000108711 | 8.15122e-06 | 8.8692e-07 | 1(Win) | true |
| Glaze | 2681.52 | 0.378214 | 1070.65ms | 9249 | 320 | 49528.5 | 3289.38 | 0.0458652 | 1.90823 | 3.62255 | 0.590443 | 0.00038146 | 1.65558e-05 | 2.02725e-06 | 2(Loss) | true |
