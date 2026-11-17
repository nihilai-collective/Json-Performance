
----
### Twitter Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5740.26 | 0.124916 | 762.146ms | 2821 | 320 | 109.681 | 468.675 | 0.136207 | 0.992042 | 3.838 | 0.485289 | 0.000631425 | 2.76941e-05 | 9.96987e-06 | 1(Win) | true |
| simdjson (ondemand) | 5490.44 | 0.0511937 | 769.939ms | 2821 | 2560 | 161.088 | 490 | 0.025437 | 1.02987 | 4.08401 | 0.437788 | 0.000412226 | 1.74473e-05 | 9.69293e-07 | 2(Loss) | true |
