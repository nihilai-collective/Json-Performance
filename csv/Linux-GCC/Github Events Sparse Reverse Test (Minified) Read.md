
----
### Github Events Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6100.62 | 0.0282678 | 1568.01ms | 53331 | 2560 | 14217.9 | 8336.92 | 0.0903902 | 0.845516 | 4.13679 | 0.69108 | 0.00173336 | 4.56319e-06 | 1.73592e-06 | 1(Win) | true |
| simdjson (ondemand) | 4102.39 | 0.0205399 | 1981.24ms | 53331 | 4890 | 31709.6 | 12397.7 | 0.125844 | 1.25501 | 5.85733 | 0.957173 | 0.00232619 | 1.04874e-05 | 5.7863e-06 | 2(Loss) | true |
