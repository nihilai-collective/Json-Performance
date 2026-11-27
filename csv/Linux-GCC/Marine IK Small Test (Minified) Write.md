
----
### Marine IK Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1584.25 | 0.0561434 | 305.683ms | 4918 | 80 | 221.013 | 2960.5 | 0.103129 | 1.54826 | 1(Win) | true |
| simdjson (reflection) | 1456.86 | 0.027123 | 330.626ms | 4918 | 80 | 60.9968 | 3219.38 | 0.0240672 | 1.68518 | 2(Loss) | true |
| Glaze | 1015.92 | 0.181714 | 438.838ms | 4604 | 2560 | 157894 | 4321.9 | 0.665583 | 2.42166 | 3(Loss) | true |
