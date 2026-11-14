
----
### Google Maps Response Test (Minified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10033.1 | 0.0664415 | 827.235ms | 11812 | 4890 | 2721.21 | 1122.76 | 0.108917 | 0.530592 | 2.50364 | 0.11082 | 8.50059e-05 | 1.69319e-05 | 5.15922e-06 | 1(Win) | true |
| simdjson (stage-1) | 9367.71 | 0.0688818 | 832.77ms | 11812 | 1280 | 878.211 | 1202.51 | 0.0540177 | 0.567757 | 2.80596 | 0.116576 | 8.50565e-05 | 9.12737e-06 | 5.29123e-07 | 2(Loss) | true |
