
----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1433.94 | 0.234334 | 7861.99ms | 7351818 | 40 | 5.25118e+09 | 4.88948e+06 | 0.495956 | 3.5353 | 14.97 | 3.21224 | 0.0111822 | 0.180903 | 0.00286236 | 1(Win) | true |
| simdjson (ondemand) | 944.497 | 0.532692 | 5592.07ms | 7351818 | 30 | 4.69096e+10 | 7.42325e+06 | 0.842218 | 5.3812 | 25.5363 | 5.09717 | 0.0101933 | 0.430577 | 0.00661506 | 2(Loss) | true |
