
----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3140.47 | 0.0373148 | 1005.55ms | 9378 | 2560 | 2890.91 | 2847.84 | 0.070278 | 1.66073 | 7.35114 | 1.3087 | 0.00202768 | 1.95354e-05 | 4.20699e-06 | 1(Win) | true |
| simdjson (ondemand) | 3118.23 | 0.0630508 | 1005.93ms | 9378 | 80 | 261.623 | 2868.15 | 0.00174325 | 1.6799 | 7.49712 | 1.16315 | 0.00147553 | 1.06633e-05 | 0 | 2(Loss) | true |
