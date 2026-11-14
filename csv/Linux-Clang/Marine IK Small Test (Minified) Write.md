
----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1491.12 | 0.0912954 | 1031.93ms | 4604 | 4890 | 35338.8 | 2944.57 | 0.0357447 | 3.4376 | 9.43788 | 0.661382 | 0.00066169 | 3.4557e-05 | 6.17406e-06 | 1(Win) | true |
| Glaze | 818.039 | 0.0586803 | 1276.52ms | 4604 | 4890 | 48508.3 | 5367.37 | 0.0926676 | 6.22561 | 12.939 | 1.08384 | 0.00185306 | 4.8815e-05 | 7.95076e-06 | 2(Loss) | true |
