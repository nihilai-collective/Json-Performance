
----
### Github Events Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1244.03 | 0.0217912 | 6279.05ms | 65103 | 4890 | 578379 | 49908.1 | 0.102433 | 4.11803 | 15.0935 | 2.96844 | 0.0109838 | 2.48937e-05 | 1.47038e-05 | 1(Win) | true |
| simdjson (ondemand) | 653.37 | 0.0602655 | 5548.69ms | 65103 | 1280 | 4.19789e+06 | 95025.9 | 0.0210236 | 7.83247 | 28.4123 | 5.66214 | 0.0506673 | 2.38084e-05 | 1.09562e-05 | 2(Loss) | true |
