
----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3544.89 | 0.0403784 | 986.908ms | 9378 | 1280 | 1328.38 | 2522.94 | 0.024457 | 1.47554 | 6.83365 | 1.18245 | 0.00215839 | 6.08139e-06 | 4.16533e-07 | 1(Win) | true |
| simdjson (ondemand) | 3365.64 | 0.0716041 | 985.963ms | 9378 | 80 | 289.635 | 2657.31 | 0.0362077 | 1.55412 | 7.03647 | 1.11772 | 0.00144221 | 5.33163e-06 | 2.66581e-06 | 2(Loss) | true |
