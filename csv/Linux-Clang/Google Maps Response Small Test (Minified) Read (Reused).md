
----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2634.17 | 0.103797 | 920.321ms | 4390 | 2560 | 6967.08 | 1589.35 | 0.215621 | 1.97497 | 9.31458 | 1.58861 | 0.00174616 | 4.33336e-05 | 9.87685e-06 | 1(Win) | true |
| Glaze | 1973.33 | 0.0797765 | 973.317ms | 4390 | 4890 | 14008.4 | 2121.61 | 0.0732761 | 2.60966 | 12.2756 | 2.32369 | 0.000614475 | 3.85706e-05 | 3.5403e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1872.31 | 0.0837182 | 988.772ms | 4390 | 4890 | 17136.5 | 2236.08 | 0.195515 | 2.75054 | 12.7506 | 2.13166 | 0.00255284 | 5.10083e-05 | 7.91909e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1142.27 | 0.0706183 | 1125.85ms | 4390 | 4890 | 32759.6 | 3665.2 | 0.000848531 | 4.47658 | 19.2276 | 3.11754 | 0.0032063 | 8.13338e-05 | 2.34778e-05 | 4(Loss) | true |
