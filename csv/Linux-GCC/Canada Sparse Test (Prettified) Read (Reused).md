
----
### Canada Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 11420.1 | 0.220099 | 5656.51ms | 5212421 | 160 | 1.46857e+08 | 435280 | 0.103794 | 0.443041 | 1.96704 | 0.18129 | 0.00227705 | 0.0393858 | 2.1631e-06 | 1(Win) | true |
| simdjson (ondemand) | 9694.64 | 0.0720456 | 6671.58ms | 5212421 | 640 | 8.73393e+07 | 512752 | 0.467094 | 0.52551 | 2.27762 | 0.202778 | 0.00212416 | 0.0393925 | 4.7168e-06 | 2(Loss) | true |
