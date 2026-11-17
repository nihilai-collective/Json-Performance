
----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 921.891 | 0.185589 | 6652.92ms | 1834197 | 30 | 3.72012e+08 | 1.89743e+06 | 0.102644 | 5.44757 | 22.5131 | 5.0806 | 0.0355 | 0.0565817 | 0.00516371 | 1(Win) | true |
| Jsonifier (two-stage) | 788.498 | 0.0524186 | 7571.75ms | 1834197 | 160 | 2.16363e+08 | 2.21843e+06 | 0.0945465 | 6.37839 | 26.8068 | 5.48513 | 0.0409841 | 0.119591 | 0.00389915 | 2(Loss) | true |
| Glaze | 722.239 | 0.0616978 | 8268.98ms | 1834197 | 160 | 3.57265e+08 | 2.42195e+06 | 0.0190547 | 6.94954 | 29.3656 | 5.62362 | 0.0331142 | 0.0598196 | 0.00366885 | 3(Loss) | true |
| simdjson (reflection) | 686.383 | 0.0526344 | 8553.46ms | 1834197 | 80 | 1.43942e+08 | 2.54847e+06 | 0.0730437 | 7.34685 | 31.8036 | 5.77333 | 0.0320177 | 0.111923 | 0.00350844 | 4(Loss) | true |
| simdjson (ondemand) | 577.87 | 0.0795708 | 10091.7ms | 1834197 | 80 | 4.64119e+08 | 3.02702e+06 | 0.0246834 | 8.72173 | 35.0131 | 6.65237 | 0.0371507 | 0.118641 | 0.0237046 | 5(Loss) | true |
