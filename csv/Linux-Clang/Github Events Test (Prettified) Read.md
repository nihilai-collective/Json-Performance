
----
### Github Events Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 17530 | 0.0338526 | 1071.7ms | 65103 | 1280 | 1840.06 | 3541.76 | 0.0291525 | 0.297126 | 1.60275 | 0.0909329 | 3.13326e-05 | 5.4961e-06 | 2.43604e-06 | 1(Win) | true |
| simdjson (stage-1) | 16135.4 | 0.0520813 | 1100.48ms | 65103 | 1280 | 5140.64 | 3847.88 | 0.0610692 | 0.322638 | 1.50234 | 0.0631154 | 4.25168e-05 | 1.81203e-06 | 1.08002e-07 | 2(Loss) | true |
