
----
### CitmCatalog Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5471.73 | 0.246414 | 5358.81ms | 1151920 | 80 | 1.95801e+07 | 200769 | 0.079389 | 0.931063 | 5.06859 | 0.781291 | 0.00175745 | 0.0105796 | 8.03007e-07 | 1(Win) | true |
| Jsonifier (generic) | 5411.54 | 0.309169 | 5412.86ms | 1151920 | 40 | 1.57564e+07 | 203003 | 0.0866643 | 0.951041 | 4.96371 | 0.801993 | 0.00150573 | 0.00979996 | 4.03023e-05 | 2(Loss) | true |
