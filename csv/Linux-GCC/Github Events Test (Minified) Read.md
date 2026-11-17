
----
### Github Events Test (Minified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16793.7 | 0.0347078 | 1024.97ms | 53331 | 4890 | 5402.94 | 3028.54 | 0.190593 | 0.309215 | 1.50764 | 0.0627028 | 5.60799e-05 | 3.13281e-06 | 2.72251e-07 | 1(Win) | true |
| simdjson (stage-1) | 14821.7 | 0.0776652 | 1061.62ms | 53331 | 40 | 284.102 | 3431.47 | 0.0177312 | 0.352376 | 1.73931 | 0.0650841 | 0.000112505 | 7.03156e-06 | 5.15648e-06 | 2(Loss) | true |
