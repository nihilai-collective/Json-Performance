
----
### Github Events Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11332 | 0.0773803 | 751.555ms | 2866 | 2560 | 89.1743 | 241.196 | 0.178304 | 0.531963 | 1.13084 | 0.185276 | 0.000348918 | 2.65778e-05 | 1.43111e-05 | 1(Win) | true |
| Glaze | 3740.31 | 0.809841 | 805.197ms | 2866 | 80 | 2801.73 | 730.75 | 0.405331 | 1.45437 | 4.08758 | 0.682484 | 0.000348918 | 5.23378e-05 | 3.48918e-05 | 2(Loss) | true |
| simdjson (reflection) | 555.987 | 0.0740229 | 1228.22ms | 2866 | 4890 | 64753.8 | 4916 | 0.0183192 | 9.3144 | 34.8503 | 7.30461 | 0.00900509 | 0.000160617 | 7.89883e-05 | 3(Loss) | true |
