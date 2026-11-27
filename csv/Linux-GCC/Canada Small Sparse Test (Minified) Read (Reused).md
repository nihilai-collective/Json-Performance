
----
### Canada Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8102.5 | 0.0839756 | 769.343ms | 4630 | 2560 | 536.13 | 544.957 | 0.255173 | 0.679832 | 3.47819 | 0.485313 | 0.000432219 | 1.32458e-05 | 2.86852e-06 | 1(Win) | true |
| simdjson (ondemand) | 6735.78 | 0.16037 | 778.833ms | 4630 | 160 | 176.829 | 655.531 | 0.253918 | 0.811282 | 4.08013 | 0.485313 | 0.000431965 | 2.29482e-05 | 1.07991e-05 | 2(Loss) | true |
