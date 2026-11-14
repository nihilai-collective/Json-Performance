
----
### Canada Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8777.55 | 0.0726018 | 7350.46ms | 5212421 | 80 | 1.35244e+07 | 566326 | 0.0179743 | 0.586427 | 2.53322 | 0.311554 | 0.00200281 | 0.059099 | 2.15591e-06 | 1(Win) | true |
| simdjson (ondemand) | 8031.96 | 0.0783487 | 7996.39ms | 5212421 | 160 | 3.762e+07 | 618896 | 0.0712162 | 0.638645 | 2.77439 | 0.331079 | 0.00218097 | 0.0590791 | 6.95694e-06 | 2(Loss) | true |
