
----
### Marine IK Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10132.5 | 0.114053 | 8930.83ms | 7351818 | 320 | 1.99308e+08 | 691958 | 0.299053 | 0.50332 | 2.24534 | 0.257055 | 0.00192036 | 0.0423417 | 8.54125e-06 | 1(Win) | true |
| simdjson (ondemand) | 9006.01 | 0.272366 | 9853.73ms | 7351818 | 80 | 3.59683e+08 | 778507 | 0.924974 | 0.563671 | 2.64671 | 0.256645 | 0.00109324 | 0.0424066 | 0.000400663 | 2(Loss) | true |
