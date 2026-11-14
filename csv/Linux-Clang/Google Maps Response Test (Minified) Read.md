
----
### Google Maps Response Test (Minified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10233.4 | 0.148425 | 822.78ms | 11812 | 1280 | 3416.91 | 1100.79 | 0.142074 | 0.520994 | 2.54004 | 0.128175 | 8.57179e-05 | 6.74632e-06 | 4.62983e-07 | 1(Win) | true |
| simdjson (stage-1) | 9490.54 | 0.0751527 | 835.284ms | 11812 | 4890 | 3891.02 | 1186.95 | 0.0615907 | 0.558902 | 2.58874 | 0.116581 | 8.55946e-05 | 9.21042e-06 | 1.78322e-06 | 2(Loss) | true |
