
----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 736.112 | 0.148217 | 506.415ms | 3862 | 4890 | 268933 | 5003.44 | 0.228029 | 3.34485 | 1(Win) | true |
| simdjson (ondemand) | 655.798 | 0.0273917 | 598.841ms | 3862 | 80 | 189.327 | 5616.2 | 0.013356 | 3.7566 | 2(Loss) | true |
