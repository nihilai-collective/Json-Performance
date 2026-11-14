
----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2684.78 | 0.0240936 | 1072.66ms | 9378 | 4890 | 3150.03 | 3331.21 | 0.0853889 | 1.9412 | 8.63702 | 1.53679 | 0.00149667 | 2.17626e-05 | 5.38614e-06 | 1(Win) | true |
| simdjson (ondemand) | 2333.07 | 0.0720918 | 1135.02ms | 9378 | 160 | 1221.96 | 3833.39 | 0.0485627 | 2.2321 | 9.5917 | 1.54639 | 0.00159949 | 2.46588e-05 | 2.66581e-06 | 2(Loss) | true |
