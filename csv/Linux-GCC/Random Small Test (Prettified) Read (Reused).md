
----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2654.41 | 0.0578016 | 1068.86ms | 8051 | 4890 | 13669.5 | 2892.56 | 0.119807 | 1.96339 | 8.70004 | 1.30344 | 0.000745909 | 3.43414e-05 | 1.42242e-05 | 1(Win) | true |
| Jsonifier | 2258.39 | 0.0501285 | 1123.6ms | 8051 | 160 | 464.722 | 3399.79 | 0.00735394 | 2.31002 | 9.48826 | 1.72736 | 0.00160229 | 3.26046e-05 | 6.98671e-06 | 2(Loss) | true |
| simdjson (reflection) | 2109.35 | 0.0676746 | 1158.8ms | 8051 | 2560 | 15534.4 | 3640 | 0.0922268 | 2.43028 | 10.1243 | 1.55422 | 0.0013249 | 7.67083e-05 | 3.6098e-05 | 3(Loss) | true |
| Glaze | 1997.14 | 0.0881963 | 1167.84ms | 8051 | 1280 | 14716.2 | 3844.52 | 0.0826995 | 2.60793 | 11.5381 | 2.15998 | 0.00353159 | 3.90091e-05 | 1.58171e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1948.04 | 0.11518 | 1191.04ms | 8051 | 320 | 6594.91 | 3941.42 | 0.00991176 | 2.6714 | 9.89368 | 1.51223 | 0.00218995 | 4.46373e-05 | 2.17364e-05 | 5(Loss) | true |
