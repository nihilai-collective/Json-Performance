
----
### Instruments Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5207.59 | 0.0502158 | 2721.17ms | 108313 | 640 | 63496.5 | 19835.5 | 0.0606839 | 0.986773 | 5.40314 | 0.772456 | 0.000895971 | 4.94804e-06 | 3.46219e-06 | 1(Win) | true |
| simdjson (ondemand) | 4671.23 | 0.18781 | 2979.02ms | 108313 | 30 | 51743.9 | 22113.1 | 0.21012 | 1.10144 | 5.78844 | 0.733421 | 0.00104912 | 2.80053e-05 | 2.67743e-05 | 2(Loss) | true |
