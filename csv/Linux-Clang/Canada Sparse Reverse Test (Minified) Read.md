
----
### Canada Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5961.27 | 0.157454 | 8698.61ms | 2090234 | 80 | 2.21772e+07 | 334392 | 0.0237166 | 0.846776 | 4.69133 | 0.718822 | 0.00266517 | 0.0763064 | 1.33956e-06 | 1(Win) | true |
| simdjson (ondemand) | 4945.86 | 0.147138 | 5298.29ms | 2090234 | 40 | 1.40674e+07 | 403044 | 0.706098 | 1.02894 | 5.09756 | 0.738336 | 0.00304328 | 0.0758865 | 4.78415e-07 | 2(Loss) | true |
