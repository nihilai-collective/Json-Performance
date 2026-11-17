
----
### Canada Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8569.78 | 0.165241 | 7565.26ms | 5212421 | 40 | 3.67484e+07 | 580056 | 0.0342944 | 0.595212 | 2.53322 | 0.311554 | 0.00202233 | 0.0590989 | 5.16555e-06 | 1(Win) | true |
| simdjson (ondemand) | 7987.56 | 0.0656996 | 8103.55ms | 5212421 | 640 | 1.06993e+08 | 622337 | 0.406053 | 0.637081 | 2.7744 | 0.33108 | 0.00217864 | 0.0590752 | 5.63078e-06 | 2(Loss) | true |
