
----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5290.38 | 0.088371 | 1185.91ms | 24579 | 4890 | 74969.4 | 4430.76 | 0.120225 | 0.964267 | 2.97258 | 0.388625 | 0.000170029 | 1.38196e-05 | 4.32644e-06 | 1(Win) | true |
| Glaze | 3649.68 | 0.120787 | 1388.37ms | 24579 | 2560 | 154062 | 6422.57 | 0.0564037 | 1.39774 | 3.73734 | 0.480044 | 0.000341866 | 9.96468e-06 | 2.32032e-06 | 2(Loss) | true |
