
----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2216.14 | 0.179167 | 1616ms | 18245 | 160 | 31661.5 | 7851.41 | 0.078471 | 2.33319 | 9.66994 | 1.66633 | 0.00320841 | 3.1858e-05 | 1.57577e-05 | 1(Win) | true |
| Jsonifier (generic) | 2154.79 | 0.0854072 | 1659.45ms | 18245 | 80 | 3805.02 | 8074.94 | 0.114528 | 2.4031 | 9.26101 | 1.7556 | 0.00258975 | 1.43875e-05 | 2.74048e-06 | 2(Loss) | true |
