
----
### Google Maps Response Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3513.09 | 0.0487137 | 1409.41ms | 25388 | 640 | 7213.73 | 6891.9 | 0.0643457 | 1.44903 | 6.91118 | 1.20935 | 0.00348842 | 7.81619e-06 | 1.96943e-06 | 1(Win) | true |
| simdjson (ondemand) | 3263.35 | 0.0967354 | 1469.12ms | 25388 | 30 | 1545.33 | 7419.33 | 0.00449297 | 1.58724 | 7.08803 | 1.14066 | 0.00370779 | 6.56478e-06 | 0 | 2(Loss) | true |
