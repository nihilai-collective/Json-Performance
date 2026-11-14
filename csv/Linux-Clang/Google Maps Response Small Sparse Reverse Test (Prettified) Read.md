
----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3100.55 | 0.0518557 | 1017.68ms | 9378 | 2560 | 5727.65 | 2884.51 | 0.00426561 | 1.66223 | 7.49744 | 1.16293 | 0.0018215 | 2.55335e-05 | 1.45787e-05 | 1(Win) | true |
| Jsonifier (generic) | 3011.41 | 0.0682454 | 1031.37ms | 9378 | 2560 | 10516.4 | 2969.89 | 0.0778305 | 1.70452 | 7.35114 | 1.3087 | 0.00185057 | 2.43255e-05 | 8.78885e-06 | 2(Loss) | true |
