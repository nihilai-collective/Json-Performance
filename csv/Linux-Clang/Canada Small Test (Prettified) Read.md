
----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1776.9 | 0.166617 | 1352.07ms | 11579 | 320 | 34308.9 | 6214.52 | 0.107021 | 2.83242 | 13.6667 | 2.32568 | 0.00148329 | 5.07384e-05 | 3.10368e-05 | 1(Win) | true |
| Jsonifier (generic) | 1738.83 | 0.0945105 | 1373.03ms | 11579 | 320 | 11527.6 | 6350.61 | 0.066878 | 2.93123 | 13.9775 | 2.60014 | 0.00132541 | 1.18749e-05 | 1.61931e-06 | 2(Loss) | true |
