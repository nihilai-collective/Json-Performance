
----
### Google Maps Response Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1646.9 | 0.052012 | 1288.2ms | 9378 | 640 | 5105.91 | 5430.54 | 0.0282913 | 3.14988 | 13.9818 | 2.72883 | 0.00600624 | 1.56617e-05 | 8.33067e-07 | 1(Win) | true |
| simdjson (ondemand) | 1564.32 | 0.0389155 | 1310.94ms | 9378 | 4890 | 24206 | 5717.21 | 0.011596 | 3.31181 | 14.6878 | 2.73129 | 0.00281137 | 3.6351e-05 | 1.40432e-05 | 2(Loss) | true |
