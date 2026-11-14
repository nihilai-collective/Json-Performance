
----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20499.9 | 0.0844767 | 1245.58ms | 108313 | 640 | 11596.1 | 5038.81 | 0.0656036 | 0.248398 | 1.08875 | 0.287694 | 0.000109434 | 6.60701e-06 | 4.12577e-06 | 1(Win) | true |
| simdjson (reflection) | 15531.2 | 0.0895633 | 1401.7ms | 108313 | 640 | 22708.6 | 6650.82 | 0.0408011 | 0.327118 | 1.48913 | 0.192645 | 0.000177783 | 1.61136e-05 | 1.08915e-05 | 2(Loss) | true |
| Glaze | 6577.11 | 0.0531397 | 2313.15ms | 108313 | 4890 | 340595 | 15705.3 | 0.0147906 | 0.769572 | 2.97166 | 0.386768 | 0.000255185 | 1.09997e-05 | 7.62578e-06 | 3(Loss) | true |
