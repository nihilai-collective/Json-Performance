
----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 418.293 | 0.143087 | 6662.3ms | 1834197 | 30 | 1.07412e+09 | 4.18182e+06 | 0.404756 | 12.0558 | 59.6326 | 12.8028 | 0.0380678 | 0.323043 | 0.000547342 | 1(Win) | true |
| simdjson (ondemand) | 278.651 | 0.0621641 | 9712.16ms | 1834197 | 80 | 1.21826e+09 | 6.27748e+06 | 0.0290427 | 18.2159 | 102.355 | 20.5158 | 0.045955 | 0.76803 | 0.0172433 | 2(Loss) | true |
