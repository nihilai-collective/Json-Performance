
----
### Marine IK Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3195.22 | 0.299031 | 7131.84ms | 1834197 | 640 | 1.71515e+09 | 547451 | 0.609198 | 1.61116 | 8.50381 | 1.52919 | 0.000584575 | 0.113194 | 6.28511e-06 | 1(Win) | true |
| simdjson (ondemand) | 2242.71 | 0.256499 | 9866.9ms | 1834197 | 320 | 1.28075e+09 | 779961 | 0.0328233 | 2.27651 | 12.8394 | 2.27672 | 0.00481044 | 0.150773 | 4.67337e-06 | 2(Loss) | true |
