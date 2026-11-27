
----
### Marine IK Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7936.08 | 0.0990799 | 937.378ms | 18245 | 2560 | 12080.5 | 2192.49 | 0.0818176 | 0.659226 | 3.10869 | 0.4792 | 0.000282291 | 8.34989e-06 | 1.9269e-06 | 1(Win) | true |
| simdjson (ondemand) | 6713.9 | 0.150496 | 981.212ms | 18245 | 160 | 2433.93 | 2591.61 | 0.107203 | 0.777235 | 4.27832 | 0.634859 | 0.000293574 | 3.35708e-05 | 2.32941e-05 | 2(Loss) | true |
