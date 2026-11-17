
----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2220.82 | 0.186177 | 924.437ms | 4390 | 640 | 7883.83 | 1885.18 | 0.0349061 | 2.31538 | 10.5394 | 1.87198 | 0.00205901 | 3.2389e-05 | 0 | 1(Win) | true |
| Glaze | 1701.27 | 0.0792585 | 981.688ms | 4390 | 4890 | 18603.1 | 2460.89 | 0.0617728 | 3.02084 | 13.8198 | 2.66287 | 0.000625795 | 5.87876e-05 | 1.35556e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1681.02 | 0.0768961 | 987.061ms | 4390 | 4890 | 17935.1 | 2490.53 | 0.184686 | 3.05712 | 13.977 | 2.41503 | 0.00270954 | 5.61324e-05 | 1.0947e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1064.71 | 0.0879287 | 1133.06ms | 4390 | 2560 | 30603.5 | 3932.19 | 0.0464134 | 4.79144 | 20.461 | 3.39658 | 0.00301796 | 6.60236e-05 | 1.63724e-05 | 4(Loss) | true |
