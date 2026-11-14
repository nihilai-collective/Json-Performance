
----
### Apache Builds Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1516.31 | 0.0839358 | 931.535ms | 3370 | 1280 | 4051.24 | 2119.54 | 0.0432542 | 3.45773 | 13.4852 | 2.62819 | 0.00305615 | 6.69974e-05 | 3.08327e-05 | 1(Win) | true |
| simdjson (ondemand) | 938.308 | 0.0617924 | 1059.85ms | 3370 | 640 | 2866.94 | 3425.19 | 0.0777934 | 5.55306 | 23.035 | 4.60979 | 0.00807307 | 2.27188e-05 | 0 | 2(Loss) | true |
