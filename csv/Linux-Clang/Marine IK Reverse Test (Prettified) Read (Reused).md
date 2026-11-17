
----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1433.52 | 0.430798 | 7689.06ms | 7351818 | 30 | 1.33183e+10 | 4.89092e+06 | 0.275606 | 3.54698 | 15.9074 | 3.24153 | 0.010524 | 0.181295 | 0.00433258 | 1(Win) | true |
| simdjson (ondemand) | 961.294 | 0.0916392 | 5305.53ms | 7351818 | 40 | 1.7869e+09 | 7.29354e+06 | 0.960852 | 5.34073 | 26.4509 | 5.15844 | 0.0115483 | 0.430653 | 0.000820647 | 2(Loss) | true |
