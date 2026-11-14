
----
### Marine IK Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7924.29 | 0.0969898 | 937.665ms | 18245 | 640 | 2902.68 | 2195.75 | 0.0426778 | 0.661211 | 3.22055 | 0.452179 | 0.00036337 | 5.39531e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 5753.14 | 0.0853539 | 1020ms | 18245 | 40 | 266.554 | 3024.4 | 0.0242531 | 0.907936 | 4.39693 | 0.636174 | 0.000360373 | 8.22143e-06 | 4.11072e-06 | 2(Loss) | true |
