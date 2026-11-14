
----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2372.74 | 0.0321299 | 1088.03ms | 8150 | 4890 | 5416.82 | 3275.73 | 0.0359092 | 2.2017 | 9.35387 | 1.68479 | 0.00250513 | 2.07761e-05 | 3.96452e-06 | 1(Win) | true |
| simdjson (ondemand) | 1952.44 | 0.0849226 | 1154.03ms | 8150 | 160 | 1828.64 | 3980.89 | 0.0554517 | 2.6667 | 10.7357 | 1.73975 | 0.00330752 | 2.76074e-05 | 8.43558e-06 | 2(Loss) | true |
