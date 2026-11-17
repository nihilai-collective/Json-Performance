
----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6869.4 | 0.202679 | 768.972ms | 3808 | 80 | 91.8467 | 528.663 | 0.740794 | 0.809385 | 3.25289 | 0.371061 | 0.000262605 | 1.31303e-05 | 0 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 6826.94 | 0.207927 | 769.241ms | 3808 | 80 | 97.8709 | 531.95 | 0.0611333 | 0.810727 | 3.25289 | 0.371061 | 0.000262605 | 2.62605e-05 | 6.56513e-06 | 2(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 6826.42 | 0.141168 | 771.96ms | 3808 | 320 | 180.48 | 531.991 | 0.227848 | 0.809595 | 3.2542 | 0.318803 | 0.000510439 | 1.88747e-05 | 0 | 2(Tie) | true |
| simdjson (reflection) | 6605.78 | 0.374051 | 777.729ms | 3808 | 640 | 2706.36 | 549.759 | 0.397199 | 0.832836 | 3.24422 | 0.323792 | 0.000543675 | 1.39509e-05 | 2.46192e-06 | 4(Loss) | true |
| Glaze | 3558.65 | 0.0522688 | 821.921ms | 3808 | 640 | 182.091 | 1020.5 | 0.120798 | 1.50001 | 6.53151 | 1.19433 | 0.000265888 | 3.28256e-06 | 0 | 5(Loss) | true |
