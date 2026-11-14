
----
### Random Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2947.74 | 0.0543557 | 990.017ms | 8150 | 2560 | 5258.57 | 2636.75 | 0.000962942 | 1.7716 | 7.76859 | 1.34871 | 0.00297388 | 1.24617e-05 | 1.91718e-07 | 1(Win) | true |
| simdjson (ondemand) | 2434.18 | 0.0531961 | 1044.8ms | 8150 | 1280 | 3693.02 | 3193.05 | 0.0208994 | 2.14146 | 8.56871 | 1.42663 | 0.00483503 | 1.51457e-05 | 2.20475e-06 | 2(Loss) | true |
