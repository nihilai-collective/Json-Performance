
----
### Canada Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10558.3 | 0.195999 | 6091.44ms | 5212421 | 640 | 5.44977e+08 | 470811 | 1.14246 | 0.47731 | 1.94442 | 0.198816 | 0.00212468 | 0.0393907 | 1.00229e-05 | 1(Win) | true |
| simdjson (ondemand) | 10038.2 | 0.243364 | 6432.21ms | 5212421 | 160 | 2.32378e+08 | 495201 | 0.0349685 | 0.50477 | 2.19702 | 0.202777 | 0.00182643 | 0.039397 | 2.32617e-06 | 2(Loss) | true |
