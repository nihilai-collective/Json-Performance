
----
### Google Maps Response Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3421.76 | 0.0743153 | 1433.78ms | 25388 | 640 | 17696.8 | 7075.85 | 0.023203 | 1.51525 | 7.19387 | 1.27241 | 0.00365453 | 1.19397e-05 | 5.9083e-06 | 1(Win) | true |
| simdjson (ondemand) | 3262.71 | 0.0511058 | 1466.28ms | 25388 | 1280 | 18409.9 | 7420.79 | 0.0430299 | 1.58216 | 7.20648 | 1.16303 | 0.00342355 | 7.84697e-06 | 1.63094e-06 | 2(Loss) | true |
