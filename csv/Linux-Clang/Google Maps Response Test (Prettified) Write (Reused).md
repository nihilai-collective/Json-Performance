
----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16248.6 | 0.0656219 | 919.532ms | 31235 | 2560 | 3705 | 1833.26 | 0.0197057 | 0.318337 | 1.40173 | 0.258844 | 4.80481e-05 | 6.71572e-06 | 2.81385e-06 | 1(Win) | true |
| Glaze | 5679.23 | 0.0487722 | 1264.36ms | 31235 | 4890 | 32000.6 | 5245.08 | 0.156777 | 0.897272 | 3.58448 | 0.627566 | 0.00227849 | 1.81617e-05 | 8.8255e-06 | 2(Loss) | true |
