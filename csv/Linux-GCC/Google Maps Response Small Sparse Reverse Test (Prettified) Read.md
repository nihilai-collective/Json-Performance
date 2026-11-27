
----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3391.26 | 0.0443939 | 991.692ms | 9378 | 1280 | 1754.51 | 2637.24 | 0.229914 | 1.54274 | 6.99829 | 1.22073 | 0.0022986 | 2.99904e-05 | 1.45787e-05 | 1(Win) | true |
| simdjson (ondemand) | 3207.11 | 0.0917602 | 997.861ms | 9378 | 30 | 196.437 | 2788.67 | 0.0227058 | 1.59957 | 7.1768 | 1.15067 | 0.00150352 | 0 | 0 | 2(Loss) | true |
